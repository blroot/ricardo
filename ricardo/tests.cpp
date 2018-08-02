/*
 * tests.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: blroot
 */

#include "stdafx.h"
#include <gtest/gtest.h>
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

using namespace math;

TEST(Vec3Test, NullVec) {
	vec3 v = vec3();

    ASSERT_EQ(v.x, 0.0f);
    ASSERT_EQ(v.y, 0.0f);
    ASSERT_EQ(v.z, 0.0f);
}

TEST(Vec3Test, UnitVecCreation) {
	vec3 v = vec3(1.0f, 1.0f, 1.0f);

    ASSERT_EQ(v.x, 1.0f);
    ASSERT_EQ(v.y, 1.0f);
    ASSERT_EQ(v.z, 1.0f);
}

TEST(Vec3Test, Add) {
	vec3 v = vec3(1.0f, 6.0f, 1.0f);
	vec3 w = vec3(5.0f, 1.0f, 0.0f);

	vec3 u = v + w;

	ASSERT_EQ(u.x, 6.0f);
	ASSERT_EQ(u.y, 7.0f);
	ASSERT_EQ(u.z, 1.0f);
}

TEST(Vec3Test, Substract) {
	vec3 v = vec3(1.0f, 6.0f, 1.0f);
	vec3 w = vec3(5.0f, 1.0f, 0.0f);

	vec3 u = v - w;

	ASSERT_EQ(u.x, -4.0f);
	ASSERT_EQ(u.y, 5.0f);
	ASSERT_EQ(u.z, 1.0f);
}

TEST(Vec3Test, ScalarMultiplication) {
	vec3 v = vec3(1.0f, 6.0f, 2.0f);

	vec3 u = 5*v;

	ASSERT_EQ(u.x, 5.0f);
	ASSERT_EQ(u.y, 30.0f);
	ASSERT_EQ(u.z, 10.0f);
}

TEST(Vec3Test, DotProduct) {
	vec3 v = vec3(1.0f, 6.0f, 2.0f);
	vec3 w = vec3(5.0f, 1.0f, 0.0f);

	float u = v.dot(w);

	ASSERT_EQ(u, 11.0f);
}

TEST(Vec3Test, Normalize) {
	vec3 v = vec3(5.0f, 3.0f, 2.0f);
	vec3 versor_v = v.normalize();

    ASSERT_FLOAT_EQ(versor_v.x, 0.8111071);
    ASSERT_FLOAT_EQ(versor_v.y, 0.48666427);
    ASSERT_FLOAT_EQ(versor_v.z, 0.32444283);
}

TEST(Vec3Test, Cross) {
	vec3 v = vec3(1.0f, 0.0f, 0.0f);
	vec3 w = vec3(0.0f, 1.0f, 0.0f);

	vec3 u = v.cross(w);

	ASSERT_EQ(u.x, 0.0f);
	ASSERT_EQ(u.y, 0.0f);
	ASSERT_EQ(u.z, 1.0f);
}

TEST(Mat3Test, NullMat) {
	mat3 M = mat3();

	ASSERT_FLOAT_EQ(M.elements[0], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 0.0f);
}

TEST(Mat3Test, DiagonalMat) {
	mat3 M = mat3(1.0f);

	ASSERT_FLOAT_EQ(M.elements[0], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 1.0f);
}

TEST(Mat3Test, MatrixProduct) {
	mat3 M = mat3(2.0f, 5.0f, 4.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.0f);
	mat3 B = mat3(2.0f, 4.0f, 5.0f, 5.0f, 2.0f, 4.0f, 3.0f, 1.0f, 1.0f);

	mat3 C = M*B;

	ASSERT_FLOAT_EQ(C.elements[0], 41.0f);
	ASSERT_FLOAT_EQ(C.elements[1], 15.0f);
	ASSERT_FLOAT_EQ(C.elements[2], 7.0f);
	ASSERT_FLOAT_EQ(C.elements[3], 22.0f);
	ASSERT_FLOAT_EQ(C.elements[4], 12.0f);
	ASSERT_FLOAT_EQ(C.elements[5], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[6], 34.0f);
	ASSERT_FLOAT_EQ(C.elements[7], 16.0f);
	ASSERT_FLOAT_EQ(C.elements[8], 9.0f);
}

TEST(Mat3Test, DiagonalDeterminant) {
	mat3 M = mat3(1.0f);

	ASSERT_FLOAT_EQ(M.determinant(), 1.0f);
}

