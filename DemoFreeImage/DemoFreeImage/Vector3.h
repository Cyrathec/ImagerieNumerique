#pragma once
#include <math.h>

namespace Vector {
	class Vector3 {
		
	public:
		float norm;

		float x;
		float y;
		float z;

		Vector3 Normalize();
		Vector3 VectorialProduct(Vector3 vector);
		Vector3 ReflectVector(Vector3 normal);
		float ScalaireProduct(Vector3 vector);
		void CalcNorm();

		Vector3();
		Vector3(const Vector3& vector);
		Vector3(float x, float y, float z);
	};
}