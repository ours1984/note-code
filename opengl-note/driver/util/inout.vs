#version 330 core

uniform vec3 cpos;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(cpos, 1.0f);
}
