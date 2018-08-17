#pragma once

#include <string>
#include "vec3.h"
#include "mat4.h"

using namespace math;

namespace ricardo {

	class Mesh {
	public:
		Mesh(vec3 center, std::string filename);
		void setTransforms(mat4 transform);
		std::string& getFilename();
		mat4& getTransforms();
		~Mesh();
	private:
		vec3 center;
		std::string filename;
		mat4 transforms;
	};	
}
