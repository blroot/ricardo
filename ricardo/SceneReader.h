#pragma once

#include <string>
#include <sstream>
#include "Scene.h"
#include "vec3.h"

using namespace math;

namespace ricardo {

	class SceneReader {
	public:
		SceneReader(const char* file);
		Scene read();
		virtual ~SceneReader();
	private:
		bool readvals(std::stringstream &s, const int numvals, float* values);
		const char* file;
		//color ambient;
		//color diffuse;
		//color specular;
		//color emission;
		//vec3 attenuation;
		std::vector<vec3> vertex_buffer;
	};

}