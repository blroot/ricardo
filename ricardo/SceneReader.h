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
		bool readvals(std::stringstream & s, const int float_numvals, float * values, const int str_numvals, std::string * stringvalues);
		const char* file;
		vec4 ambient;
		//color diffuse;
		//color specular;
		//color emission;
		//vec3 attenuation;
		std::vector<vec3> vertex_buffer;
	};

}