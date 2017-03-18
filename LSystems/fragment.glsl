#version 330 core
in vec3 ourColor;

out vec4 color;

void main()
{
    color = vec4(0.1f, 1.0f , 0.5f - (ourColor.y/2 + ourColor.x/2),  1.0f);  
}