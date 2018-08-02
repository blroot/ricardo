#include "stdafx.h"
#include "Triangle.h"

ricardo::Triangle::Triangle(vec3 A, vec3 B, vec3 C)
{
	this->A = A;
	this->B = B;
	this->C = C;

	//this->materials = Materials();
	this->normal = (this->B - this->A).cross(this->C - this->A).normalize();
}

ricardo::Triangle::~Triangle()
{
}

void ricardo::Triangle::applyTransform()
{
	// Apply transforms using homogeneous coordinates

	this->A = this->transform * vec4(this->A, 1.0f);
	this->B = this->transform * vec4(this->B, 1.0f);
	this->C = this->transform * vec4(this->C, 1.0f);

	this->normal = (this->B - this->A).cross(this->C - this->A).normalize();
}

vec3 ricardo::Triangle::getNormal()
{
	return this->normal;
}

vec3 & ricardo::Triangle::getA()
{
	return this->A;
}

vec3 & ricardo::Triangle::getC()
{
	return this->C;
}

vec3 & ricardo::Triangle::getB()
{
	return this->B;
}
