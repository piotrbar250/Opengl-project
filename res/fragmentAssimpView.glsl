#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 objectColor;

uniform sampler2D texture_diffuse1;

// Gouraud shading
uniform bool gouraud;
in vec3 LightingColor;

// Light sources
struct Light {
    vec3 pos;
    vec3 color;

    // Spotlight-specific parameters
    vec3 direction;  // Direction the spotlight is pointing
    float cutOff;    // Cosine of the inner cutoff angle
    float outerCutOff; // Cosine of the outer cutoff angle for smooth transition
};

uniform Light lightSources[2];

// Function to calculate Phong shading
vec3 calculatePhongShading(vec3 texColor)
{
    float ambientStrength = 0.1f;
    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(-FragPos);

    for (int i = 0; i < 2; i++) {
        vec3 lightDir = normalize(lightSources[i].pos - FragPos);

        // Spotlight calculations for lightSources[0]
        if (i == 0) {
            // Calculate the angle between the light direction and the fragment's direction
            float theta = dot(lightDir, normalize(-lightSources[0].direction));

            // Check if the fragment is inside the spotlight cone
            float epsilon = lightSources[0].cutOff - lightSources[0].outerCutOff;
            float intensity = clamp((theta - lightSources[0].outerCutOff) / epsilon, 0.0, 1.0);

            // Skip this light if it's outside the spotlight cone
            if (theta < lightSources[0].outerCutOff) {
                intensity = 0.0;
            }

            // Apply attenuation based on the spotlight effect
            lightDir = normalize(lightSources[0].pos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0f);
            diffuse += diff * lightSources[0].color * intensity;

            // Specular component (using the intensity for spotlight)
            float specularStrength = 0.5f;
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
            specular += specularStrength * spec * lightSources[0].color * intensity;

            // Ambient component is attenuated too
            ambient += ambientStrength * lightSources[0].color * intensity;
        }
        else {
            // Standard Phong calculations for other lights
            ambient += ambientStrength * lightSources[i].color;

            float diff = max(dot(norm, lightDir), 0.0f);
            diffuse += diff * lightSources[i].color;

            float specularStrength = 0.5f;
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
            specular += specularStrength * spec * lightSources[i].color;
        }
    }

    return (ambient + diffuse + specular) * texColor;
}

const vec3 skyColor = vec3(0.1f, 0.1f, 0.1f);

const float gradient = 1.5;
uniform float fogDensity;

vec3 addFog(vec3 color, float distanceFromCamera)
{
    float visibility = clamp(exp(-pow((distanceFromCamera * fogDensity), gradient)), 0.0, 1.0);
    return mix(skyColor, color, visibility);
}


void main()
{
    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    if(gouraud)
    {
        FragColor = vec4(LightingColor * texColor, 1.0f);
    }
    else
    {
        vec3 result = calculatePhongShading(texColor);
        result = addFog(result, length(-FragPos));
        FragColor = vec4(result, 1.0f);
    }
}