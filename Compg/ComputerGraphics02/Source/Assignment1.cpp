#include "Assignment1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "shader.hpp"
#include "Application.h"
#include "MyMath.h"

Assignment1::Assignment1()
{
}

Assignment1::~Assignment1()
{
}

void Assignment1::Init()
{
	rotateAngle = 1.9;
	translateX = -1;
	scaleAll = 0.3;
	triangle1start =18 ;
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	Bufferdata();
	COLORS();

	// Load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(m_programID);

	// Enable depth test 
	glEnable(GL_DEPTH_TEST);

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
}
void Assignment1::Bufferdata()
{
	//Rectangle(1)
	static const GLfloat Ground_buffer_data[] = {
		0.0f, 0.8f, 0.0f, // vertex 0 of Rectangle
		3.0f, 0.8f, 0.0f, // vertex 1 of Rectangle
		3.0f, 0.0f, 0.0f, // vertex 2 of Rectangle
		0.0f, 0.0f, 0.0f, //Vertex 3 of Rectangle
	};

	// Set the current active buffer Then Transfer vertices to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Ground_buffer_data), Ground_buffer_data, GL_STATIC_DRAW);
	//Square(2)
	static const GLfloat ICON_buffer_data[] = {
		0.0f, 1.0f, 0.0f, // vertex 0 of Square
		1.0f, 1.0f, 0.0f, // vertex 1 of square
		1.0f, 0.0f, 0.0f, // vertex 2 of square
		0.0f, 0.0f, 0.0f, //Vertex 3 of square
	};

	// Set the current active buffer Then Transfer vertices to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_ICONS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ICON_buffer_data), ICON_buffer_data, GL_STATIC_DRAW);

	//Triangle(3)
	static const GLfloat Mountain_buffer_data[] = {
		0.0f, 0.0f, 0.0f, // vertex 0 of Triangle
		2.0f, 0.0f, 0.0f, // vertex 1 of Triangle
		1.0f, 2.0f, 0.0f, // vertex 2 of Triangle
	};

	// Set the current active buffer Then Transfer vertices to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mountain_buffer_data), Mountain_buffer_data, GL_STATIC_DRAW);

	//Circle (4)
	GLfloat vertex_buffer_data7[36];
	for (int i = 0; i < 12; i++)
	{
		vertex_buffer_data7[i  *3 + 0] = cos(i  *30 * Math::PI / 180);
		vertex_buffer_data7[i  *3 + 1] = sin(i  *30 * Math::PI / 180);
		vertex_buffer_data7[1 * 3 + 2] = 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data7), vertex_buffer_data7, GL_STATIC_DRAW);

	//Circle (6)
	GLfloat vertex_buffer_data8[36];
	for (int i = 0; i < 12; i++)
	{
		vertex_buffer_data8[i * 3 + 0] = cos(i * 30 * Math::PI / 180);
		vertex_buffer_data8[i * 3 + 1] = sin(i * 30 * Math::PI / 180);
		vertex_buffer_data8[1 * 3 + 2] = 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WHITECIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data8), vertex_buffer_data8, GL_STATIC_DRAW);
	
	//Stickman-1(5)
	static const GLfloat StickMan_buffer_data[] = {
		0.0f, 0.8f, 0.0f,
		-0.4f, 0.4f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.4f, 0.4f, 0.0f,
		0.0f, 0.8f, 0.0f,
		-0.4f, 0.4f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0, -0.2, 0.0, 
		0.3,-0.2,0.0,
		0.0,-0.2,0.0,
		0.0,-0.3,0.0,
		0.3,-0.3,0.0,
		0.0,-0.3,0.0,
		0.0,-0.7,0.0,
		-0.2,-0.9,0.0,
		0.0,-0.7,0.0,
		0.2,-0.7,0.0,
		0.0,-0.7,0.0,
		 



	};

	// Set the current active buffer Then Transfer vertices to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STICKMAN]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(StickMan_buffer_data), StickMan_buffer_data, GL_STATIC_DRAW);

}

