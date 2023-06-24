#include <iostream>

#include <SDL.h>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <fstream>

#undef main

//Globals
int gScreenHeight = 480;
int gScreenWidth = 640;

SDL_Window* gGraphicApplicationWindow=nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit=false;

//VAO
GLuint gVertexArrayObject =0;

//VBO
GLuint gVertexBufferObject=0;
GLuint gIndexBufferObject=0;


//Program Object (for our shaders)
GLuint gGraphicsPipelineShaderProgram = 0;


//vvvvvvvvvvvvvvvvvvvvvvvvvvvvv Error Handling Routines vvvvvvvvvvvvvvvvvvvv
static void GLClearAllErrors()
{
    while (glGetError() != GL_NO_ERROR){

    }
}

static bool GLCheckErrorStatus(const char* function,int line)
{
    while(GLenum error = glGetError()){
        std::cout << "OpenGL Error:" <<error
        <<"\tLine: "<<line
        <<"\tfunction: "<<function<<std::endl;
        return true;
    }
    return false;
}


#define GLCheck(x) GLClearAllErrors();x;GLCheckErrorStatus(#x,__LINE__)
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Error Handling Routines ^^^^^^^^^^^^^^^^^^^^


std::string LoadShaderAsString(const std::string& filename)
{
    std::string result="";

    std::string line="";
    std::ifstream myFile(filename.c_str());

    if(myFile.is_open()){
        while(std::getline(myFile,line)){
            result +=line + '\n';
        }
        myFile.close();
    }

    return result;
}



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

    // 检查编译状态
    GLint compileStatus;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        // 获取编译错误信息
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, NULL, infoLog);
        std::cout << "Shader compilation error: " << infoLog << std::endl;

        // 删除 GLSL 着色器程序对象
        glDeleteShader(shaderObject);
    }


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
    //一旦我们的program object 被创建以后，我们就可以detach and delete 我们的shader了
    glDetachShader(programObject,myVertexShader);
    glDetachShader(programObject,myFragmentShader);

    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);

    return programObject;

}

void CreateGraphicsPipeline()
{
    std::string vertexShaderSource = LoadShaderAsString("../shaders/vert.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("../shaders/frag.glsl");

    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource,fragmentShaderSource);
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
    const std::vector<GLfloat> vertexData{
          // 0 - Vertex
          -0.5f, -0.5f, 0.0f,  //position 1
          1.0f, 0.0f, 0.0f,    //color 1
          // 1 - Vertex
          0.5f, -0.5f, 0.0f,   //position 2
          0.0f, 1.0f, 0.0f,    //color 2
          // 2 - Vertex
          -0.5f, 0.5f, 0.0f,   //position 3
          0.0f, 0.0f, 1.0f,    //color 3
          // 3 - Vertex
          0.5f, 0.5f, 0.0f,   //position 4
          0.0f, 1.0f, 0.0f,    //color 4
    };


    //We start setting things up
    //on the GPU
    //VAO things
    glGenVertexArrays(1,&gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);


    //start generating our VBO
    glGenBuffers(1,&gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,vertexData.size()*sizeof(GL_FLOAT),vertexData.data(),GL_STATIC_DRAW);


    const std::vector<GLuint> indexBufferData{2,0,1,3,2,1};
    //Setup the index Buffer Object(IBO i.e EBO)
    glGenBuffers(1,&gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexBufferData.size()*sizeof(GLuint),indexBufferData.data(),GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*6,(void*)0);  //倒数第二个参数stride，指的是一整个帧周期的长度，在这里就是xyz+rgb，一个整属性的字节长度，所以这里要 GL_FLOAT*6


    //linking up the attributes in our VAO
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*6,(GLvoid*)(sizeof(GL_FLOAT)*3));

    //clean up
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

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
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER,gVertexBufferObject);

//    glDrawArrays(GL_TRIANGLES,0,6);
    GLCheck(glDrawElements(GL_TRIANGLES,
                   6,  //6个顶点
                   GL_UNSIGNED_INT,
                   0  //index之前没有东西
                   ));

    //not necessary if we only have one graphics pipeline
    glUseProgram(0);
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



int main2() {

    //1. Setup the graphics program
    InitializeProgram();

    //2. Setup our geometry
    VertexSpecification();

    //3. Create our graphics pipeline
    //  -At a minimum, this means ther vertex and fragment shader
    CreateGraphicsPipeline();

    //4. Call the main application loop
    MainLoop();

    //5. Call the cleanup function when our program terminates
    CleanUp();

    return 0;
}
