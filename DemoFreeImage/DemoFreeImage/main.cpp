#include <iostream>

#include "FreeImage.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plan.h"
#include "Light.h"
#include "Ray.h"

Scene * createScene();
bool ** interTestMethode(Scene * scene); // test the intersection between the focal plan & the sphere

int main(int argc, char** argv)
{
	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(640, 480, 32);

	Scene * scene = createScene();
	bool ** pixels = interTestMethode(scene);

	if (pixels == nullptr)
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
	// For now the camera look toward (0, 0, -1)
	// Code are made for that below

	// This is made for simplicity but we should search for all
	Camera * camera = scene->GetCameras().at(0);
	if (camera == nullptr)
	{
		delete camera;
		return nullptr;
	}

	Plan * planfocale = new Plan();
	planfocale->position = Vector::Vector3(camera->position.x, camera->position.y, camera->position.z + camera->direction.z * camera->focal);
	planfocale->width = camera->focalwidth;
	planfocale->height = (planfocale->width * camera->resheigth) / camera->reswidth;
	scene->scene.push_back(planfocale);

	Sphere * sphere = new Sphere();
	sphere->position = Vector::Vector3(camera->position.x, camera->position.y, camera->position.z + camera->direction.z * camera->focal);
	sphere->range = 0.5f;
	scene->scene.push_back(sphere);

	return scene;
}

// TODO: Fonction lancer de rayon (pos depart, pos arrivee, scene*, pas) retourne l'id de l'object touché à créer
bool ** interTestMethode(Scene * scene)
{
	Camera	* camera	= nullptr;
	Plan	* plan		= nullptr;
	Sphere	* sphere	= nullptr;
	Light	* light		= nullptr;

	for (size_t i = 0; i < scene->scene.size(); i++)
	{
		if (scene->scene.at(i)->type == "Camera")
		{
			camera = static_cast<Camera*>(scene->scene.at(i));
		}
		if (scene->scene.at(i)->type == "Plan")
		{
			plan = static_cast<Plan*>(scene->scene.at(i));
		}
		if (scene->scene.at(i)->type == "Sphere")
		{
			sphere = static_cast<Sphere*>(scene->scene.at(i));
		}
		if (scene->scene.at(i)->type == "Light")
		{
			light = static_cast<Light*>(scene->scene.at(i));
		}
	}

	if (camera == nullptr || sphere == nullptr || plan == nullptr || light == nullptr)
	{
		return nullptr;
	}

	bool ** pixels = static_cast<bool**>(malloc(camera->resheigth * sizeof(bool*)));

	if (pixels == nullptr) {
		return nullptr;
	}

	for (int i = 0; i < camera->resheigth; i++)
	{
		pixels[i] = static_cast<bool*>(malloc(camera->reswidth * sizeof(bool)));

		if (pixels[i] == nullptr) {
			return nullptr;
		}

		for (int j = 0; j < camera->reswidth; j++)
		{
			pixels[i][j] = false;
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
				pixels[i][j] = true;
			}
			x += plan->width / camera->reswidth;
			break;
		}
		break;
		x = plan->position.x - plan->width / 2;
		y += plan->height / camera->resheigth;
	}

	return pixels;
}