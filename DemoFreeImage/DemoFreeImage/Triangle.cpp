#include "Triangle.h"

Vector::Vector3 Triangle::CalcNormale()
{
	Vector::Vector3 p1p2(Vector::Vector3(points[1].x - points[0].x, points[1].y - points[0].y, points[1].z - points[0].z));
	Vector::Vector3 p1p3(Vector::Vector3(points[2].x - points[0].x, points[2].y - points[0].y, points[2].z - points[0].z));

	normale = Vector::Vector3(p1p2);
	normale = normale.VectorialProduct(p1p3);
	normale = normale.Normalize();
	normale.ZeroSignCorrection();
	return normale;
}

Triangle::Triangle() : D3Object("Triangle")
{
	for (size_t i = 0; i < 3; i++)
	{
		points[i] = Vector::Vector3(0, 0, 0);
	}
	CalcNormale();
}

Triangle::Triangle(Vector::Vector3 p1, Vector::Vector3 p2, Vector::Vector3 p3) : D3Object("Triangle")
{
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	CalcNormale();
}

Triangle::Triangle(Vector::Vector3 pts[3]) : D3Object("Triangle")
{
	for (size_t i = 0; i < 3; i++)
	{
		points[i] = pts[i];
	}
	CalcNormale();
}
