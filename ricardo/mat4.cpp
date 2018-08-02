/*
 * mat4.cpp

 *
 *  Created on: Jul 8, 2017
 *      Author: blroot
 */

#include "stdafx.h"
#include "mat4.h"
#include <math.h>

namespace math {

	/*
	 * Note that matrix is in column order
	 */

	mat4::mat4() {

		for (int i = 0; i < 16; i++) {
			this->elements[i] = 0.0f;
		}
	}

	mat4::mat4(float diagonal) {

		for (int i = 0; i < 16; i++) {
			this->elements[i] = 0.0f;
		}

		elements[0] = diagonal;
		elements[5] = diagonal;
		elements[10] = diagonal;
		elements[15] = diagonal;
	}

	mat4::mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {

		elements[0] = a;
		elements[1] = e;
		elements[2] = i;
		elements[3] = m;
		elements[4] = b;
		elements[5] = f;
		elements[6] = j;
		elements[7] = n;
		elements[8] = c;
		elements[9] = g;
		elements[10] = k;
		elements[11] = o;
		elements[12] = d;
		elements[13] = h;
		elements[14] = l;
		elements[15] = p;
	}

	mat4 mat4::rotate(const float degrees, const vec3& axis)
	{
		mat4 resulting_matrix(1.0f);

		float radians = (pi/180)*degrees;
		float cosine = cos(radians);
		float sine = sin(radians);
		const float one_minus_cosine = 1.0f - cosine;

		const float x = axis.x;
		const float y = axis.y;
		const float z = axis.z;

		resulting_matrix.elements[0] = x * x * one_minus_cosine + cosine;
		resulting_matrix.elements[4] = x * y * one_minus_cosine - z * sine;
		resulting_matrix.elements[8] = x * z * one_minus_cosine + y * sine;

		resulting_matrix.elements[1] = x * y * one_minus_cosine + z * sine;
		resulting_matrix.elements[5] = y * y * one_minus_cosine + cosine;
		resulting_matrix.elements[9] = y * z * one_minus_cosine - x * sine;

		resulting_matrix.elements[2] = x * z * one_minus_cosine - y * sine;
		resulting_matrix.elements[6] = y * z * one_minus_cosine + x * sine;
		resulting_matrix.elements[10] = z * z * one_minus_cosine + cosine;

		return resulting_matrix;
	}

	mat4 mat4::scale(const float &sx, const float &sy, const float &sz)
	{
	  mat4 resulting_matrix(1.0f);

	  resulting_matrix.elements[0] = sx;
	  resulting_matrix.elements[5] = sy;
	  resulting_matrix.elements[10] = sz;

	  return resulting_matrix;
	}

	mat4 mat4::translate(const float &tx, const float &ty, const float &tz)
	{
	  mat4 resulting_matrix(1.0f);

	  resulting_matrix.elements[12] = tx;
	  resulting_matrix.elements[13] = ty;
	  resulting_matrix.elements[14] = tz;

	  return resulting_matrix;
	}

	mat4 mat4::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
	{
		mat4 resulting_matrix(1.0f);

		vec3 w = eye.normalize();
		vec3 u = (up.cross(w)).normalize();
		vec3 v = w.cross(u);

		resulting_matrix.elements[0] = u.x;
		resulting_matrix.elements[4] = u.y;
		resulting_matrix.elements[8] = u.z;

		resulting_matrix.elements[1] = v.x;
		resulting_matrix.elements[5] = v.y;
		resulting_matrix.elements[9] = v.z;

		resulting_matrix.elements[2] = w.x;
		resulting_matrix.elements[6] = w.y;
		resulting_matrix.elements[10] = w.z;

		resulting_matrix.elements[12] = u.dot(-1*eye);
		resulting_matrix.elements[13] = v.dot(-1*eye);
		resulting_matrix.elements[14] = w.dot(-1*eye);

		return resulting_matrix;
	}

	mat4 mat4::transpose() {

		return mat4(this->elements[0], this->elements[1], this->elements[2], this->elements[3],
					this->elements[4], this->elements[5], this->elements[6], this->elements[7],
					this->elements[8], this->elements[9], this->elements[10], this->elements[11],
					this->elements[12], this->elements[13], this->elements[14], this->elements[15]);
	}

