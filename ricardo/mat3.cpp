/*
 * mat3.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: blroot
 */

#include "stdafx.h"
#include "mat3.h"

namespace math {

	/*
	 * Note that matrix is in column order
	 */

	mat3::mat3() {

		for (int i = 0; i < 9; i++) {
			this->elements[i] = 0.0f;
		}
	}

	mat3::mat3(float diagonal) {

		for (int i = 0; i < 9; i++) {
					this->elements[i] = 0.0f;
		}

		elements[0] = diagonal;
		elements[4] = diagonal;
		elements[8] = diagonal;
	}

	mat3::mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {

		elements[0] = a;
		elements[1] = d;
		elements[2] = g;
		elements[3] = b;
		elements[4] = e;
		elements[5] = h;
		elements[6] = c;
		elements[7] = f;
		elements[8] = i;
	}

	mat3 mat3::transpose() {

		return mat3(this->elements[0], this->elements[1], this->elements[2],
					this->elements[3], this->elements[4], this->elements[5],
					this->elements[6], this->elements[7], this->elements[8]);
	}

	float mat3::determinant() {

		return(this->elements[0]*this->elements[4]*this->elements[8]
			   + this->elements[1]*this->elements[5]*this->elements[6]
			   + this->elements[2]*this->elements[3]*this->elements[7]
			   - this->elements[2]*this->elements[4]*this->elements[6]
			   - this->elements[0]*this->elements[5]*this->elements[7]
			   - this->elements[1]*this->elements[3]*this->elements[8]);
	}

	mat3 mat3::inverse() {

		mat3 cofactor = mat3();

		cofactor.elements[0] = this->elements[4]*this->elements[8] - this->elements[5]*this->elements[7];
		cofactor.elements[1] = -(this->elements[3]*this->elements[8] - this->elements[5]*this->elements[6]);
		cofactor.elements[2] = this->elements[3]*this->elements[7] - this->elements[4]*this->elements[6];
		cofactor.elements[3] = -(this->elements[1]*this->elements[8] - this->elements[2]*this->elements[7]);
		cofactor.elements[4] = this->elements[0]*this->elements[8] - this->elements[2]*this->elements[6];
		cofactor.elements[5] = -(this->elements[0]*this->elements[7] - this->elements[1]*this->elements[6]);
		cofactor.elements[6] = this->elements[1]*this->elements[5] - this->elements[2]*this->elements[4];
		cofactor.elements[7] = -(this->elements[0]*this->elements[5] - this->elements[2]*this->elements[3]);
		cofactor.elements[8] = this->elements[0]*this->elements[4] - this->elements[1]*this->elements[3];

	    return 1/this->determinant()*cofactor.transpose();
	}

	mat3& mat3::operator=(mat3 matrix) {

		for (int i = 0; i < 9; i++)  {
			this->elements[i] = matrix.elements[i];
		}

		return *this;
	}

	mat3 mat3::operator*(mat3 matrix) {

		return mat3(this->elements[0]*matrix.elements[0] + this->elements[3]*matrix.elements[1] + this->elements[6]*matrix.elements[2],
					this->elements[0]*matrix.elements[3] + this->elements[3]*matrix.elements[4] + this->elements[6]*matrix.elements[5],
					this->elements[0]*matrix.elements[6] + this->elements[3]*matrix.elements[7] + this->elements[6]*matrix.elements[8],
					this->elements[1]*matrix.elements[0] + this->elements[4]*matrix.elements[1] + this->elements[7]*matrix.elements[2],
					this->elements[1]*matrix.elements[3] + this->elements[4]*matrix.elements[4] + this->elements[7]*matrix.elements[5],
					this->elements[1]*matrix.elements[6] + this->elements[4]*matrix.elements[7] + this->elements[7]*matrix.elements[8],
					this->elements[2]*matrix.elements[0] + this->elements[5]*matrix.elements[1] + this->elements[8]*matrix.elements[2],
					this->elements[2]*matrix.elements[3] + this->elements[5]*matrix.elements[4] + this->elements[8]*matrix.elements[5],
					this->elements[2]*matrix.elements[6] + this->elements[5]*matrix.elements[7] + this->elements[8]*matrix.elements[8]
					);
	}

	mat3 mat3::operator*(float scalar) {

		mat3 resulting_matrix = mat3();

		for (int i = 0; i < 9; i++) {
			resulting_matrix.elements[i] = scalar*this->elements[i];
		}

		return resulting_matrix;
	}

	mat3 operator*(float scalar, const mat3& matrix) {
		mat3 resulting_matrix = mat3();

		for (int i = 0; i < 9; i++) {
			resulting_matrix.elements[i] = scalar*matrix.elements[i];
		}

		return resulting_matrix;
	}

	mat3 operator*(int scalar, const mat3& matrix) {

		mat3 resulting_matrix = mat3();

		for (int i = 0; i < 9; i++) {
			resulting_matrix.elements[i] = scalar*matrix.elements[i];
		}

		return resulting_matrix;
	}

	bool mat3::operator==(mat3 matrix) {

		bool result = true;
		for (int i = 0; i < 9; i++) {
			if (this->elements[i] != matrix.elements[i]) {
				result = false;
			}
		}
		return result;
	}

}
