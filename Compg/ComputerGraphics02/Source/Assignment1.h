#ifndef ASSIGNMENT_1_H
#define ASSIGNMENT_1_H
#include "Scene.h"
#include "MyMath.h"

class Assignment1 : public Scene
{
public:
	Assignment1();
	~Assignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void Bufferdata();
	void COLORS();
	enum GEOMETRY_TYPE
	{
		GEO_RECTANGLE=0,
		GEO_MOUNTAINS,
		GEO_TOWER,
		GEO_ICONS,
		GEO_CIRCLE,
		GEO_STICKMAN,
		GEO_BLUECOLOR,
		GEO_WHITECOLOR,
		GEO_REDCOLOR,
		GEO_YELLOWCOLOR,
		GEO_WHITECIRCLE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
	unsigned m_parameters[U_TOTAL];
private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	float rotateAngle;
	float translateX;
	float scaleAll;
	float triangle1start;
};
#endif