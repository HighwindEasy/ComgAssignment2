#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"



Scene2::Scene2()
{
    float rotateAngle = 0;
    float translateX = 0;
    float scaleAll = 0;
}

Scene2::~Scene2()
{
}


void Scene2::Init()
{
    //Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Set background color 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//TransformVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader");

    //get handle for "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //Use shader
    glUseProgram(m_programID);

    //Generate temp VAO 
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    // Generate Buffers
    glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

    //Array of 3 vectors that represent 3 vertices
    static const GLfloat vertex_buffer_data[] =
    {
        -0.5f, 0.5f, 0.0f, //vertex 0
        -0.5f, 0.0f, 0.0f, //vertex 1
        0.0f, 0.5f, 0.0f, //vertex 2

        0.0f, 0.0f, 0.0f, //vertex 0
        0.5f, 0.5f, 0.0f, //vertex 1
        0.5f, 0.0f, 0.0f, //vertex 2
    };

    //set current active buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    //Transfer Vertices to open gl
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);


    // Init VBO here

    // array of vectors that represent the colors of the 3 vertices
    static const GLfloat color_buffer_data[] =
    {
        1.0f, 1.0f, 1.0f, //color vertex 0
        1.0f, 1.0f, 1.0f, //color vertex 1
        1.0f, 1.0f, 1.0f, //color vertex 2

        1.0f, 1.0f, 1.0f, //color vertex 0
        1.0f, 1.0f, 1.0f, //color vertex 1
        1.0f, 1.0f, 1.0f, //color vertex 2
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);


}

void Scene2::Update(double dt)
{
    rotateAngle += (float)(10 * dt);
    translateX += (float)(10 * dt);
    scaleAll += (float)(2 * dt);
}

void Scene2::Render()
{
    // clear color every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Mtx44 translate, rotate, scale;
    Mtx44 model;
    Mtx44 view;
    Mtx44 projection;
    Mtx44 MVP;

    translate.SetToIdentity();
    rotate.SetToIdentity();
    scale.SetToIdentity();
    model.SetToIdentity();
    view.SetToIdentity();//camera set at world origin

    projection.SetToOrtho(-40, +40, -30, +30, -10, +10); //define the world in a cube by these boundaries

    glEnableVertexAttribArray(0); //1st attri buffer: vertices
    glEnableVertexAttribArray(1);

    scale.SetToScale(10, 10, 10);
    rotate.SetToRotation(45, 0, 0, 1);
    translate.SetToTranslation(5, 5, 0);
    model = translate * rotate *scale; //scale, fcollowed by rotate then translate
    MVP = projection * view * model;
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update new shader w MVP
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //draw triangle

    glDrawArrays(GL_TRIANGLES, 0, 6); //starting from vertex 0; 3 vertices = 1 triangle
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer
        (
        0, //Attribute 0. Must match layout in shader. usually 0 is for vertex
        3, //size
        GL_FLOAT, //type
        GL_FALSE, //normalised
        0,        //stride
        0         //array buffer offset
        );
    glEnableVertexAttribArray(1);//2nd attr buffer: colors
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    

    glDisableVertexAttribArray(1);

    glDisableVertexAttribArray(0);

   

   
    
}

void Scene2::Exit()
{
    glDeleteProgram(m_programID);
    glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
    glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    // Cleanup VBO here
}
