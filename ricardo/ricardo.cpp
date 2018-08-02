// ricardo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SceneReader.h"
#include "Scene.h"
#include <iostream>
#include "Renderer.h"

using namespace ricardo;

void printHelp()
{
	std::cout << "Usage: ./ricardo <scene file>" << std::endl;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printHelp();
		return 1;
	}

	SceneReader scene_reader = SceneReader(argv[1]);
	Scene scene = scene_reader.read();

	// Main loop
	Renderer<DX11Handler> *renderer = new DX11Handler();
	renderer->render();
	renderer->otro();

    return 0;
}
