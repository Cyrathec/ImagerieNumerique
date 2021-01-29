#pragma once
#include <vector>
#include "Camera.h"
#include "GameObject.h"

class Scene
{
public:
	std::vector<GameObject*> scene;
	std::vector<Camera*> GetCameras();
	Scene();
	~Scene();
};