#version 450 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;



void main()
{
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);
    FragColor = texture(texture1, TexCoord);
}