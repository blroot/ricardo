#include "stdafx.h"
#include "Object.h"

ricardo::Object::Object()
{
}

ricardo::Object::~Object()
{
}

void ricardo::Object::setTransform(mat4 transform)
{
	this->transform = transform;
}

mat4 & ricardo::Object::getTransform()
{
	return this->transform;
}
