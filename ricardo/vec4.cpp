/*
 * vec4.cpp
 *
 *  Created on: Aug 10, 2017
 *      Author: blroot
 */

#include "stdafx.h"
#include "vec4.h"

namespace math {

	vec4::vec4() {

		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	vec4::vec4(float x, float y, float z, float w) {

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4::vec4(const vec3 &threevec, float w) {

		this->x = threevec.x;
		this->y = threevec.y;
		this->z = threevec.z;
		this->w = w;
	}

	bool vec4::operator==(const vec4 &vector) {

		return this->x == vector.x && this->y == vector.y && this->z == vector.z && this->w == vector.w;
	}

	bool vec4::operator!=(const vec4 &vector) {

		return this->x == vector.x || this->y == vector.y || this->z == vector.z || this->w == vector.w;
	}

	vec4 vec4::operator+(vec4 right) {

		return vec4(this->x + right.x, this->y + right.y, this->z + right.z, this->w + right.w);
	}

	vec4& vec4::operator+=(vec4 right) {

		this->x = this->x + right.x;
		this->y = this->y + right.y;
		this->z = this->z + right.z;
		this->w = this->w + right.w;

		return *this;
	}

	vec4 vec4::operator-(vec4 right) {

		return vec4(this->x - right.x, this->y - right.y, this->z - right.z, this->w - right.w);
	}

	vec4 vec4::operator*(float scalar) {

		return vec4(scalar * this->x, scalar * this->y, scalar * this->z, scalar * this->w);
	}

	vec4 operator*(float scalar, const vec4 &vector) {

		return vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
	}

	vec4 operator*(int scalar, const vec4 &vector) {

		return vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
		stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}

} /* namespace superboy */
