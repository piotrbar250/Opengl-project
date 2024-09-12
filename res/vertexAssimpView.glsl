#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


// Gourand shading
uniform bool gourand;

out vec3 LightingColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoords = aTexCoords;

    if(gourand)
    {
        vec3 Position = vec3(view * model * vec4(aPos, 1.0f));
        vec3 normal = mat3(transpose(inverse(view * model))) * aNormal;
        vec3 viewLightPos = vec3(view * vec4(lightPos, 1.0f));

        float ambientStrength =  0.1f;
        vec3 ambient = ambientStrength * lightColor;

        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(viewLightPos - Position);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        float specularStrength = 1.0f;
        vec3 viewDir = normalize(-Position);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
        vec3 specular = specularStrength * spec * lightColor;

        LightingColor = ambient + diffuse + specular;
    }
    else
    {
        FragPos = vec3(view * model * vec4(aPos, 1.0f));
        Normal = mat3(transpose(inverse(view * model))) * aNormal;
        LightPos = vec3(view * vec4(lightPos, 1.0f));
    }
}

// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;

// out vec2 TexCoords;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// void main()
// {
//     TexCoords = aTexCoords;    
//     gl_Position = projection * view * model * vec4(aPos, 1.0);
// }