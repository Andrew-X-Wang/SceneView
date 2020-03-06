#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace glm;

const float EPSILON = 1e-20;
#define IN_RANGE(a,b)   (((a>(b-EPSILON))&&(a<(b+EPSILON)))?1:0)

#define DEFAULT_FOCUS_LENGTH 1.0f
#define NEAR_PLANE 0.01f
#define FAR_PLANE 20.0f
#define VIEW_ANGLE 60.0f
#define PI pi<float>()


class Camera {
public:
	float rotU, rotV, rotW;  //values used by the callback in main.cpp

	Camera();
	~Camera();

	void reset();
	void orientLookAt(vec3 eyePoint, vec3 focusPoint, vec3 upVec);
	void orientLookVec(vec3 eyePoint, vec3 lookVec, vec3 upVec);
	void setViewAngle(float _viewAngle);
	void setNearPlane(float _nearPlane);
	void setFarPlane(float _farPlane);
	void setUpVec(vec3 _upVec);
	void setEyePoint(vec3 _eyePoint);
	void setLookVec(vec3 _lookVec);
	void setScreenSize(int _screenWidth, int _screenHeight);
	void setRotUVW(float u, float v, float w);  //called by main.cpp as a part of the slider callback

	mat4 getUnhingeMatrix();
	mat4 getProjectionMatrix();
	mat4 getScaleMatrix();
	mat4 getInverseScaleMatrix();
	mat4 getModelViewMatrix();
	mat4 getInverseModelViewMatrix();

	void rotateV(float degree);
	void rotateU(float degree);
	void rotateW(float degree);

	void rotate(vec3 point, vec3 axis, float degree);
	void translate(vec3 v);

	vec3 getEyePoint();
	vec3 getLookVector();
	vec3 getUpVector();
	vec3 getU();
	vec3 getV();
	vec3 getW();
	float getViewAngle();
	float getNearPlane();
	float getFarPlane();
	int getScreenWidth();
	int getScreenHeight();
	float getFilmPlanDepth();
	float getScreenWidthRatio();

private:
	float viewAngle, filmPlanDepth;
	vec3 eyePoint, lookVec, upVec;
	mat4 rotation, translation;
	float nearPlane, farPlane;
	int screenWidth, screenHeight;
	float screenWidthRatio;
};
#endif

