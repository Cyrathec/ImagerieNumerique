#pragma once
#include <string>
#include "Vector3.h"

class GameObject
{
public:
	static int		index;
	std::string		type;
	Vector::Vector3 position;
	Vector::Vector3 direction;
	GameObject(std::string type);
};