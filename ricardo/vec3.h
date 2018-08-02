/*
 * vec3.h

 *
 *  Created on: Jul 4, 2017
 *      Author: blroot
 */

#pragma once

#include "vec4.h"
#include <ostream>

namespace math {

	struct vec4;

	struct vec3 {

		float x;
		float y;
		float z;

		vec3();
		vec3(float x, float y, float z);
		vec3(const vec4& fourvec);

		float dot(vec3 vector) const;
		bool operator==(const vec3 &vector);
		bool operator!=(const vec3 &vector);
		vec3 operator+(vec3 right);
		vec3& operator+=(vec3 right);
		vec3 operator-(vec3 right);
		vec3 operator*(float scalar);
		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		friend vec3 operator*(float scalar, const vec3& vector);
		friend vec3 operator*(int scalar, const vec3& vector);
		vec3 cross(vec3 vector) const;
		float norm() const;
		vec3 normalize() const;
	};

}
