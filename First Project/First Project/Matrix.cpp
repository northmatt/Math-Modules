#include "Matrix.h"

mat2::mat2(vec2 _row1, vec2 _row2) {
	row1 = _row1;
	row2 = _row2;
}

mat2::mat2(float rot) {
	row1 = vec2(cos(rot), -sin(rot));
	row2 = vec2(sin(rot), cos(rot));
}

mat2 mat2::operator+(mat2 m) {
	return mat2(row1 + m.row1, row2 + m.row2);
}

mat2 mat2::operator-(mat2 m) {
	return mat2(row1 - m.row1, row2 - m.row2);
}

mat2 mat2::operator*(float f) {
	return mat2(row1 * f, row2 * f);
}

mat2 mat2::operator/(float f) {
	return mat2(row1 / f, row2 / f);
}

mat2 mat2::operator*(mat2 m) {
	vec2 col1 = vec2(m.row1.x, m.row2.x);
	vec2 col2 = vec2(m.row1.y, m.row2.y);
	return mat2({ row1.Dot(col1), row1.Dot(col2) }, { row2.Dot(col1), row2.Dot(col2) });
}

vec2 mat2::operator*(vec2 v2) {
	return vec2(row1.Dot(v2), row2.Dot(v2));
}

vec2 mat2::operator[](int i) {
	return *hold[i];
}

void mat2::Print() {
	printf("[ %f, %f ]\n", row1.x, row1.y);
	printf("[ %f, %f ]\n", row2.x, row2.y);
}

mat2 mat2::Transpose() {
	mat2 temp;
	temp.row1 = vec2(row1.x, row2.x);
	temp.row2 = vec2(row1.y, row2.y);

	return temp;
}

float mat2::Determinant() {
	return row1.x * row2.y - row1.y * row2.x;
}

mat2 mat2::Inverse() {
	float det = Determinant();
	mat2 temp;
	temp.row1 = vec2(row2.y, -row1.y);
	temp.row2 = vec2(-row2.x, row1.x);

	temp = temp / det;

	return temp;
}

mat3::mat3(vec3 _row1, vec3 _row2, vec3 _row3) {
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
}

mat3::mat3(mat4 m) {
	this->row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	this->row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	this->row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
}

void mat3::Add(mat3 m) {
	row1 = row1 + m.row1;
	row2 = row2 + m.row2;
	row3 = row3 + m.row3;
}

void mat3::Subtract(mat3 m) {
	row1 = row1 - m.row1;
	row2 = row2 - m.row2;
	row3 = row3 - m.row3;
}

mat3 mat3::Transpose(mat3 R) {
	mat3 temp;

	temp.row1 = vec3(R.row1.x, R.row2.x, R.row3.x);
	temp.row2 = vec3(R.row1.y, R.row2.y, R.row3.y);
	temp.row3 = vec3(R.row1.z, R.row2.z, R.row3.z);

	return temp;
}

mat3 mat3::operator+(mat3 m) {
	return mat3(row1 + m.row1, row2 + m.row2, row3 + m.row3);
}

mat3 mat3::operator-(mat3 m) {
	return mat3(row1 - m.row1, row2 - m.row2, row3 - m.row3);
}

mat3 mat3::operator*(float f) {
	return mat3(row1 * f, row2 * f, row3 * f);
}

mat3 mat3::operator*(mat3 m) {
	mat3 temp;
	mat3 mTran;
	mTran = mat3::Transpose(m);

	temp.row1 = vec3(temp.row1.Dot(mTran.row1), temp.row1.Dot(mTran.row2), temp.row1.Dot(mTran.row3));
	temp.row2 = vec3(temp.row2.Dot(mTran.row1), temp.row2.Dot(mTran.row2), temp.row2.Dot(mTran.row3));
	temp.row3 = vec3(temp.row3.Dot(mTran.row1), temp.row3.Dot(mTran.row2), temp.row3.Dot(mTran.row3));

	return temp;
}

mat3 mat3::operator/(float f) {
	return mat3(row1 / f, row2 / f, row3 / f);
}

mat3 mat3::operator-() {
	return mat3(-row1, -row2, -row3);
}

vec3 mat3::operator[](int i) {
	return *hold[i];
}

vec3 mat3::operator*(vec3 vec) {
	vec3 temp;
	temp = vec3(
		row1.x * vec.x + row1.y * vec.y + row1.z * vec.z, 
		row2.x * vec.x + row2.y * vec.y + row2.z * vec.z,
		row3.x * vec.x + row3.y * vec.y + row3.z * vec.z );

	return temp;
}

float mat3::Determinant() {
	//[a, b, c]
	//[d, e, f]
	//[g, h, i]
	//a * det(e, f, h, i) - b * det(d, f, g, i) + c * det(d, e, g, h)
	mat2 aCol({ row2.y, row2.z }, { row3.y, row3.z });
	mat2 bCol({ row2.x, row2.z }, { row3.x, row3.z });
	mat2 cCol({ row2.x, row2.y }, { row3.x, row3.y });

	return row1.x * aCol.Determinant() - row1.y * bCol.Determinant() + row1.z * cCol.Determinant();
}

mat3 mat3::Inverse() {
	mat3 temp;
	float det = Determinant();

	temp.row1 = vec3(row3.z, -row1.y, row1.z);
	temp.row2 = vec3(-row2.x, row2.y, -row2.z);
	temp.row3 = vec3(row3.x, -row3.y, row1.x);
	temp = temp / det;

	return mat3();
}

