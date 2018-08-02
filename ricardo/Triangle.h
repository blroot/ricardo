#pragma once

#include "Object.h"
#include "vec3.h"

using namespace math;

namespace ricardo {

	class Triangle : public Object {
	public:
		Triangle(vec3 A, vec3 B, vec3 C);
		virtual ~Triangle();
		void applyTransform();
		vec3 getNormal();
		vec3& getA();
		vec3& getC();
		vec3& getB();
	private:
		vec3 normal;
		vec3 A;
		vec3 B;
		vec3 C;
	};
}