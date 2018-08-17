#pragma once

#include "vec3.h"
#include "mat4.h"

using namespace math;

namespace ricardo {

	class Triangle {
	public:
		Triangle(vec3 indices);
		virtual ~Triangle();
		void setTransforms(mat4 transform);
		//void setAmbient(vec4 color);
		//vec4& getAmbient();
		//vec3 getNormal();
		vec3& getIndices();
		mat4& getTransforms();
	private:
		//vec3 normal;
		vec3 indices;
		//vec4 ambient;
		mat4 transforms;
	};
}