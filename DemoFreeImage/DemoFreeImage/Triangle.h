#pragma once
#include "D3Object.h"

class Triangle : public D3Object
{
public:
	Vector::Vector3 normale;

	Vector::Vector3 points[3]; //valeur relative à la position du triangle

	Vector::Vector3 CalcNormale();

	Triangle();
	Triangle(Vector::Vector3 p1, Vector::Vector3 p2, Vector::Vector3 p3);
	Triangle(Vector::Vector3 pts[3]);
};