//#version 410 core
#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;

uniform mat4 u_ModelMatrix;
uniform mat4 u_Projection;  //We'll use a perspective projection

out vec3 v_vertexColors;

void main()
{
    v_vertexColors = vertexColors;

    vec4 newPostion = u_Projection * u_ModelMatrix * vec4(position,1.0f);
                                                                //don't forget 'w'
    gl_Position = vec4(newPostion.x,newPostion.y,newPostion.z,newPostion.w);

}

