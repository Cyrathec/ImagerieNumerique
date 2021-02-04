#include "GameObject.h"

static int sindex = 0;

GameObject::GameObject(std::string type)
{
	index = sindex;
	this->type = type;
	sindex++;
}