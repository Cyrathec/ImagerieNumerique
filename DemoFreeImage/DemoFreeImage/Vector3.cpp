#include "Vector3.h"

namespace Vector
{
	void Vector3::CalcNorm()
	{
		norm = sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}

	Vector3 Vector3::Normalize()
	{
		Vector3 normalized;
		CalcNorm();
		normalized.x = x / norm;
		normalized.y = y / norm;
		normalized.z = z / norm;
		return normalized;
	}

	Vector3 Vector3::VectorialProduct(Vector3 vector)
	{
		Vector3 product;
		product.x = y * vector.z - z * vector.y;
		product.y = z * vector.x - x * vector.z;
		product.z = x * vector.y - y * vector.x;
		return product;
	}

	Vector3 Vector3::ReflectVector(Vector3 normal)
	{
		Vector3 reflected;
		float scal = ScalaireProduct(normal);
		reflected.x = x - 2 * scal * normal.x;
		reflected.y = y - 2 * scal * normal.y;
		reflected.z = z - 2 * scal * normal.z;
		return reflected;
	}

	float Vector3::CalcDistance(Vector3 vector)
	{
		return sqrtf(	(vector.x - x) * (vector.x - x) +
						(vector.y - y) * (vector.y - y) +
						(vector.z - z) * (vector.z - z)
					);
	}

	float Vector3::ScalaireProduct(Vector3 vector)
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		CalcNorm();
	}

	Vector3::Vector3(const Vector3& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		CalcNorm();
	}

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		CalcNorm();
	}
}