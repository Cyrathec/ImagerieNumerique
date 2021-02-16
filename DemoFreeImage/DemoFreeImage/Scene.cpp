#include "Scene.h"
#include "Camera.h"
#include "Light.h"

std::vector<Camera*> Scene::GetCameras()
{
	std::vector<Camera*> cameras;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Camera") {
			cameras.push_back(static_cast<Camera*>(scene.at(i)));
		}
	}

	return cameras;
}

std::vector<Light*> Scene::GetLights()
{
	std::vector<Light*> lights;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Light") {
			lights.push_back(static_cast<Light*>(scene.at(i)));
		}
	}

	return lights;
}

std::vector<D3Object*> Scene::GetD3Objects()
{
	std::vector<D3Object*> objects;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Plan" || scene.at(i)->type == "Sphere") {
			objects.push_back(static_cast<D3Object*>(scene.at(i)));
		}
	}

	return objects;
}

std::vector<Plan*> Scene::GetPlans()
{
	std::vector<Plan*> plans;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Plan") {
			plans.push_back(static_cast<Plan*>(scene.at(i)));
		}
	}

	return plans;
}

std::vector<Sphere*> Scene::GetSpheres()
{
	std::vector<Sphere*> spheres;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Sphere") {
			spheres.push_back(static_cast<Sphere*>(scene.at(i)));
		}
	}

	return spheres;
}

std::vector<Triangle*> Scene::GetTriangle()
{
	std::vector<Triangle*> triangles;

	for (size_t i = 0; i < scene.size(); i++)
	{
		if (scene.at(i)->type == "Triangle") {
			triangles.push_back(static_cast<Triangle*>(scene.at(i)));
		}
	}

	return triangles;
}

Scene::Scene()
{
	scene.push_back(new Camera());
	scene.back()->direction.z = -1.0f;
	scene.push_back(new Light());
	scene.back()->position.y = 100.0f;
}

Scene::~Scene()
{
	for (size_t i = 0; i < scene.size(); i++)
	{
		delete scene.at(i);
	}
	scene.clear();
}
