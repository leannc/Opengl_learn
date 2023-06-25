//
// Created by wangkang on 2023/6/24.
//

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

//glm::translate,glm::rotate,glm::scale
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

//glm::perspective
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

//glm::pi
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <cmath>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    glm::vec4 vertex(1.0f,5.0f,1.0f,1.0f); //最后一个1.0f，表示的是这个是一个点，如果是0.0f，表示这是一个向量
    std::cout<<"origin vertex\n"<<glm::to_string(vertex)<<'\n'<<std::endl;

    glm::mat4 model(1.0f);

    //scaling Matrix
//    model = glm::scale(glm::mat4(1.0f),glm::vec3(3.0f,2.0f,2.0f));
    glm::mat4 s = glm::scale(glm::mat4(1.0f),glm::vec3(2.0f,2.0f,2.0f));

    //rotation Matrix
//    model=glm::rotate(glm::mat4(1.0f),glm::radians(180.0f),glm::vec3(0,1,0));
    glm::mat4 r = glm::rotate(glm::mat4(1.0f),glm::radians(180.0f),glm::vec3(0,1,0));

    //translate Matrix
//    model = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-2.0f));
    glm::mat4 t = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-2.0f));

    //translate first, then rotate, then scale
    model = s*r*t;

    std::cout << "------------model-------------------"<<std::endl;
    //Trick to print off each column
    std::cout << glm::to_string(model[0])<<std::endl;
    std::cout << glm::to_string(model[1])<<std::endl;
    std::cout << glm::to_string(model[2])<<std::endl;
    std::cout << glm::to_string(model[3])<<std::endl;
    std::cout <<std::endl;


    glm::vec4 worldspace_vertex = (model*vertex);

    std::cout << "\n"<<"our vertex in world space\n";
    std::cout<<glm::to_string(worldspace_vertex)<<std::endl;


    return 0;
}