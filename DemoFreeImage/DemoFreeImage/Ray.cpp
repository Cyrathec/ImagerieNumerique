#include "Ray.h"
#include "Plan.h"
#include "Light.h"
#include "Sphere.h"

int rayLaunch(Vector::Vector3 start, Vector::Vector3 finish, Scene * scene, float step)
{
	std::vector<Light*>		lights	= scene->GetLights();
	std::vector<Sphere*>	spheres	= scene->GetSpheres();

	Vector::Vector3 direction = Vector::Vector3(finish.x - start.x, finish.y - start.y, finish.z - start.z).Normalize();

	float distance = start.CalcDistance(finish);

	if (step == -1.0f)
	{
		step = distance * 10;
	}

	Vector::Vector3 raypos = start;

	for (float i = 0.0f; i <= distance; i += step)
	{
		for (size_t i = 0; i < spheres.size(); i++)
		{
			Sphere * sphere = static_cast<Sphere*>(spheres.at(i));
			if (sphere != nullptr)
			{
				if (sphere->position.CalcDistance(raypos) <= sphere->range + step / 100)
				{
					return sphere->index;
				}
			}
		}

		raypos.x += direction.x * step;
		raypos.y += direction.y * step;
		raypos.z += direction.z * step;
	}

	return -1;
}