	mat4 mat4::operator*(mat4 matrix) {

			return mat4(this->elements[0]*matrix.elements[0] + this->elements[4]*matrix.elements[1] + this->elements[8]*matrix.elements[2] + this->elements[12]*matrix.elements[3],
						this->elements[0]*matrix.elements[4] + this->elements[4]*matrix.elements[5] + this->elements[8]*matrix.elements[6] + this->elements[12]*matrix.elements[7],
						this->elements[0]*matrix.elements[8] + this->elements[4]*matrix.elements[9] + this->elements[8]*matrix.elements[10] + this->elements[12]*matrix.elements[11],
						this->elements[0]*matrix.elements[12] + this->elements[4]*matrix.elements[13] + this->elements[8]*matrix.elements[14] + this->elements[12]*matrix.elements[15],
						this->elements[1]*matrix.elements[0] + this->elements[5]*matrix.elements[1] + this->elements[9]*matrix.elements[2] + this->elements[13]*matrix.elements[3],
						this->elements[1]*matrix.elements[4] + this->elements[5]*matrix.elements[5] + this->elements[9]*matrix.elements[6] + this->elements[13]*matrix.elements[7],
						this->elements[1]*matrix.elements[8] + this->elements[5]*matrix.elements[9] + this->elements[9]*matrix.elements[10] + this->elements[13]*matrix.elements[11],
						this->elements[1]*matrix.elements[12] + this->elements[5]*matrix.elements[13] + this->elements[9]*matrix.elements[14] + this->elements[13]*matrix.elements[15],
						this->elements[2]*matrix.elements[0] + this->elements[6]*matrix.elements[1] + this->elements[10]*matrix.elements[2] + this->elements[14]*matrix.elements[3],
						this->elements[2]*matrix.elements[4] + this->elements[6]*matrix.elements[5] + this->elements[10]*matrix.elements[6] + this->elements[14]*matrix.elements[7],
						this->elements[2]*matrix.elements[8] + this->elements[6]*matrix.elements[9] + this->elements[10]*matrix.elements[10] + this->elements[14]*matrix.elements[11],
						this->elements[2]*matrix.elements[12] + this->elements[6]*matrix.elements[13] + this->elements[10]*matrix.elements[14] + this->elements[14]*matrix.elements[15],
						this->elements[3]*matrix.elements[0] + this->elements[7]*matrix.elements[1] + this->elements[11]*matrix.elements[2] + this->elements[15]*matrix.elements[3],
						this->elements[3]*matrix.elements[4] + this->elements[7]*matrix.elements[5] + this->elements[11]*matrix.elements[6] + this->elements[15]*matrix.elements[7],
						this->elements[3]*matrix.elements[8] + this->elements[7]*matrix.elements[9] + this->elements[11]*matrix.elements[10] + this->elements[15]*matrix.elements[11],
						this->elements[3]*matrix.elements[12] + this->elements[7]*matrix.elements[13] + this->elements[11]*matrix.elements[14] + this->elements[15]*matrix.elements[15]
						);
	}

	float mat4::determinant() {

		return (this->elements[0]*( this->elements[5]*this->elements[10]*this->elements[15]
									+ this->elements[6]*this->elements[11]*this->elements[13]
								    + this->elements[7]*this->elements[9]*this->elements[14]
								    - this->elements[13]*this->elements[10]*this->elements[7]
								    - this->elements[14]*this->elements[11]*this->elements[5]
									- this->elements[15]*this->elements[9]*this->elements[6])
				-this->elements[4]*( this->elements[1]*this->elements[10]*this->elements[15]
									+ this->elements[2]*this->elements[11]*this->elements[13]
									+ this->elements[3]*this->elements[9]*this->elements[14]
									- this->elements[13]*this->elements[10]*this->elements[3]
									- this->elements[14]*this->elements[11]*this->elements[1]
								    - this->elements[15]*this->elements[9]*this->elements[2])
				+this->elements[8]*( this->elements[1]*this->elements[6]*this->elements[15]
									+ this->elements[2]*this->elements[7]*this->elements[13]
									+ this->elements[3]*this->elements[5]*this->elements[14]
									- this->elements[13]*this->elements[6]*this->elements[3]
									- this->elements[14]*this->elements[7]*this->elements[1]
									- this->elements[15]*this->elements[5]*this->elements[2])
				-this->elements[12]*( this->elements[1]*this->elements[6]*this->elements[11]
									+ this->elements[2]*this->elements[7]*this->elements[9]
									+ this->elements[3]*this->elements[5]*this->elements[10]
									- this->elements[9]*this->elements[6]*this->elements[3]
									- this->elements[10]*this->elements[7]*this->elements[1]
									- this->elements[11]*this->elements[5]*this->elements[2])

		);
	}

