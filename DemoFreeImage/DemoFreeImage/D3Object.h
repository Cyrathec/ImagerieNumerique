#pragma once
#include "GameObject.h"
#include "Material.h"

class D3Object : public GameObject
{
public:
	Material * material = NULL; // Becareful there is no destructor to delete the material
	D3Object(std::string type);
};