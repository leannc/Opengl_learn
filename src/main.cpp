#include <iostream>

#include <SDL.h>
#include <glad/glad.h>

#undef main

//Globals
int gScreenHeight = 480;
int gScreenWidth = 640;

SDL_Window* gGraphicApplicationWindow=nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit=false;


void GetOpenGLVersionInfo()
{
    std::cout<<"vendor: "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"renderer: "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"Shading Language: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
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

}
void Draw()
{

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

    MainLoop();

    CleanUp();

    return 0;
}