	mat4 mat4::inverse() {

		mat4 cofactor = mat4();

		cofactor.elements[0] = (this->elements[5]*this->elements[10]*this->elements[15]
							    + this->elements[6]*this->elements[11]*this->elements[13]
							    + this->elements[7]*this->elements[9]*this->elements[14]
							    - this->elements[13]*this->elements[10]*this->elements[7]
							    - this->elements[14]*this->elements[11]*this->elements[5]
							    - this->elements[15]*this->elements[9]*this->elements[6]);

		cofactor.elements[1] = -(this->elements[4]*this->elements[10]*this->elements[15]
					            + this->elements[6]*this->elements[11]*this->elements[12]
								+ this->elements[7]*this->elements[8]*this->elements[14]
								- this->elements[12]*this->elements[10]*this->elements[7]
								- this->elements[14]*this->elements[11]*this->elements[4]
								- this->elements[15]*this->elements[8]*this->elements[6]);

		cofactor.elements[2] = (this->elements[4]*this->elements[9]*this->elements[15]
							    + this->elements[5]*this->elements[11]*this->elements[12]
							    + this->elements[7]*this->elements[8]*this->elements[13]
								- this->elements[12]*this->elements[9]*this->elements[7]
								- this->elements[13]*this->elements[11]*this->elements[4]
								- this->elements[15]*this->elements[8]*this->elements[5]);

		cofactor.elements[3] = -(this->elements[4]*this->elements[9]*this->elements[14]
							    + this->elements[5]*this->elements[10]*this->elements[12]
								+ this->elements[6]*this->elements[8]*this->elements[13]
								- this->elements[12]*this->elements[9]*this->elements[6]
								- this->elements[13]*this->elements[10]*this->elements[4]
								- this->elements[14]*this->elements[8]*this->elements[5]);

		cofactor.elements[4] = -(this->elements[1]*this->elements[10]*this->elements[15]
							    + this->elements[2]*this->elements[11]*this->elements[13]
								+ this->elements[3]*this->elements[9]*this->elements[14]
								- this->elements[13]*this->elements[10]*this->elements[3]
								- this->elements[14]*this->elements[11]*this->elements[1]
								- this->elements[15]*this->elements[9]*this->elements[2]);

		cofactor.elements[5] = (this->elements[0]*this->elements[10]*this->elements[15]
							    + this->elements[2]*this->elements[11]*this->elements[12]
								+ this->elements[3]*this->elements[8]*this->elements[14]
								- this->elements[12]*this->elements[10]*this->elements[3]
								- this->elements[14]*this->elements[11]*this->elements[0]
								- this->elements[15]*this->elements[8]*this->elements[2]);

		cofactor.elements[6] = -(this->elements[0]*this->elements[9]*this->elements[15]
							    + this->elements[1]*this->elements[11]*this->elements[12]
								+ this->elements[3]*this->elements[8]*this->elements[13]
								- this->elements[12]*this->elements[9]*this->elements[3]
								- this->elements[13]*this->elements[11]*this->elements[0]
								- this->elements[15]*this->elements[8]*this->elements[1]);

		cofactor.elements[7] = (this->elements[0]*this->elements[9]*this->elements[14]
							    + this->elements[1]*this->elements[10]*this->elements[12]
								+ this->elements[2]*this->elements[8]*this->elements[13]
								- this->elements[12]*this->elements[9]*this->elements[2]
								- this->elements[13]*this->elements[10]*this->elements[0]
								- this->elements[14]*this->elements[8]*this->elements[1]);

		cofactor.elements[8] = (this->elements[1]*this->elements[6]*this->elements[15]
							    + this->elements[2]*this->elements[7]*this->elements[13]
								+ this->elements[3]*this->elements[5]*this->elements[14]
								- this->elements[13]*this->elements[6]*this->elements[3]
								- this->elements[14]*this->elements[7]*this->elements[1]
								- this->elements[15]*this->elements[5]*this->elements[2]);

		cofactor.elements[9] = -(this->elements[0]*this->elements[6]*this->elements[15]
							     + this->elements[2]*this->elements[7]*this->elements[12]
								 + this->elements[3]*this->elements[4]*this->elements[14]
								 - this->elements[12]*this->elements[6]*this->elements[3]
								 - this->elements[14]*this->elements[7]*this->elements[0]
								 - this->elements[15]*this->elements[4]*this->elements[2]);

		cofactor.elements[10] = (this->elements[0]*this->elements[5]*this->elements[15]
							     + this->elements[1]*this->elements[7]*this->elements[12]
								 + this->elements[3]*this->elements[4]*this->elements[13]
								 - this->elements[12]*this->elements[5]*this->elements[3]
								 - this->elements[13]*this->elements[7]*this->elements[0]
								 - this->elements[15]*this->elements[4]*this->elements[1]);

		cofactor.elements[11] = -(this->elements[0]*this->elements[5]*this->elements[14]
							      + this->elements[1]*this->elements[6]*this->elements[12]
								  + this->elements[2]*this->elements[4]*this->elements[13]
								  - this->elements[12]*this->elements[5]*this->elements[2]
								  - this->elements[13]*this->elements[6]*this->elements[0]
								  - this->elements[14]*this->elements[4]*this->elements[1]);

		cofactor.elements[12] = -(this->elements[1]*this->elements[6]*this->elements[11]
							    + this->elements[2]*this->elements[7]*this->elements[9]
								+ this->elements[3]*this->elements[5]*this->elements[10]
								- this->elements[9]*this->elements[6]*this->elements[3]
								- this->elements[10]*this->elements[7]*this->elements[1]
								- this->elements[11]*this->elements[5]*this->elements[2]);

		cofactor.elements[13] = (this->elements[0]*this->elements[6]*this->elements[11]
							     + this->elements[2]*this->elements[7]*this->elements[8]
								 + this->elements[3]*this->elements[4]*this->elements[10]
								 - this->elements[8]*this->elements[6]*this->elements[3]
								 - this->elements[10]*this->elements[7]*this->elements[0]
								 - this->elements[11]*this->elements[4]*this->elements[2]);

		cofactor.elements[14] = -(this->elements[0]*this->elements[5]*this->elements[11]
							    + this->elements[1]*this->elements[7]*this->elements[8]
								+ this->elements[3]*this->elements[4]*this->elements[9]
								- this->elements[8]*this->elements[5]*this->elements[3]
								- this->elements[9]*this->elements[7]*this->elements[0]
								- this->elements[11]*this->elements[4]*this->elements[1]);

		cofactor.elements[15] = (this->elements[0]*this->elements[5]*this->elements[10]
							     + this->elements[1]*this->elements[6]*this->elements[8]
								 + this->elements[2]*this->elements[4]*this->elements[9]
								 - this->elements[8]*this->elements[5]*this->elements[2]
						         - this->elements[9]*this->elements[6]*this->elements[0]
								 - this->elements[10]*this->elements[4]*this->elements[1]);

		return 1/this->determinant()*cofactor.transpose();
	}

