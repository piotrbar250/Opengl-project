#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 inColor;

uniform vec3 horizontalOffset;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);//+ vec4(horizontalOffset, 0.0f);
    inColor = aPos; //+ horizontalOffset;
}