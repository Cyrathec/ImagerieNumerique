#pragma once
#include "GameObject.h"

class Light : public GameObject {
public:

	int type = 0; // 0 = Directionnal 1 = Spot 2 = Point
	float range = -1.0f; // = -1 with Directionnal type
	float intensity = 1.0f;

};