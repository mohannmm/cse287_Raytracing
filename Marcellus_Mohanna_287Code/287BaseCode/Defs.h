#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

// Glut takes care of all the system-specific chores required for creating windows, 
// initializing OpenGL contexts, and handling input events
#include <GL/freeglut.h>

// GLM math library includes (See http://glm.g-truc.net/0.9.7/glm-0.9.7.pdf)
#define GLM_FORCE_SWIZZLE  // Enable GLM "swizzle" operators

// Basic GLM functionality
#include <glm/glm.hpp> 
#include <glm/gtx/rotate_vector.hpp>

const float EPSILON = 1.0E-3f;		//!< default value used for "SMALL" tolerances.

const int TIME_INTERVAL = 100;		//!< default time interval used timers.
const int WINDOW_WIDTH = 500;		//!< default window width.
const int WINDOW_HEIGHT = 250;		//!< default window height.
const unsigned char ESCAPE = 27;	//!< escape key.
const int SLICES = 8;				//!< default value used when slicing up a curved object.

const float M_PI = std::acos(-1.0f);	//!< pi
const float M_2PI = 2 * M_PI;			//!< 2pi	(360 degrees)
const float M_PI_2 = M_PI / 2.0f;		//!< pi/2	(180 degrees)
const float M_PI_3 = M_PI / 3.0f;		//!< pi/3	(120 degrees)
const float M_PI_4 = M_PI / 4.0f;		//!< pi/4	(90 degrees)
const float M_PI_6 = M_PI / 6.0f;		//!< pi/6	(60 degrees)
const float M_PI_12 = M_PI / 12.0f;		//!< pi/12	(30 degrees)

const glm::vec3 ORIGIN3D = glm::vec3(0.0f, 0.0f, 0.0f);				//!< (0, 0, 0)
const glm::vec4 ORIGIN3DHOMO = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);	//!< (0, 0, 0)
const glm::vec2 ORIGIN2D = glm::vec2(0.0f, 0.0f);					//!< (0, 0)
const glm::vec3 ORIGIN2DHOMO = glm::vec3(0.0f, 0.0f, 1.0f);			//!< (0, 0, 1)

const glm::vec3 ZEROVEC = glm::vec3(0.0f, 0.0f, 0.0f);			//!< <0, 0, 0>
const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);			//!< <1, 0, 0>
const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);			//!< <0, 1, 0>
const glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);			//!< <0, 0, 1>

/**
 * @struct	Window
 * @brief	Represents a positionless rectangle, with a particular dimension
 */

struct Window {
	int width;			//!< width of window
	int height;			//!< height of window
	Window(int W, int H);
	int area() const;
	float aspectRatio() const;
};

/**
 * @struct	BoundingBox
 * @brief	A bounding box in 2D.
 */

struct BoundingBox {
	float lx;		//!< lower left corner's x value
	float ly;		//!< lower left corner's y value
	float rx;		//!< upper right corner's x value
	float ry;		//!< upper right corner's y value
	BoundingBox(float left, float right, float bottom, float top);
	float width() const;
	float height() const;
	float aspectRatio() const;
};

/**
 * @struct	BoundingBox3D
 * @brief	Represents a bounding box in 3D.
 */

struct BoundingBox3D {
	float lx;	//!< lower left x
	float ly;	//!< lower left y
	float lz;	//!< lower left z
	float rx;	//!< upper right x
	float ry;	//!< upper right y
	float rz;	//!< upper right z
	BoundingBox3D(float left, float right, float bottom, float top, float back, float front);
	float width() const;
	float height() const;
	float depth() const;
};

/**
 * @struct	Frame
 * @brief	Represents a coordinate frame
 */

struct Frame {
	glm::vec3 u;		//!< "x" axis in frame
	glm::vec3 v;		//!< "y" axis in frame
	glm::vec3 w;		//!< "z" axis in frame
	glm::vec3 origin;	//!< location of frame's origin
	glm::mat4 inverse;	//!< The inverse of the frame's transformation
	Frame();
	Frame(const glm::vec3 &O, const glm::vec3 &U, const glm::vec3 &V, const glm::vec3 &W);
	glm::vec3 toFrameCoords(const glm::vec3 &pt) const;
	glm::vec3 toWorldCoords(const glm::vec3 &pt) const;
	glm::vec3 toFrameVector(const glm::vec3 &pt) const;
	glm::vec3 toWorldVector(const glm::vec3 &pt) const;
	void setFrame(const glm::vec3 &O, const glm::vec3 &U, const glm::vec3 &V, const glm::vec3 &W);
	static Frame createOrthoNormalBasis(const glm::vec3 &pos, const glm::vec3 &w, const glm::vec3 &up);
	friend std::ostream &operator <<(std::ostream &os, const Frame &frame);
protected:
	void setInverse();
};