void Assignment1::COLORS()
{
	//Blue (1)
	static const GLfloat Blue_color_buffer[] = {
		0.000f, 0.000f, 1.000f, //color of vertex 0
		0.000f, 0.000f, 1.000f, //color of vertex 1
		0.000f, 0.000f, 1.000f, //color of vertex 2
		0.000f, 0.000f, 1.000f, //color of vertex 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Blue_color_buffer), Blue_color_buffer, GL_STATIC_DRAW);

	//Pink (2)
	static const GLfloat Tower_color_buffer[] = {
		0.933f, 0.510f, 0.933f, //color of vertex 0
		0.933f, 0.510f, 0.933f, //color of vertex 1
		0.933f, 0.510f, 0.933f, //color of vertex 2
		0.933f, 0.510f, 0.933f, //color of vertex 3

	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tower_color_buffer), Tower_color_buffer, GL_STATIC_DRAW);
	//GREEN (3)
	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat Ground_color_buffer[] = {
		0.604f, 0.804f, 0.196f, //color of vertex 0
		0.604f, 0.804f, 0.196f, //color of vertex 1
		0.604f, 0.804f, 0.196f, //color of vertex 2
		0.604f, 0.804f, 0.196f, //color of vertex 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Ground_color_buffer), Ground_color_buffer, GL_STATIC_DRAW);
	
	//Green (4)
	static const GLfloat Mountain_color_buffer[] = {
		0.000f, 0.392f, 0.000f, //color of vertex 0
		0.000f, 0.392f, 0.000f, //color of vertex 1
		0.000f, 0.392f, 0.000f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mountain_color_buffer), Mountain_color_buffer, GL_STATIC_DRAW);

	//White (5)
	static const GLfloat White_color_buffer[] = {
		0.878f, 1.000f, 1.000f, //color of vertex 0
		0.878f, 1.000f, 1.000f, //color of vertex 1
		0.878f, 1.000f, 1.000f, //color of vertex 2
		0.878f, 1.000f, 1.000f, //color of vertex 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECOLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(White_color_buffer), White_color_buffer, GL_STATIC_DRAW);
	//Red (6)
	static const GLfloat RED_color_buffer[] = {
		0.863f, 0.361f, 0.235f, //color of vertex 0
		0.863f, 0.361f, 0.235f, //color of vertex 1
		0.863f, 0.361f, 0.235f, //color of vertex 2
		0.863f, 0.361f, 0.235f, //color of vertex 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RED_color_buffer), RED_color_buffer, GL_STATIC_DRAW);

	//Circle Color (7)
	static GLfloat color_buffer_data7[36];
	for (int i = 0; i < 12; i++)
	{
		color_buffer_data7[i * 3 + 0] = 0.933f;
		color_buffer_data7[i * 3 + 1] = 0.510f;
		color_buffer_data7[i * 3 + 2] = 0.933f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data7), color_buffer_data7, GL_STATIC_DRAW);

	static GLfloat color_buffer_data8[36];
	for (int i = 0; i < 12; i++)
	{
		color_buffer_data8[i * 3 + 0] = 1.000f;
		color_buffer_data8[i * 3 + 1] = 1.000f;
		color_buffer_data8[i * 3 + 2] = 1.000f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data8), color_buffer_data8, GL_STATIC_DRAW);
	//Yellow Color (8)
	static const GLfloat YELLOW_color_buffer[] = {
		1.000f, 1.000f, 0.000f, //color of vertex 0
		1.000f, 1.000f, 0.000f, //color of vertex 1
		1.000f, 1.000f, 0.000f, //color of vertex 2
		1.000f, 1.000f, 0.000f, //color of vertex 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_YELLOWCOLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(YELLOW_color_buffer), YELLOW_color_buffer, GL_STATIC_DRAW);

}

void Assignment1::Update(double dt)
{

	if (Application::IsKeyPressed(VK_SPACE))
	{
		rotateAngle += (float)(10 * 3);
		if (rotateAngle > 90)
		{
			rotateAngle = 0;
		}
		translateX += (float)(10 * dt);
		if (translateX > 65){
			translateX = 0;
		}
		scaleAll += (float)(2 * dt);
		if (scaleAll > 7)
		{
			scaleAll = 1;
		}
	}
}

void Assignment1::Render()
{
	// Clear color buffer & depth every frame
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
	view.SetToIdentity(); // no need camera for now, set it at World's origin
	projection.SetToOrtho(-40, +40, -30, +30, -10, +10); // Our world is a cube defined by these boundaries
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	////////////////////This Section Places the Objects////////////////////
	//Ground();
	{
		scale.SetToScale(50, 50, 50);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-40, -48, -1);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_RECTANGLE]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// Draw the Rectangle
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		scale.SetToScale(50, 50, 50);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(-40, -60, -0);
		model = translate * rotate * scale;
		MVP = projection * view * model;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// Draw the Rectangle
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	}
/////////////////////////////////////////////////////////////////////////////////
	//Mountains();
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-40, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3); 

	
	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-36, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-32, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//Mountains();
	scale.SetToScale(8, 8, 8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-30, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	scale.SetToScale(7, 7, 7);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-25, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-18,-9 , -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(9, 9, 9);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-16, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);


	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-3, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(7, 7, 7);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(3, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(4, 4, 4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(12, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	scale.SetToScale(8, 8, 8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(17, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(28, -9, -2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Tower HP bar
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(29, -23, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	//till here 

	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(29, -23, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//till here 
/////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Tower 1
	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(8, -20, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//till here 

	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(62, 0, 0, 1);
	translate.SetToTranslation(11, -6, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//till here 

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(62, 0, 0, 1);
	translate.SetToTranslation(11, -6, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//till here 

	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(16, -19, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//till here 


	scale.SetToScale(6, 2, 6);
	rotate.SetToRotation(225, 0, rotateAngle, 1);
	translate.SetToTranslation(10, -2.5, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	scale.SetToScale(6, 6, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(14, 0, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
	//till here 
////////////////////////////////////////////////////////////////////////////////////////////////////
	//Tower 2
	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(28, -20, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//till here 

	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(35, -19, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	//till here 

	scale.SetToScale(6, 6, 6);
	rotate.SetToRotation(90, 0, 0, 1);
	translate.SetToTranslation(38, -19, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(33, -2, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TOWER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(180 , 0, 0, 1);
	translate.SetToTranslation(37, -10, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(1.5, 1.5, 1.5);
	rotate.SetToRotation(180, 0, 0, 1);
	translate.SetToTranslation(35.5, -11, 3);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_YELLOWCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(35.1, -10, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(31, -10, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

/////////////////////////////////////////////////////////////////////////
	//Stickman()
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-25, -15, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_STICKMAN]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_REDCOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_LINE_LOOP, 0, 20);


	scale.SetToScale(2, 2, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-25, -13, 5);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_CIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
	//till here 

	//Magic arrows
	scale.SetToScale(1, 1, 6);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, -15.5, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	scale.SetToScale(1, 1, 6);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(translateX, -14, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	scale.SetToScale(1, 1, 6);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, -13.5, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_RECTANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	scale.SetToScale(1, 1, 6);
	rotate.SetToRotation(270, 0, 0, 1);
	translate.SetToTranslation(translateX, -12, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_MOUNTAINS]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_BLUECOLOR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//Clouds

	scale.SetToScale(3,3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-7, 15, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
	//till here 

	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-10, 15, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
	//till here 

	scale.SetToScale(3, 3, 0);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-4, 15, 4);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); // update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_WHITECIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Draw the Triangles
	glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
	//till here 


 
	/*---------------------------------------------------------------------------------------------------------*/
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

}

void Assignment1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteBuffers(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}