TEST(Mat3Test, Determinant) {
	mat3 M = mat3(1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	ASSERT_FLOAT_EQ(M.determinant(), -1.0f);
}

TEST(Mat3Test, Transpose) {
	mat3 M = mat3(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f).transpose();

	ASSERT_FLOAT_EQ(M.elements[0], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 5.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 3.0f);
}

TEST(Mat3Test, Inverse) {
	mat3 M = mat3(1.0f, 2.0f, 3.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f).inverse();

	ASSERT_FLOAT_EQ(M.elements[0], -1.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[3], -1.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[5], -1.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 4.0f);
	ASSERT_FLOAT_EQ(M.elements[7], -5.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 2.0f);
}

TEST(Mat3Test, ScalarMultiplication) {
	mat3 M = mat3(1.0f, 2.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	M = 3*M;

	ASSERT_FLOAT_EQ(M.elements[0], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 3.0f);
}

TEST(Mat4Test, NullMat) {
	mat4 M = mat4();

	ASSERT_FLOAT_EQ(M.elements[0], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[9], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[10], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[11], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[12], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[13], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[14], 0.0f);
	ASSERT_FLOAT_EQ(M.elements[15], 0.0f);
}

TEST(Mat4Test, DiagonalMat) {
	mat4 M = mat4(1.0f);

	ASSERT_FLOAT_EQ(M.elements[0], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[10], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[15], 1.0f);
}

TEST(Mat4Test, Transpose) {
	mat4 M = mat4(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f, 5.0f, 1.0f, 2.0f, 6.0f, 1.0f, 9.0f, 11.0f).transpose();

	ASSERT_FLOAT_EQ(M.elements[0], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[1], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[2], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[3], 5.0f);
	ASSERT_FLOAT_EQ(M.elements[4], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[5], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[6], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[7], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[8], 3.0f);
	ASSERT_FLOAT_EQ(M.elements[9], 5.0f);
	ASSERT_FLOAT_EQ(M.elements[10], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[11], 2.0f);
	ASSERT_FLOAT_EQ(M.elements[12], 6.0f);
	ASSERT_FLOAT_EQ(M.elements[13], 1.0f);
	ASSERT_FLOAT_EQ(M.elements[14], 9.0f);
	ASSERT_FLOAT_EQ(M.elements[15], 11.0f);
}

TEST(Mat4Test, MatrixProduct) {
	mat4 M = mat4(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f, 5.0f, 1.0f, 2.0f, 6.0f, 1.0f, 9.0f, 11.0f);
	mat4 B = mat4(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f, 5.0f, 1.0f, 2.0f, 6.0f, 1.0f, 9.0f, 11.0f);

	mat4 C = M*B;

	ASSERT_FLOAT_EQ(C.elements[0], 44.0f);
	ASSERT_FLOAT_EQ(C.elements[1], 38.0f);
	ASSERT_FLOAT_EQ(C.elements[2], 28.0f);
	ASSERT_FLOAT_EQ(C.elements[3], 101.0f);
	ASSERT_FLOAT_EQ(C.elements[4], 28.0f);
	ASSERT_FLOAT_EQ(C.elements[5], 45.0f);
	ASSERT_FLOAT_EQ(C.elements[6], 28.0f);
	ASSERT_FLOAT_EQ(C.elements[7], 71.0f);
	ASSERT_FLOAT_EQ(C.elements[8], 63.0f);
	ASSERT_FLOAT_EQ(C.elements[9], 48.0f);
	ASSERT_FLOAT_EQ(C.elements[10], 58.0f);
	ASSERT_FLOAT_EQ(C.elements[11], 132.0f);
	ASSERT_FLOAT_EQ(C.elements[12], 70.0f);
	ASSERT_FLOAT_EQ(C.elements[13], 50.0f);
	ASSERT_FLOAT_EQ(C.elements[14], 49.0f);
	ASSERT_FLOAT_EQ(C.elements[15], 171.0f);
}

TEST(Mat4Test, ScalarMultiplication) {
	mat4 M = mat4(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f, 5.0f, 1.0f, 2.0f, 6.0f, 1.0f, 9.0f, 11.0f);
	mat4 C = 3*M;

	ASSERT_FLOAT_EQ(C.elements[0], 3.0f);
	ASSERT_FLOAT_EQ(C.elements[1], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[2], 9.0f);
	ASSERT_FLOAT_EQ(C.elements[3], 18.0f);
	ASSERT_FLOAT_EQ(C.elements[4], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[5], 9.0f);
	ASSERT_FLOAT_EQ(C.elements[6], 15.0f);
	ASSERT_FLOAT_EQ(C.elements[7], 3.0f);
	ASSERT_FLOAT_EQ(C.elements[8], 9.0f);
	ASSERT_FLOAT_EQ(C.elements[9], 18.0f);
	ASSERT_FLOAT_EQ(C.elements[10], 3.0f);
	ASSERT_FLOAT_EQ(C.elements[11], 27.0f);
	ASSERT_FLOAT_EQ(C.elements[12], 15.0f);
	ASSERT_FLOAT_EQ(C.elements[13], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[14], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[15], 33.0f);
}

TEST(Mat4Test, Inverse) {
	mat4 C = mat4(1.0f, 2.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 4.0f, 2.0f, 2.0f, 1.0f, 1.0f, 2.0f, 2.0f).inverse();

	ASSERT_FLOAT_EQ(C.elements[0], -3.0f);
	ASSERT_FLOAT_EQ(C.elements[1], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[2], 0.0f);
	ASSERT_FLOAT_EQ(C.elements[3], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[4], 6.0f);
	ASSERT_FLOAT_EQ(C.elements[5], -2.0f);
	ASSERT_FLOAT_EQ(C.elements[6], -1.0f);
	ASSERT_FLOAT_EQ(C.elements[7], -1.0f);
	ASSERT_FLOAT_EQ(C.elements[8], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[9], 0.0f);
	ASSERT_FLOAT_EQ(C.elements[10], 0.0f);
	ASSERT_FLOAT_EQ(C.elements[11], -0.5f);
	ASSERT_FLOAT_EQ(C.elements[12], -4.0f);
	ASSERT_FLOAT_EQ(C.elements[13], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[14], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[15], 1.0f);
}

TEST(Mat4Test, Inverse2) {
	mat4 C = mat4(1.0f, 2.0f, 8.0f, 2.0f, 1.0f, 3.0f, 1.0f, 2.0f, 2.0f, 4.0f, 2.0f, 2.0f, 1.0f, 5.0f, 2.0f, 2.0f).inverse();

	ASSERT_FLOAT_EQ(C.elements[0], -1.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[1], -1.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[2], 2.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[3], 1.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[4], -2.0f/5.0f);
	ASSERT_FLOAT_EQ(C.elements[5], -2.0f/5.0f);
	ASSERT_FLOAT_EQ(C.elements[6], -1.0f/5.0f);
	ASSERT_FLOAT_EQ(C.elements[7], 7.0f/5.0f);
	ASSERT_FLOAT_EQ(C.elements[8], 1.0f);
	ASSERT_FLOAT_EQ(C.elements[9], 0.0f);
	ASSERT_FLOAT_EQ(C.elements[10], 0.0f);
	ASSERT_FLOAT_EQ(C.elements[11], -0.5f);
	ASSERT_FLOAT_EQ(C.elements[12], -8.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[13], 7.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[14], 1.0f/15.0f);
	ASSERT_FLOAT_EQ(C.elements[15], -7.0f/15.0f);
}

TEST(Mat4Test, Determinant) {
	mat4 C = mat4(1.0f, 2.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 4.0f, 2.0f, 2.0f, 1.0f, 1.0f, 2.0f, 2.0f);

	ASSERT_FLOAT_EQ(C.determinant(), -2.0f);
}

TEST(Mat4Test, DiagonalDeterminant) {
	mat4 M = mat4(1.0f);

	ASSERT_FLOAT_EQ(M.determinant(), 1.0f);
}

TEST(Mat4Test, Mat4XVec4) {
	mat4 M = mat4(1.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 6.0f, 2.0f, 3.0f, 5.0f, 1.0f, 2.0f, 6.0f, 1.0f, 9.0f, 11.0f);
	vec4 v = vec4(8.0f, 2.5f, 3.0f, 1.0f);
	v = M*v;

	ASSERT_FLOAT_EQ(v.x, 27.0f);
	ASSERT_FLOAT_EQ(v.y, 43.5f);
	ASSERT_FLOAT_EQ(v.z, 41.5f);
	ASSERT_FLOAT_EQ(v.w, 88.5f);
}



int main(int argc, char **argv) {

	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
