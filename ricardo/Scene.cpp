#include "stdafx.h"
#include "Scene.h"
#include <iostream>

using namespace ricardo;
using namespace DirectX;

ricardo::Scene::Scene()
{
}

void ricardo::Scene::setResolution(int width, int height)
{
	this->resolution_width = width;
	this->resolution_height = height;
}

void ricardo::Scene::setGraphic_api(graphics_apis api)
{
	this->graphic_api = api;
}

void ricardo::Scene::addTriangle(Triangle * triangle)
{
	this->triangles.push_back(triangle);
}

void ricardo::Scene::addMesh(Mesh * mesh)
{
	this->meshes.push_back(mesh);
}

ricardo::graphics_apis& ricardo::Scene::getGraphicsAPI()
{
	return graphic_api;
}

int & ricardo::Scene::getResolution_width()
{
	return this->resolution_width;
}

int & ricardo::Scene::getResolution_height()
{
	return this->resolution_height;
}

std::vector<Triangle*>& ricardo::Scene::getTriangles()
{
	return this->triangles;
}

std::vector<Mesh*>& ricardo::Scene::getMeshes()
{
	return this->meshes;
}

std::vector<WORD> ricardo::Scene::getIndices()
{
	return this->indices;
}

void ricardo::Scene::addIndex(WORD index)
{
	this->indices.push_back(index);
}

void ricardo::Scene::addVertex(vec3 vertex, vec4 color)
{
	InfoVertex arr = { vertex, color };
	this->vertices.push_back(arr);
}

void ricardo::Scene::setCameraEye(vec3 eye)
{
	this->cameraEye = eye;
}

void ricardo::Scene::setCameraLookAt(vec3 lookAt)
{
	this->cameraLookAt = lookAt;
}

void ricardo::Scene::setCameraRotationScaler(float rotationScaler)
{
	this->cameraRotationScaler = rotationScaler;
}

void ricardo::Scene::setCameraMoveScaler(float moveScaler)
{
	this->cameraMoveScaler = moveScaler;
}

void ricardo::Scene::setCameraVMin(vec3 vMin)
{
	this->cameraVMin = vMin;
}

void ricardo::Scene::setCameraVMax(vec3 vMax)
{
	this->cameraVMax = vMax;
}

vec3 & ricardo::Scene::getCameraEye()
{
	return this->cameraEye;
}

vec3 & ricardo::Scene::getCameraLookAt()
{
	return this->cameraLookAt;
}

float & ricardo::Scene::getCameraRotationScaler()
{
	return this->cameraRotationScaler;
}

float & ricardo::Scene::getCameraMoveScaler()
{
	return this->cameraMoveScaler;
}

vec3 & ricardo::Scene::getCameraVMin()
{
	return this->cameraVMin;
}

vec3 & ricardo::Scene::getCameraVMax()
{
	return this->cameraVMax;
}
