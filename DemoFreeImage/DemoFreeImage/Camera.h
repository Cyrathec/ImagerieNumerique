#pragma once
#include "GameObject.h"

class Camera : public GameObject {
public:

	float focale = 1.0f;
	float nearplane = 0.1f;
	float farplane = 100.0f;

	int reswidth = 640; // Width of image resolution
	int resheigth = 480; // Height of image resolution

	float imgwidth = 2.0f; // Width of plan at focale

};