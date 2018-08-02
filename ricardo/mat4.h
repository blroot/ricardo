/*
 * mat4.h
 *
 *  Created on: Jul 8, 2017
 *      Author: blroot
 */

#pragma once

#include "vec3.h"
#include "vec4.h"

const double pi = 3.14159265;

namespace math {

	struct mat4 {

		float elements[16];

		mat4();
		mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
		mat4(float diagonal);

		mat4 rotate(const float degrees, const vec3& axis);
		mat4 scale(const float &sx, const float &sy, const float &sz);
		mat4 translate(const float &tx, const float &ty, const float &tz);
		mat4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up);

		mat4 transpose();
		float determinant();
		mat4 inverse();

		mat4 operator*(mat4 matrix);
		mat4 operator*(float scalar);
		friend mat4 operator*(float scalar, const mat4& matrix);
		friend mat4 operator*(int scalar, const mat4& matrix);
		friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
		vec3 operator*(const vec3& vector);
		vec4 operator*(const vec4& vector);
		mat4& operator=(mat4 matrix);
		bool operator==(mat4 matrix);
		bool operator!=(mat4 matrix);
	};

}
