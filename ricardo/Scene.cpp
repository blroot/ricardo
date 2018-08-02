#include "stdafx.h"
#include "Scene.h"

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

ricardo::graphics_apis & ricardo::Scene::getGraphicsAPI()
{
	return graphic_api;
}
