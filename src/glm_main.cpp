//
// Created by wangkang on 2023/6/24.
//

#define GLM_FORCE_SWIZZLE

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <iostream>
#include <glm/gtx/string_cast.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

int glm_main()
{
    glm::vec3 A(1.0f,1.0f,1.1f);
    glm::vec3 B(0.5f,1.0f,0.7f);
    glm::mat4 mat(1.0f);

    glm::vec3 C=glm::cross(A,B);
    std::cout<<"cross(A,B) is: "<<glm::to_string(C)<<std::endl;


    std::cout<<glm::to_string(A.yz())<<std::endl;


    float f = glm::dot(glm::normalize(A),glm::normalize(B));

    std::cout<<"dot(A,B) is: "<<f<<std::endl;

    std::cout<<glm::to_string(A) <<std::endl;
    std::cout<<glm::to_string(B) <<std::endl;
    std::cout<<glm::to_string(glm::normalize(A)) <<std::endl;
    std::cout<<glm::to_string(glm::normalize(B)) <<std::endl;
    std::cout<<glm::to_string(mat) <<std::endl;

    return 0;
}