#version 450 core
out vec4 FragColor;

uniform vec4 uColor;

void main()
{
    FragColor = uColor;
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}