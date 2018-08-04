#include "stdafx.h"
#include "Scene.h"
#include <iostream>

using namespace ricardo;

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

void ricardo::Scene::addObject(Object * object)
{
	this->objects.push_back(object);
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

std::vector<Object*>& ricardo::Scene::getObjects()
{
	return this->objects;
}

std::vector<WORD> ricardo::Scene::getIndices()
{
	return this->indices;
}

std::vector<InfoVertex> ricardo::Scene::getVertices()
{
	return this->vertices;
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
