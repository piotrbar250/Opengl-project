#version 450 core

in vec3 inColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(inColor, 1.0f);
}