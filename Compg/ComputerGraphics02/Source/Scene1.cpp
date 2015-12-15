#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
    //Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Set background color 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //load vertex and fragment shaders
    m_programID = LoadShaders(
        "Shader//SimpleVertexShader.vertexshader",
        "Shader//SimpleFragmentShader.fragmentshader");

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

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
    // clear color every frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(0); //1st attri buffer: vertices

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
	//draw triangle

	glDrawArrays(GL_TRIANGLES, 0, 6); //starting from vertex 0; 3 vertices = 1 triangle

	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(0);

	
	// Render VBO here
}

void Scene1::Exit()
{
    glDeleteProgram(m_programID);
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	// Cleanup VBO here
}
