#include "Scene.h"
#include "Camera.h"
#include "Light.h"

Scene::Scene()
{
	scene.push_back(new Camera());
	scene.back()->position = Vector::Vector3(0.0f, 0.0f, 0.0f);
	scene.back()->direction = Vector::Vector3(0.0f, 0.0f, -1.0f);
	scene.push_back(new Light());
	//scene.back().position = Vector::Vector3(0.0f, 100.0f, 0.0f);
	//scene.back().direction = Vector::Vector3(0.0f, 0.0f, 0.0f);
}

Scene::~Scene()
{
	for (size_t i = 0; i < scene.size(); i++)
	{
		delete scene.at(i);
	}
	scene.clear();
}
