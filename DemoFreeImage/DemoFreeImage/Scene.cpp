#include "Scene.h"
#include "Camera.h"
#include "Light.h"

Scene::Scene() {
	scene.push_back(Camera());
	//scene.back().position = Vector::Vector3(0.0f, 0.0f, 0.0f);
	//scene.back().rotation = Vector::Vector3(0.0f, 180.0f, 0.0f); // regarde vers (0, 0, -1)
	scene.push_back(Light());
	//scene.back().position = Vector::Vector3(0.0f, 100.0f, 0.0f);
	//scene.back().rotation = Vector::Vector3(315.0f, 135.0f, 0.0f);
}