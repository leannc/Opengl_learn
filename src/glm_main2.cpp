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
    //Create vectors
    glm::vec3 A(3.0f,4.0f,0.0f);
    glm::vec3 B(0.0f,7.0f,0.0f);

    std::cout <<"A's length: "<<glm::length(A)<<std::endl;
    std::cout <<"B's length : "<<glm::length(B)<<std::endl;
    std::cout <<"A normalized : "<<glm::to_string(glm::normalize(A))<<std::endl;
    std::cout <<"A-hat : "<<glm::length(glm::normalize(A))<<std::endl;

    float dotproduct = glm::dot(glm::normalize(A),(glm::normalize(B))); // 这个是cos的值
    std::cout<<"dot product (which is the cos value): "<<dotproduct<<std::endl;

    std::cout<<"the angle is: "<<std::acos(dotproduct)* 180.0/M_PI<<std::endl;

    std::cout<<glm::dot(glm::normalize(A),(glm::normalize(B)))<<std::endl;


    std::cout<<"--------------------------------------------------------------- "<<std::endl;
    glm::vec C = glm::cross(A,B);
    glm::vec D = glm::cross(B,A);
    std::cout<<"cross product of A,B: "<<glm::to_string(C)<<std::endl;
    std::cout<<"cross product of B,A: "<<glm::to_string(D)<<std::endl;



    return 0;
}