	mat4 operator*(int scalar, const mat4& matrix) {

		mat4 resulting_matrix = mat4();

		for (int i = 0; i < 16; i++) {
			resulting_matrix.elements[i] = scalar*matrix.elements[i];
		}

		return resulting_matrix;
	}

	mat4 operator*(float scalar, const mat4& matrix) {

		mat4 resulting_matrix = mat4();

		for (int i = 0; i < 16; i++) {
			resulting_matrix.elements[i] = scalar*matrix.elements[i];
		}

		return resulting_matrix;
	}

	vec3 mat4::operator*(const vec3& vector) {

		return vec3(this->elements[0]*vector.x + this->elements[4]*vector.y + this->elements[8]*vector.z,
				this->elements[1]*vector.x + this->elements[5]*vector.y + this->elements[9]*vector.z,
				this->elements[2]*vector.x + this->elements[6]*vector.y + this->elements[10]*vector.z);
	}

	vec4 mat4::operator*(const vec4& vector) {

		return vec4(this->elements[0]*vector.x + this->elements[4]*vector.y + this->elements[8]*vector.z + this->elements[12]*vector.w,
				this->elements[1]*vector.x + this->elements[5]*vector.y + this->elements[9]*vector.z + this->elements[13]*vector.w,
				this->elements[2]*vector.x + this->elements[6]*vector.y + this->elements[10]*vector.z + this->elements[14]*vector.w,
				this->elements[3]*vector.x + this->elements[7]*vector.y + this->elements[11]*vector.z + this->elements[15]*vector.w);
	}

	mat4& mat4::operator=(mat4 matrix) {

		for (int i = 0; i < 16; i++)  {
			this->elements[i] = matrix.elements[i];
		}

		return *this;
	}

	bool mat4::operator==(mat4 matrix) {

		for (int i = 0; i < 16; i++)  {
			if (this->elements[i] != matrix.elements[i]) {
				return false;
			}
		}

		return true;
	}

	bool mat4::operator!=(mat4 matrix) {

		return !this->operator==(matrix);
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& matrix) {
		stream << "mat4: {{" << matrix.elements[0] << ", " << matrix.elements[4] << ", " << matrix.elements[8] << ", " << matrix.elements[12] <<
				"}, {" << matrix.elements[1] << ", " << matrix.elements[5] << ", " << matrix.elements[9] << ", " << matrix.elements[13] <<
				"}, {" << matrix.elements[2] << ", " << matrix.elements[6] << ", " << matrix.elements[10] << ", " << matrix.elements[14] <<
				"}, {" << matrix.elements[3] << ", " << matrix.elements[7] << ", " << matrix.elements[11] << ", " << matrix.elements[15] << "}}";
		return stream;
	}

}