void mat3::Print() {
	printf("[ %f, %f, %f ]\n", row1.x, row1.y, row1.z);
	printf("[ %f, %f, %f ]\n", row2.x, row2.y, row2.z);
	printf("[ %f, %f, %f ]\n", row3.x, row3.y, row3.z);
}

mat4::mat4(vec4 _row1, vec4 _row2, vec4 _row3, vec4 _row4) {
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
	row4 = _row4;
}

mat4::mat4(mat3 rot, vec3 trans) {
	row1 = vec4{ rot.row1.x, rot.row1.y, rot.row1.z, trans.x };
	row2 = vec4{ rot.row2.x, rot.row2.y, rot.row2.z, trans.y };
	row3 = vec4{ rot.row3.x, rot.row3.y, rot.row3.z, trans.z };
	row4 = vec4{ 0.f, 0.f, 0.f, 1.f };
}

mat4 mat4::FastInverse(mat4 mat) {
	mat3 rotation = mat3(mat);
	vec3 translation = Translation(mat);

	rotation = mat3::Transpose(rotation);
	translation = -rotation * translation;

	return mat4(rotation, translation);
}

vec3 mat4::Translation(mat4 mat) {
	return vec3(mat.row1.z, mat.row2.z, mat.row3.z);
}

mat4 mat4::Transpose(mat4 m) {
	mat4 temp;

	temp.row1 = vec4(m.row1.x, m.row2.x, m.row3.x, m.row4.x);
	temp.row2 = vec4(m.row1.y, m.row2.y, m.row3.y, m.row4.y);
	temp.row3 = vec4(m.row1.z, m.row2.z, m.row3.z, m.row4.z);
	temp.row4 = vec4(m.row1.w, m.row2.w, m.row3.w, m.row4.w);

	return temp;
}

void mat4::Add(mat4 m) {
	row1 = row1 + m.row1;
	row2 = row2 + m.row2;
	row3 = row3 + m.row3;
	row4 = row4 + m.row4;
}

void mat4::Subtract(mat4 m) {
	row1 = row1 - m.row1;
	row2 = row2 - m.row2;
	row3 = row3 - m.row3;
	row4 = row4 - m.row4;
}

mat4 mat4::operator+(mat4 m) {
	return mat4(row1 + m.row1, row2 + m.row2, row3 + m.row3, row4 + m.row4);
}

mat4 mat4::operator-(mat4 m) {
	return mat4(row1 - m.row1, row2 - m.row2, row3 - m.row3, row4 - m.row4);
}

mat4 mat4::operator*(float f) {
	return mat4(row1 * f, row2 * f, row3 * f, row4 * f);
}

mat4 mat4::operator*(mat4 m) {
	mat4 temp;
	mat4 mTran = mat4::Transpose(m);

	temp.row1 = vec4(row1.Dot(mTran.row1), row1.Dot(mTran.row2), row1.Dot(mTran.row3), row1.Dot(mTran.row4));
	temp.row2 = vec4(row2.Dot(mTran.row1), row2.Dot(mTran.row2), row2.Dot(mTran.row3), row2.Dot(mTran.row4));
	temp.row3 = vec4(row3.Dot(mTran.row1), row3.Dot(mTran.row2), row3.Dot(mTran.row3), row3.Dot(mTran.row4));
	temp.row4 = vec4(row4.Dot(mTran.row1), row4.Dot(mTran.row2), row4.Dot(mTran.row3), row4.Dot(mTran.row4));

	return temp;
}

mat4 mat4::operator/(float f) {
	return mat4(row1 / f, row2 / f, row3 / f, row4 / f);
}

vec4 mat4::operator[](int i) {
	return *hold[i];
}

mat4 mat4::operator-() {
	return mat4(-row1, -row2, row3, -row4);
}

vec4 mat4::operator*(vec4 vec) {
	return vec4(row1.Dot(vec), row2.Dot(vec), row3.Dot(vec), row4.Dot(vec));
}

float mat4::Determinant() {
	mat3 aDet({ row2.y, row2.z, row2.w }, { row3.y, row3.z, row3.w }, { row4.y, row4.z, row4.w });
	mat3 bDet({ row2.x, row2.z, row2.w }, { row3.x, row3.z, row3.w }, { row4.x, row4.z, row4.w });
	mat3 cDet({ row2.x, row2.y, row2.w }, { row3.x, row3.y, row3.w }, { row4.x, row4.y, row4.w });
	mat3 dDet({ row2.x, row2.y, row2.z }, { row3.x, row3.y, row3.z }, { row4.x, row4.y, row4.z });

	return row1.x * aDet.Determinant() - row1.y * bDet.Determinant() + row1.z * cDet.Determinant() - row1.w * dDet.Determinant();
}

mat4 mat4::Inverse() {
	mat4 temp;

	temp.row1 = vec4(row4.w, -row1.y, row1.z, -row1.w);
	temp.row2 = vec4(-row2.x, row3.z, -row2.z, row2.w);
	temp.row3 = vec4(row3.x, -row3.y, row2.y, -row3.w);
	temp.row4 = vec4(-row4.x, row4.y, -row4.z, row1.x);
	temp = temp / Determinant();

	return temp;
}

void mat4::Print() {
	printf("[ %f, %f, %f, %f ]", row1.x, row1.y, row1.z, row1.w);
	printf("[ %f, %f, %f, %f ]", row2.x, row2.y, row2.z, row2.w);
	printf("[ %f, %f, %f, %f ]", row3.x, row3.y, row3.z, row3.w);
	printf("[ %f, %f, %f, %f ]", row4.x, row4.y, row4.z, row4.w);
}
