//#version 410 core
#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;

uniform mat4 u_ModelMatrix;

out vec3 v_vertexColors;

void main()
{
    v_vertexColors = vertexColors;

    vec4 newPostion = u_ModelMatrix * vec4(position,1.0f);

    gl_Position = vec4(newPostion.x,newPostion.y,newPostion.z,1.0f);

}

