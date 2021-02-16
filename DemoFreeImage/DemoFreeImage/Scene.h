#pragma once
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Plan.h"
#include "Sphere.h"
#include "Triangle.h"

class Scene
{
public:
	std::vector<GameObject*> scene;
	std::vector<Camera*> GetCameras();
	std::vector<Light*> GetLights();
	std::vector<D3Object*> GetD3Objects();
	std::vector<Plan*> GetPlans();
	std::vector<Sphere*> GetSpheres();
	std::vector<Triangle*> GetTriangle();
	Scene();
	~Scene();
};