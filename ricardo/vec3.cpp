/*
 * vec3.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: blroot
 */

#include "stdafx.h"
#include "vec3.h"
#include "vec4.h"
#include <math.h>

namespace math {

	vec3::vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3::vec3(const vec4 &fourvec) {

		this->x = fourvec.x;
		this->y = fourvec.y;
		this->z = fourvec.z;
	}

	vec3 vec3::cross(vec3 vector) const {
		return vec3(this->y*vector.z - this->z*vector.y,
				    -(this->x*vector.z - this->z*vector.x),
					this->x*vector.y - this->y*vector.x);
	}

	float vec3::norm() const {
		return sqrt(x*x + y*y + z*z);
	}

	vec3 vec3::normalize() const {
		float norm = this->norm();
		return vec3(this->x/norm, this->y/norm, this->z/norm);
	}

	float vec3::dot(vec3 vector) const {
		return this->x * vector.x + this->y * vector.y + this->z * vector.z;
	}

	bool vec3::operator==(const vec3 &vector) {
		return this->x == vector.x && this->y == vector.y && this->z == vector.z;
	}

	bool vec3::operator!=(const vec3 &vector) {
		return this->x != vector.x || this->y != vector.y || this->z != vector.z;
	}

	vec3 vec3::operator+(vec3 right) {
		return vec3(this->x + right.x, this->y + right.y, this->z + right.z);
	}

	vec3& vec3::operator+=(vec3 right) {
		this->x = this->x + right.x;
		this->y = this->y + right.y;
		this->z = this->z + right.z;

		return *this;
	}

	vec3 vec3::operator-(vec3 right) {
		return vec3(this->x - right.x, this->y - right.y, this->z - right.z);
	}

	vec3 vec3::operator*(float scalar) {
		return vec3(scalar * this->x, scalar * this->y, scalar * this->z);
	}

	vec3 operator*(float scalar, const vec3 &vector) {
		return vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
	}

	vec3 operator*(int scalar, const vec3 &vector) {
		return vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}
}
