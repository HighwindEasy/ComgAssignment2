#ifndef _MATERIAL_H
#define _MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f,float  b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; 
		this->g = g;
		this->b = b;
	}
};

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	Material()
	{
		kAmbient.Set(0.0f, 0.0f, 0.0f);
		kDiffuse.Set(0.0f, 0.0f, 0.0f);
		kSpecular.Set(0.0f, 0.0f, 0.0f);
		float kShininess = 0.0f;
	}
};

#endif