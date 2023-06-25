//#version 410 core
#version 140

in vec3 v_vertexColors;

out vec4 color;

uniform float u_Offset; // uniform variable

void main()
{
    color = vec4(v_vertexColors.r-u_Offset,v_vertexColors.g,v_vertexColors.b,1.0f);
//    color = vec4(1.0f,0.0f,0.0f,1.0f);
}