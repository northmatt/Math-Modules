#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include "Vector.h"

class mat4;

class mat3
{
public:
	//Empty constructor
	mat3() { }
	//Sets row1, row2, and row3
	mat3(vec3 _row1, vec3 _row2, vec3 _row3);
	//Creates a 3x3 matrix using a 4x4 matrix
	//*useful for grabing rotation matrix from a homogenous transformation matrix
	mat3(mat4 m);

	void Add(mat3 m);
	void Subtract(mat3 m);

	static mat3 Transpose(mat3 R);

	//Rows are made up of vectors
	//*defaults to zero
	vec3 row1 = vec3();
	vec3 row2 = vec3();
	vec3 row3 = vec3();
	//For use so that you can index the matrix using [] operator
	vec3* hold[3] = { &row1, &row2, &row3 };

	mat3 operator+(mat3 m);
	mat3 operator-(mat3 m);
	mat3 operator*(float f);
	mat3 operator*(mat3 m);
	mat3 operator/(float f);
	//Negates the matrix
	mat3 operator-();
	//For use so that you can index the matrix using [] operator
	vec3 operator[](int i);
	//Multiplies the matrix with a 3D vector
	vec3 operator*(vec3 vec);

	float Determinant();
	mat3 Inverse();

	void Print();
};

class mat4
{
public:
	mat4() { }
	//Sets row1, row2, row3, and row4
	mat4(vec4 _row1, vec4 _row2, vec4 _row3, vec4 _row4);
	//creates a 4x4 matrix using a 3x3 rotation matrix and a 3D translation vector
	mat4(mat3 rot, vec3 trans);

	//Gets the fast inverse of a homogenous transformation matrix
	static mat4 FastInverse(mat4 mat);
	//Gets the translation data from a homogenous transformation matrix
	static vec3 Translation(mat4 mat);
	static mat4 Transpose(mat4 m);

	//Rows are made up of vectors
	vec4 row1 = vec4(0.f, 0.f, 0.f, 0.f);
	vec4 row2 = vec4(0.f, 0.f, 0.f, 0.f);
	vec4 row3 = vec4(0.f, 0.f, 0.f, 0.f);
	vec4 row4 = vec4(0.f, 0.f, 0.f, 0.f);
	//For use so that you can index the matrix using [] operator
	vec4* hold[4] = { &row1, &row2, &row3, &row4 };

	void Add(mat4 m);
	void Subtract(mat4 m);

	mat4 operator+(mat4 m);
	mat4 operator-(mat4 m);
	mat4 operator*(float f);
	mat4 operator*(mat4 m);
	mat4 operator/(float f);
	//For use so that you can index the matrix using [] operator
	vec4 operator[](int i);
	//Negates the matrix
	mat4 operator-();
	//Multiplies the matrix with a 3D vector
	vec4 operator*(vec4 vec);

	float Determinant();
	mat4 Inverse();

	void Print();
};

class mat2 {
public:
	//Empty constructor
	mat2() {}
	//sets row1 and row2
	mat2(vec2 _row1, vec2 _row2);
	//with rotation
	mat2(float rot);

	void Add(mat2 m);
	void Subtract(mat2 m);

	//Rows are made up of vectors
	vec2 row1 = vec2();
	vec2 row2 = vec2();
	//For use so that you can index the matrix using [] operator
	vec2* hold[2] = { &row1, &row2 };

	mat2 operator+(mat2 m);
	mat2 operator-(mat2 m);
	mat2 operator*(float f);
	mat2 operator/(float f);
	mat2 operator*(mat2 m);
	vec2 operator*(vec2 v2);
	//for use so that you can index the matrix using [] operator
	vec2 operator[](int i);

	void Print();

	mat2 Transpose();
	float Determinant();
	mat2 Inverse();
};

#endif // !__MATRIX_H__
