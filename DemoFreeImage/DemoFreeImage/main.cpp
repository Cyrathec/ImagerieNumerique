#include <iostream>

#include "FreeImage.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plan.h"
#include "Light.h"
#include "Ray.h"
#include "Triangle.h"

Scene * createScene();
std::vector<std::vector<bool>> intersections(Scene* scene);

int main(int argc, char** argv)
{
	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(640, 480, 32);

	Scene * scene = createScene();
	std::vector<std::vector<bool>> pixels = intersections(scene);

	if (pixels.size() == 0)
	{
		return 1;
	}

	color.rgbRed = 0;
	color.rgbGreen = 125;
	color.rgbBlue = 0;

	for (size_t i = 0; i < 640; i++)
	{

		for (size_t j = 0; j < 480; j++)
		{

			if (pixels[j][i])
			{
				color.rgbRed = 255;
				color.rgbGreen = 255;
				color.rgbBlue = 255;
			}
			else
			{
				color.rgbRed = 0;
				color.rgbGreen = 0;
				color.rgbBlue = 0;
			}

			FreeImage_SetPixelColor(image, i, j, &color);
		}
	}

	FreeImage_Save(FIF_BMP, image, "out.bmp");

	return EXIT_SUCCESS;
}

Scene * createScene()
{
	Scene * scene = new Scene();
	// For now the camera look toward (1, 1, -1)
	// Code are made for that below

	// This is made for simplicity but we should search for all
	Camera * camera = scene->GetCameras().at(0);
	if (camera == nullptr)
	{
		delete camera;
		return nullptr;
	}

	// Creating the focale plan
	Plan * planfocale = new Plan();
	planfocale->position = Vector::Vector3(camera->position.x, camera->position.y, camera->position.z + camera->direction.z * camera->focal);
	planfocale->width = camera->focalwidth;
	planfocale->height = (planfocale->width * camera->resheigth) / camera->reswidth;
	scene->scene.push_back(planfocale);

	// Creating a sphere
	Sphere * sphere = new Sphere();
	sphere->position = Vector::Vector3(camera->position.x, camera->position.y, camera->position.z + camera->direction.z * camera->focal);
	sphere->range = 0.5f;
	scene->scene.push_back(sphere);

	// Creating a triangle
	Triangle * triangle = new Triangle(Vector::Vector3(-1.0f, 0.75f, 0.0f), Vector::Vector3(0.0f, -0.75f, 0.0f), Vector::Vector3(1.0f, 0.75f, 0.0f));
	triangle->position.z = -1.0f;

	return scene;
}

std::vector<std::vector<bool>> intersections(Scene * scene)
{

	std::vector<Camera*>	cameras	= scene->GetCameras();
	std::vector<Light*>		lights	= scene->GetLights();
	std::vector<Plan*>		plans	= scene->GetPlans();
	std::vector<Sphere*>	spheres	= scene->GetSpheres();

	if (cameras.size() == 0 || spheres.size() == 0 || plans.size() == 0 || lights.size() == 0)
	{
		std::vector<std::vector<bool>> tmp;
		printf("size %d\n", tmp.size());
		tmp.resize(0);
		return tmp;
	}

	Camera	*	camera	= cameras.at(0);
	Light	*	light	= lights.at(0);
	Plan	*	plan	= plans.at(0);

	if (camera == nullptr || spheres.at(0) == nullptr || plan == nullptr || light == nullptr)
	{
		std::vector<std::vector<bool>> tmp;
		printf("size %d\n", tmp.size());
		tmp.resize(0);
		return tmp;
	}

	std::vector<std::vector<bool>> pixels;
	pixels.resize(camera->resheigth);

	for (int i = 0; i < camera->resheigth; i++)
	{
		pixels.at(i).resize(camera->reswidth);
		for (int j = 0; j < camera->reswidth; j++)
		{
			pixels.at(i).at(j) = false;
		}
	}

	float y = plan->position.y - plan->height / 2;
	float x = plan->position.x - plan->width / 2;

	for (int i = 0; i < camera->resheigth; i++)
	{
		for (int j = 0; j < camera->reswidth; j++)
		{
			Vector::Vector3 dir = Vector::Vector3(x - camera->position.x, y - camera->position.y, plan->position.z - camera->position.z).Normalize();

			float scale = -camera->nearplane / dir.z;
			Vector::Vector3 start = Vector::Vector3(dir.x * scale, dir.y * scale, dir.z * scale);

			scale = -camera->farplane / dir.z;
			Vector::Vector3 finish = Vector::Vector3(dir.x * scale, dir.y * scale, dir.z * scale);

			float pixelstep = 1.0f / (camera->farplane * 10);
			if (camera->nearplane != 0.0f)
			{
				float pixelstep = camera->nearplane / (camera->farplane * 10);
			}

			pixelstep = 0.1f; // DEBUG

			int test = rayLaunch(start, finish, scene, pixelstep);

			if (test >= 0)
			{
				pixels.at(i).at(j) = true;
			}
			x += plan->width / camera->reswidth;
		}
		x = plan->position.x - plan->width / 2;
		y += plan->height / camera->resheigth;
	}

	return pixels;
}