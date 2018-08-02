#pragma once

#include "mat4.h"

using namespace math;

namespace ricardo {

	class Object {
		public:
			Object();
			virtual ~Object();
			virtual vec3 getNormal() = 0;
			void setTransform(mat4 transform);
			virtual void applyTransform() = 0;
			//Materials& getMaterials();
			mat4& getTransform();
	protected:
		//Materials materials;
		mat4 transform;

	};
}