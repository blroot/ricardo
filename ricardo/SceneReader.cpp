#include "stdafx.h"
#include "SceneReader.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include "mat4.h"
#include "Triangle.h"

using namespace std;

ricardo::SceneReader::SceneReader(const char * file)
{
	this->file = file;
}

ricardo::Scene ricardo::SceneReader::read()
{
	Scene scene = Scene();
	std::stack<mat4> transfstack;

	ifstream infile;
	string line, command;

	infile.open(this->file);

	if (infile.is_open()) {

		// Initially push identity into transformation stack
		transfstack.push(mat4(1.0f));

		getline(infile, line);

		while (infile) {

			// Wipe blank and commented lines
			if ((line.find_first_not_of(" \t\r\n") != string::npos)
				&& (line[0] != '#')) {

				float values[10];
				std::string filename;
				bool valid_input;

				stringstream s(line);
				s >> command;

				if (command == "mode") {
					valid_input = this->readvals(s, 2, values);

					if (valid_input) {

						scene.setResolution(values[0], values[1]);
						std::cout << "Setting resolution to : " << values[0] << "x" << values[1] << std::endl;

						scene.setGraphic_api(graphics_apis::DirectX11);
						std::cout << "Setting graphics API to : " << "DirectX11" << std::endl;
					}
				}
				else if (command == "vertex") {
					valid_input = this->readvals(s, 3, values);

					if (valid_input) {

						vec3 vertex = vec3(values[0], values[1], values[2]);
						this->vertex_buffer.push_back(vertex);
						std::cout << "Adding vertex to buffer with coordinates: " << vertex << std::endl;
					}
				} 
				else if (command == "tri") {
					valid_input = this->readvals(s, 3, values);

					if (valid_input) {

						Triangle *triangle = new Triangle(vertex_buffer[values[0]], vertex_buffer[values[1]], vertex_buffer[values[2]]);

						//triangle->getMaterials().setAmbient(this->ambient);
						//triangle->getMaterials().setDiffuse(this->diffuse);
						//triangle->getMaterials().setSpecular(this->specular);
						//triangle->getMaterials().setShininess(this->shininess);
						//triangle->getMaterials().setEmission(this->emission);
						//triangle->setTransform(transfstack.top());
						triangle->applyTransform();
						scene.addObject(triangle);

						std::cout << "Adding triangle to scene with vertices: " << vertex_buffer[values[0]]
							<< " " << vertex_buffer[values[1]] << " " << vertex_buffer[values[2]] << std::endl;
						std::cout << "Setting triangle transform:" << transfstack.top() << std::endl;
						//std::cout << "Setting triangle ambient to: " << this->ambient << std::endl;
						//std::cout << "Setting triangle diffuse to: " << this->diffuse << std::endl;
						//std::cout << "Setting triangle specular to: " << this->specular << std::endl;
						//std::cout << "Setting triangle shininess to: " << this->shininess << std::endl;
					}
				}
				else if (command == "pushTransform") {

					transfstack.push(transfstack.top());
					std::cout << "Pushing current transform to the stack : " << transfstack.top() << std::endl;

				}
				else if (command == "popTransform") {

					if (transfstack.size() <= 1) {

						cerr << "Stack has no elements.  Cannot Pop\n";
					}
					else {

						transfstack.pop();
						std::cout << "Popping current transform from the stack" << std::endl;

					}

				}
				else if (command == "translate") {

					valid_input = this->readvals(s, 3, values);

					if (valid_input) {

						mat4 translation_matrix = mat4().translate(values[0], values[1], values[2]);
						std::cout << "Translation Matrix -> " << translation_matrix << std::endl;
						mat4 &top_matrix = transfstack.top();
						top_matrix = top_matrix * translation_matrix;
						std::cout << "Applying transform -> Translating: " << vec3(values[0], values[1], values[2]) << std::endl;
					}

				}
				else if (command == "scale") {

					valid_input = this->readvals(s, 3, values);

					if (valid_input) {

						mat4 scale_matrix = mat4().scale(values[0], values[1], values[2]);
						std::cout << "Scale Matrix -> " << scale_matrix << std::endl;
						mat4 &top_matrix = transfstack.top();
						top_matrix = top_matrix * scale_matrix;
						std::cout << "Applying transform -> Scaling: " << vec3(values[0], values[1], values[2]) << std::endl;
					}

				}
				else if (command == "rotate") {

					valid_input = this->readvals(s, 4, values);

					if (valid_input) {

						vec3 axis = vec3(values[0], values[1], values[2]);

						mat4 rotation_matrix = mat4().rotate(values[3], axis);
						std::cout << "Rotation Matrix -> " << rotation_matrix << std::endl;
						mat4 &top_matrix = transfstack.top();
						top_matrix = top_matrix * rotation_matrix;
						std::cout << "Applying transform -> Rotating: axis:" << axis << " angle:" << values[3] << std::endl;
					}

				}
				std::cout << "==================================" << std::endl;
			}
			// Get next line
			getline(infile, line);
		}
	} else {
		std::cout << "Error reading scene file" << std::endl;
		exit(1);
	}

	return scene;
}

ricardo::SceneReader::~SceneReader()
{
}

bool ricardo::SceneReader::readvals(std::stringstream & s, const int numvals, float * values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];

		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}
