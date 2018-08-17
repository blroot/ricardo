#include "stdafx.h"
#include "Mesh.h"


ricardo::Mesh::Mesh(vec3 center, std::string filename) {
	this->center = center;
	this->filename = filename;
}

void ricardo::Mesh::setTransforms(mat4 transform) {
	this->transforms = transform;
}

std::string & ricardo::Mesh::getFilename()
{
	return this->filename;
}

mat4& ricardo::Mesh::getTransforms() {
	return this->transforms;
}

ricardo::Mesh::~Mesh() {
}
