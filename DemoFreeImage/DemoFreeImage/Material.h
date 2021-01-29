#pragma once

class Material
{
public:
	Color color;
	Color BlinnPhong();
};

typedef struct
{
	int r;
	int g;
	int b;
}Color;