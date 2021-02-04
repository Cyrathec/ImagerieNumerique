#pragma once

class Material
{
public:
	int color;
	void BlinnPhong();
};

typedef struct
{
	int r;
	int g;
	int b;
}Color;