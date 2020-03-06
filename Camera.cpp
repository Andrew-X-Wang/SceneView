#include "Camera.h"

Camera::Camera() {
	reset();
}

Camera::~Camera() {
}

void Camera::reset() {
	orientLookAt(vec3(0.0f, 0.0f, DEFAULT_FOCUS_LENGTH), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	setViewAngle(VIEW_ANGLE);
	setNearPlane(NEAR_PLANE);
	setFarPlane(FAR_PLANE);
	screenWidth = screenHeight = 200;
	screenWidthRatio = 1.0f;
	rotU = rotV = rotW = 0;
}

//called by main.cpp as a part of the slider callback for controlling rotation
// the reason for computing the diff is to make sure that we are only incrementally rotating the camera
void Camera::setRotUVW(float u, float v, float w) {
	float diffU = u - rotU;
	float diffV = v - rotV;
	float diffW = w - rotW;
	rotateU(diffU);
	rotateV(diffV);
	rotateW(diffW);
	rotU = u;
	rotV = v;
	rotW = w;
}


void Camera::orientLookAt(vec3 eyePoint, vec3 lookatPoint, vec3 upVec) {
	setEyePoint(eyePoint);
	setUpVec(upVec);
	setLookVec(lookatPoint - eyePoint);
}


void Camera::orientLookVec(vec3 eyePoint, vec3 lookVec, vec3 upVec) {
	setEyePoint(eyePoint);
	setUpVec(upVec);
	setLookVec(lookVec);
}

mat4 Camera::getScaleMatrix() {
	mat4 scaleMat4 = mat4(1.0f);
	float widthAngle = viewAngle * getScreenWidthRatio();

	scaleMat4[0][0] = 1.0f / (tan(widthAngle * 0.5f * (PI / 180)) * farPlane);
	scaleMat4[1][1] = 1.0f / (tan(viewAngle * 0.5f * (PI / 180)) * farPlane);
	scaleMat4[2][2] = 1.0f / farPlane;

	return scaleMat4;
}

mat4 Camera::getInverseScaleMatrix() {
	return inverse(getScaleMatrix());
}

mat4 Camera::getUnhingeMatrix() {
	float c = (-1.0f * nearPlane) / farPlane;
	mat4 unhingeMat4 = mat4(1.0f);

	unhingeMat4[2][2] = (-1.0f) / (c + 1.0f);
	unhingeMat4[3][2] = c / (c + 1.0f);
	unhingeMat4[2][3] = (-1.0f);
	unhingeMat4[3][3] = 0.0f;

	return unhingeMat4;
}

mat4 Camera::getProjectionMatrix() {
	mat4 projMat4 = getUnhingeMatrix() * getScaleMatrix();
	return projMat4;
}

mat4 Camera::getModelViewMatrix() {
	mat4 rotation = mat4(1.0f);
	vec3 w = getW();
	vec3 u = getU();
	vec3 v = getV();
	rotation[0][0] = u.x;
	rotation[1][0] = u.y;
	rotation[2][0] = u.z;
	rotation[0][1] = v.x;
	rotation[1][1] = v.y;
	rotation[2][1] = v.z;
	rotation[0][2] = w.x;
	rotation[1][2] = w.y;
	rotation[2][2] = w.z;

	mat4 translation = mat4(1.0f);
	translation[3][0] = -1.0f * eyePoint.x;
	translation[3][1] = -1.0f * eyePoint.y;
	translation[3][2] = -1.0f * eyePoint.z;

	return rotation * translation;
}

mat4 Camera::getInverseModelViewMatrix() {
	return inverse(getModelViewMatrix());
}

vec3 Camera::getW() {
	vec3 w = normalize(-1.0f * lookVec);
	return w;
}

vec3 Camera::getU() {
	vec3 w = getW();
	vec3 u = normalize(cross(upVec, w));
	return u;
}

vec3 Camera::getV() {
	vec3 w = getW();
	vec3 u = getU();
	vec3 v = cross(w, u);
	return v;
}

void Camera::rotateV(float degrees) {
	mat4 yaw = mat4(1.0f);
	yaw[0][0] = cos(degrees * (PI / 180));
	yaw[2][0] = sin(degrees * (PI / 180));
	yaw[0][2] = (-1.0f) * sin(degrees * (PI / 180));
	yaw[2][2] = cos(degrees * (PI / 180));

	vec4 lookVec4(lookVec, 0);

	setLookVec(yaw * lookVec4);
}

void Camera::rotateU(float degrees) {
	mat4 pitch = mat4(1.0f);
	pitch[1][1] = cos(degrees * (PI / 180));
	pitch[1][2] = sin(degrees * (PI / 180));
	pitch[2][1] = (-1.0f) * sin(degrees * (PI / 180));
	pitch[2][2] = cos(degrees * (PI / 180));

	vec4 lookVec4(lookVec, 0);
	vec4 upVec4(upVec, 0);

	setLookVec(pitch * lookVec4);
	setUpVec(pitch * upVec4);
}

void Camera::rotateW(float degrees) {
	mat4 roll = mat4(1.0f);
	roll[0][0] = cos((-1.0f) * degrees * (PI / 180));
	roll[0][1] = sin((-1.0f) * degrees * (PI / 180));
	roll[1][0] = (-1.0f) * sin((-1.0f) * degrees * (PI / 180));
	roll[1][1] = cos((-1.0f) * degrees * (PI / 180));

	vec4 upVec4(upVec, 0);

	setUpVec(roll * upVec4);
}

void Camera::rotate(vec3 point, vec3 axis, float degrees) {

}

void Camera::translate(vec3 v) {
	setEyePoint(v);
}

void Camera::setEyePoint(vec3 _eyePoint) {
	eyePoint = _eyePoint;
}

void Camera::setLookVec(vec3 _lookVec) {
	lookVec = normalize(_lookVec);
}

void Camera::setUpVec(vec3 _upVec) {
	upVec = normalize(_upVec);
}

void Camera::setViewAngle(float _viewAngle) {
	viewAngle = _viewAngle;
}

void Camera::setNearPlane(float _nearPlane) {
	nearPlane = _nearPlane;
}

void Camera::setFarPlane(float _farPlane) {
	farPlane = _farPlane;
}

void Camera::setScreenSize(int _screenWidth, int _screenHeight) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
}

vec3 Camera::getEyePoint() {
	return eyePoint;
}

vec3 Camera::getLookVector() {
	return lookVec;
}

vec3 Camera::getUpVector() {
	return upVec;
}

float Camera::getViewAngle() {
	return viewAngle;
}

float Camera::getNearPlane() {
	return nearPlane;
}

float Camera::getFarPlane() {
	return farPlane;
}

int Camera::getScreenWidth() {
	return screenWidth;
}

int Camera::getScreenHeight() {
	return screenHeight;
}

float Camera::getScreenWidthRatio() {
	screenWidthRatio = (float)getScreenWidth() / (float)getScreenHeight();
	return screenWidthRatio;
}
