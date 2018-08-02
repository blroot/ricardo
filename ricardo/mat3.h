/*

 * mat3.h
 *
 *  Created on: Jul 5, 2017
 *      Author: blroot
 */

#pragma once

namespace math {

	struct mat3 {

		float elements[9];

		mat3();
		mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
		mat3(float diagonal);

		mat3 transpose();
		float determinant();
		mat3 inverse();

		mat3 operator*(mat3 matrix);
		mat3 operator*(float scalar);
		friend mat3 operator*(float scalar, const mat3& matrix);
		friend mat3 operator*(int scalar, const mat3& matrix);
		mat3& operator=(mat3 matrix);
		bool operator==(mat3 matrix);
	};

}


