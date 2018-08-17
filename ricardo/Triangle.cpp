#include "stdafx.h"
#include "Triangle.h"

ricardo::Triangle::Triangle(vec3 indices)
{
	this->indices = indices;
	//this->normal = (this->B - this->A).cross(this->C - this->A).normalize();
}

ricardo::Triangle::~Triangle()
{
}

void ricardo::Triangle::setTransforms(mat4 transform)
{
	this->transforms = transform;
}

vec3 & ricardo::Triangle::getIndices()
{
	return this->indices;
}

mat4 & ricardo::Triangle::getTransforms()
{
	return this->transforms;
}
