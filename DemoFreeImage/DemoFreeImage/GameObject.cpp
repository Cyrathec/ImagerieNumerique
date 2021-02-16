#include "GameObject.h"

static int sindex = 0;

GameObject::GameObject(std::string type)
{
	position = Vector::Vector3(0.0f, 0.0f, 0.0f);
	direction = Vector::Vector3(1.0f, 1.0f, 1.0f);
	index = sindex;
	this->type = type;
	sindex++;
}