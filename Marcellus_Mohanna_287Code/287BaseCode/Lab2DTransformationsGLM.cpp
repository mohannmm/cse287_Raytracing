#include <ctime>
#include <iostream>
#include "ColorAndMaterials.h"
#include "FrameBuffer.h"
#include "Utilities.h"
#include "Rasterization.h"

FrameBuffer colorBuffer(500, 500);
const int N = 50;
static int ROTDEG = 0, PLANETROTDEG = 0;
static int BOUNCEDIST = 5;
static bool BOUNCEDIR = true;

int windowWidth, windowHeight;

std::vector<glm::vec3> triangleVertices = { glm::vec3(-2 * N,2 * N,1), glm::vec3(-N,2 * N,1), glm::vec3(-1.5f*N,3 * N,1) };
std::vector<glm::vec3> square1Vertices = { glm::vec3(-N,-N,1), glm::vec3(N,-N,1),
						glm::vec3(N,N,1), glm::vec3(-N,N,1) };
std::vector<glm::vec3> square2Vertices = { glm::vec3(3 * N,-2 * N,1), glm::vec3(3 * N,-3 * N,1),
	glm::vec3(2 * N,-3 * N,1), glm::vec3(2 * N,-2 * N,1) };

int displayedProblem = 0;

std::vector<glm::vec3> transformVertices(const glm::mat3 &transMatrix, const std::vector<glm::vec3> &vertices) {
	std::vector<glm::vec3> transformedVertices;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		glm::vec3 vt(transMatrix * vertices[i]);
		transformedVertices.push_back(vt);
	}

	return transformedVertices;
}
void drawWirePolygonWithShift(std::vector<glm::vec3> verts, const color &C) {
	int W2 = colorBuffer.getWindowWidth()/2;
	int H2 = colorBuffer.getWindowHeight()/2;
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += W2;
		verts[i].y += H2;
	}
	drawWirePolygon(colorBuffer, verts, C);
}
void drawOne(const glm::mat3 &TM, const std::vector<glm::vec3> &verts, bool drawAxis = true) {
	std::vector<glm::vec3> vertsTransformed = transformVertices(TM, verts);
	drawWirePolygonWithShift(verts, black);
	drawWirePolygonWithShift(vertsTransformed, red);
	if (drawAxis) {
		drawAxisOnWindow(colorBuffer);
	}
}
void drawAll(const glm::mat3 &TM) {
	drawOne(TM, triangleVertices, false);
	drawOne(TM, square1Vertices, false);
	drawOne(TM, square2Vertices, false);
	drawAxisOnWindow(colorBuffer);
}

// Draw all the shapes, transformed by S(2, 0.5)
void scaleBy2xOneHalf() {
	drawAll(S(2, 0.5));
}

// Draw square1, transformed by T(50, 50)
void translate50_50() {
	drawOne(T(50,50) , square1Vertices);
}

// Draw all the shapes, transformed by R(45)
void rotate45() {
	drawAll(R(45));
}

// Draw all the shapes, transformed by R(-10)
void rotateNeg10() {
	drawAll(R(-10));
}

// Draw all shapes, reflected across the Y axis
void reflectAcrossYaxis() {
	drawAll(S(-1, 1));
}

// Draw all shapes, reflected across the origin
void reflectAcrossOrigin() {
	drawAll(S(-1, -1));
}

// Draw only triangle, scaled 2X about its center (-1.5N, 2.5N)
void scale2XAboutCenterOfTriangle() {
	drawOne(T(-1.5*N, 2.5*N) * S(2,2) * T(1.5*N, -2.5*N), triangleVertices);
}

// Draw all shapes, reflected across y=x+50
void reflectAcrossLineYeqXplus50() {
	drawAll(T(0, 50) * R(-45) * S(-1, 1) * R(45) * T(0, -50));
}

// Draw all shapes, reflected across y=2x-100
void reflectAcrossLineYeq2Xminus100() {
	drawAll(T(0, -100) * R(-26.565f) * S(-1, 1) * R(26.565f) * T(0, +100));
}

// Animate the rotation of the square1
void animationOfRotationByAngle() {
	drawOne(R(++ROTDEG), square1Vertices);
	ROTDEG = ROTDEG % 360;
}

// Animate the bouncing of all shapes left-right-left-etc
void animationBounceSideToSide() {
	if(BOUNCEDIR)
		drawAll(T(BOUNCEDIST, 0));
	else
		drawAll(T(-BOUNCEDIST, 0));

	BOUNCEDIR = !BOUNCEDIR;
}

// Horizontally shear square 1 by factor 0.5
void horzShearOneHalf() {
	glm::mat3 mat(1, 0.0f, 0.0f, 0.5f, 1, 0.0f, 0.0f, 0.0f, 1.0f);
	drawOne(T(0, 0), transformVertices(mat, square1Vertices));
}

// Vertically shear square 1 by factor 0.5
void vertShearOneHalf() {
	glm::mat3 mat(1, 0.5f, 0.0f, 0.0f, 1, 0.0f, 0.0f, 0.0f, 1.0f);
	drawOne(T(0, 0), transformVertices(mat, square1Vertices));
}

// Render square1 so that it rotates about its own axis, and then orbits the origin.
void squareRotatingAroundOwnAxisAndAroundSun() {
	drawOne(R(ROTDEG) * T(150, 0) *R (ROTDEG), square1Vertices);
	ROTDEG = ++ROTDEG % 360;
}

struct DisplayFunc {
	void(*f)();
	std::string name;
	DisplayFunc(void(*func)(), char *N) : f(func), name(N) {}
};

#define FUNC(F) DisplayFunc(F, #F)
std::vector<DisplayFunc> funcs = { FUNC(scaleBy2xOneHalf),
	FUNC(translate50_50),
	FUNC(rotate45),
	FUNC(rotateNeg10),
	FUNC(reflectAcrossYaxis),
	FUNC(reflectAcrossOrigin),
	FUNC(scale2XAboutCenterOfTriangle),
	FUNC(reflectAcrossLineYeqXplus50),
	FUNC(reflectAcrossLineYeq2Xminus100),
	FUNC(animationOfRotationByAngle),
	FUNC(animationBounceSideToSide),
	FUNC(horzShearOneHalf),
	FUNC(vertShearOneHalf),
	FUNC(squareRotatingAroundOwnAxisAndAroundSun),
};

void render() {
	colorBuffer.clearColorAndDepthBuffers();
	(*funcs[displayedProblem].f)();				// call the correct function
	colorBuffer.showColorBuffer();
}

void resize(int width, int height) {
	colorBuffer.setFrameBufferSize(width, height);
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

void timer(int id) {
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	const float INC = 0.5f;
	switch (key) {
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}
void problemMenu(int value) {
	if (value < (int)funcs.size()) {
		displayedProblem = value;
		glutSetWindowTitle(funcs[displayedProblem].name.c_str());
	} else {
		glutLeaveMainLoop();
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	GLuint world_Window = glutCreateWindow(__FILE__);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(TIME_INTERVAL, timer, 0);

	int menu1id = glutCreateMenu(problemMenu);
	for (unsigned int i = 0; i < funcs.size(); i++) {
		glutAddMenuEntry(funcs[i].name.c_str(), i);
	}
	glutAddMenuEntry("Quit", funcs.size());
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	colorBuffer.setClearColor(white);

	glutMainLoop();

	return 0;
}