#include <iostream>

#include <SDL.h>
#include <glad/glad.h>
#include <vector>

#undef main

//Globals
int gScreenHeight = 480;
int gScreenWidth = 640;

SDL_Window* gGraphicApplicationWindow=nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit=false;

//VAO
GLuint gVertextArrayObject =0;

//VBO
GLuint gVertextBufferObject=0;

//Program Object (for our shaders)
GLuint gGraphicsPipelineShaderProgram = 0;


const std::string gVertexShaderSource =
        "#version 410 core\n"
        "in vec4 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x,position.y,position.z,position.w);\n"
        "}\n";

const std::string gFragmentShaderSource =
        "#version 410 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(1.0f,0.5f,0.0f,1.0f);\n"
        "}\n";


GLuint CompileShader(GLuint type, const std::string& source){
    GLuint shaderObject;
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src=source.c_str();
    glShaderSource(shaderObject,1,&src,nullptr);
    glCompileShader(shaderObject);

    return shaderObject;
}


GLuint CreateShaderProgram(const std::string& vs,const std::string& fs)
{
    GLuint programObject = glCreateProgram();
    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER,vs);
    GLuint myFragmentShader =CompileShader(GL_FRAGMENT_SHADER,fs);

    glAttachShader(programObject,myVertexShader);
    glAttachShader(programObject,myFragmentShader);
    glLinkProgram(programObject);

    //validate our program
    glValidateProgram(programObject);

    //glDetachShader,glDeleteShader

    return programObject;

}

void CreateGraphicsPipeline()
{
    gGraphicsPipelineShaderProgram = CreateShaderProgram(gVertexShaderSource,gFragmentShaderSource);
}



void GetOpenGLVersionInfo()
{
    std::cout<<"vendor: "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"renderer: "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"Shading Language: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}


void VertexSpecification()
{
    //Lives on the cpu
    const std::vector<GLfloat> vertextPosition{
        // x       y      z
          -0.8f, -0.8f, 0.0f,  //vertex 1
           0.8f, -0.8f, 0.0f,  //vertex 2
           0.0f, 0.8f, 0.0f    //vertex 3
    };

    //We start setting things up
    //on the GPU
    glGenVertexArrays(1,&gVertextArrayObject);
    glBindVertexArray(gVertextArrayObject);

    //start generating our VBO
    glGenBuffers(1,&gVertextBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertextBufferObject);
    glBufferData(GL_ARRAY_BUFFER,vertextPosition.size()*sizeof(GLfloat),vertextPosition.data(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    //clean up
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

}



void InitializeProgram()
{
    if(SDL_Init(SDL_INIT_VIDEO) <0)
    {
        std::cout<<"SDL2 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gGraphicApplicationWindow =  SDL_CreateWindow("OpenGL Window",100,100,gScreenWidth,gScreenHeight,SDL_WINDOW_OPENGL);

    if(gGraphicApplicationWindow == nullptr)
    {
        std::cout<<"SDL_WINDOW was not able to be created" << std::endl;
        exit(1);
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicApplicationWindow);

    if(gOpenGLContext == nullptr)
    {
        std::cout<<"OpenGL Context not available" << std::endl;
        exit(1);
    }

    //init the glad lib
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout<<"glad was not able to create" << std::endl;
        exit(1);
    }
    GetOpenGLVersionInfo();

}


void Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) !=0)
    {

        if(e.type==SDL_QUIT){
            std::cout<<"Goodbye!" << std::endl;
            gQuit=true;
        }
    }

}
void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,gScreenWidth,gScreenHeight);
    glClearColor(1.f,1.f,0.1f,1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram);
}
void Draw()
{
    glBindVertexArray(gVertextArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER,gVertextBufferObject);

    glDrawArrays(GL_TRIANGLES,0,3);
}



void MainLoop()
{
    while (!gQuit)
    {
        Input();
        PreDraw();
        Draw();

        //update the screen
        SDL_GL_SwapWindow(gGraphicApplicationWindow);
    }
}

void CleanUp()
{
    SDL_DestroyWindow(gGraphicApplicationWindow);
    SDL_Quit();
}



int main() {
    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();

    MainLoop();


    CleanUp();

    return 0;
}
