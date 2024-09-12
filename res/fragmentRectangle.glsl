#version 450 core

in vec3 uColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(uColor, 1.0f);
    // FragColor = texture(ourTexture, TexCoord) * vec4(uColor, 1.0f);
    // FragColor =  mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, 1.0f - TexCoord.y)), 0.2f);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y)), 0.2f);

}