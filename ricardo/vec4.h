/*
 * vec4.h
 *
 *  Created on: Aug 10, 2017
 *      Author: blroot
 */

#pragma once

#include "vec3.h"
#include <ostream>

namespace math {

	struct vec3;

	struct vec4 {

		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(float x, float y, float z, float w);
		vec4(const vec3& threevec, float w);

		bool operator==(const vec4 &vector);
		bool operator!=(const vec4 &vector);
		vec4 operator+(vec4 right);
		vec4& operator+=(vec4 right);
		vec4 operator-(vec4 right);
		vec4 operator*(float scalar);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		friend vec4 operator*(float scalar, const vec4& vector);
		friend vec4 operator*(int scalar, const vec4& vector);

	};

} /* namespace superboy */
