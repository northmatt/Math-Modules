#include "Vector.h"

vec2::vec2() {
}

vec2::vec2(float _x, float _y) {
	x = _x;
	y = _y;
}

void vec2::Subtract(vec2 v2) {
	this->x -= v2.x;
	this->y -= v2.y;
}

void vec2::MultScalar(float s) {
	this->x *= s;
	this->y *= s;
}

void vec2::DivScalar(float s) {
	this->x /= s;
	this->y /= s;
}

float vec2::Dot(vec2 v2) {
	return x * v2.x + y * v2.y;
}

float vec2::GetMagnitude() {
	return sqrtf(x * x + y * y);
}

float vec2::GetMagnitudeSquared() {
	return x * x + y * y;
}

vec2 vec2::Normailize() {
	return *this / GetMagnitude();
}

vec2 vec2::Project(vec2 b) {
	return b * (Dot(b) / b.GetMagnitudeSquared());
}

vec2 vec2::Rotate(float rot) {
	double c{ cos(rot) }, s{ sin(rot) };
	return vec2(x * c - y * s, x * s + y * c);
}

float vec2::operator[](int i) {
	//used for indexing
	//i == 0 then x
	//i == 1 then y
	return *hold[i];
}

vec2 vec2::operator-() {
	return vec2(-x, -y);
}

vec2 vec2::operator+(vec2 v1) {
	return vec2(this->x + v1.x, this->y + v1.y);
}

vec2 vec2::operator-(vec2 v1) {
	return vec2(this->x - v1.x, this->y - v1.y);
}

vec2 vec2::operator*(float f) {
	return vec2(this->x * f, this->y * f);
}

vec2 vec2::operator/(float f) {
	return vec2(this->x / f, this->y / f);
}

vec3::vec3() {
}

vec3::vec3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void vec3::Subtract(vec3 v2) {
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
}

void vec3::MultScalar(float f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
}

void vec3::DivScalar(float f) {
	this->x /= f;
	this->y /= f;
	this->z /= f;
}

float vec3::Dot(vec3 v2) {
	return x * v2.x + y * v2.y + z * v2.z;
}

float vec3::GetMagnitude() {
	return sqrtf(x * x + y * y + z * z);
}

float vec3::GetMagnitudeSquared() {
	return x * x + y * y + z * z;
}

vec3 vec3::Normailize() {
	return *this / GetMagnitude();
}

vec3 vec3::Project(vec3 v2) {
	return v2 * (Dot(v2) / v2.GetMagnitudeSquared());
}

vec3 vec3::RotateZ(float rot) {
	double c{ cos(rot) }, s{ sin(rot) };
	return vec3(x * c - y * s, x * s + y * c, z);
}

float vec3::operator[](int i) {
	return *hold[i];
}

vec3 vec3::operator-() {
	return vec3(-x, -y, -z);
}

vec3 vec3::operator+(vec3 v2) {
	return vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

vec3 vec3::operator-(vec3 v2) {
	return vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

vec3 vec3::operator*(float f) {
	return vec3(this->x * f, this->y * f, this->z * f);
}

vec3 vec3::operator/(float f) {
	return vec3(this->x / f, this->y / f, this->z / f);
}

vec4::vec4() {
}

vec4::vec4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void vec4::Subtract(vec4 v2) {
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	this->w -= v2.w;
}

void vec4::MultScalar(float f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
	this->w *= f;
}

void vec4::DivScalar(float f) {
	this->x /= f;
	this->y /= f;
	this->z /= f;
	this->w /= f;
}

float vec4::Dot(vec4 v2) {
	return x * v2.x + y * v2.y + z * v2.z + w * v2.w;
}

float vec4::GetMagnitude() {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float vec4::GetMagnitudeSquared() {
	return x * x + y * y + z * z + w * w;
}

vec4 vec4::Normalize(vec4 v2) {
	return *this / GetMagnitude();
}

vec4 vec4::Project(vec4 v2) {
	return v2 * (Dot(v2) / v2.GetMagnitudeSquared());
}

float vec4::operator[](int i) {
	return *hold[i];
}

vec4 vec4::operator+(vec4 v2) {
	return vec4(this->x + v2.x, this->y + v2.y, this->z + v2.z, this->z + v2.w);
}

vec4 vec4::operator-(vec4 v2) {
	return vec4(this->x - v2.x, this->y - v2.y, this->z - v2.z, this->z - v2.w);
}

vec4 vec4::operator-() {
	return vec4(-this->x, -this->y, -this->z, -this->w);
}

vec4 vec4::operator*(float f) {
	return vec4(this->x * f, this->y * f, this->z * f, this->z * f);
}

vec4 vec4::operator/(float f) {
	return vec4(this->x / f, this->y / f, this->z / f, this->z / f);
}
