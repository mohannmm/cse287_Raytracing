#include <ctime>
#include <vector>
#include "defs.h"
#include "Utilities.h"
#include "FrameBuffer.h"
#include "ColorAndMaterials.h"
#include "Rasterization.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void closed5x5Square(int x, int y, color C) {
	for (int i = x - 2; i <= x + 2; i++) {
		drawLine(frameBuffer, i, y - 2, i, y + 2, C);
	}
}

void closed5x5Square(const glm::vec2 &centerPt, color C) {
	for (int i = centerPt.x - 2; i <= centerPt.x + 2; i++) {
		drawLine(frameBuffer, i, centerPt.y - 2, i, centerPt.y + 2, C);
	}
}

void open5x5Square(const glm::vec2 &centerPt, color C) {
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y - 2, centerPt.x - 2, centerPt.y + 2, C); //left
	drawLine(frameBuffer, centerPt.x + 2, centerPt.y - 2, centerPt.x + 2, centerPt.y + 2, C); //right
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y - 2, centerPt.x + 2, centerPt.y - 2, C); //let
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y + 2, centerPt.x + 2, centerPt.y + 2, C); //right
}

void pieChart(const glm::vec2 &centerPt, float rad, float perc, const color &C1, const color &C2) {
	float pie1 = M_2PI * (1.0f - perc);
	float pie2 = M_2PI * perc;
	glm::vec2 shiftedCenter(centerPt.x + 25, centerPt.y);

	//Left Piece
	drawArc(frameBuffer, centerPt, rad, pie2/2, pie1, C1);
	drawLine(frameBuffer, centerPt, pointOnCircle(centerPt, rad, pie2 / 2), C1);
	drawLine(frameBuffer, centerPt, pointOnCircle(centerPt, rad, -pie2 / 2), C1);

	//Right Piece
	drawArc(frameBuffer, shiftedCenter, rad, -pie2/2, pie2, C2);
	drawLine(frameBuffer, shiftedCenter, pointOnCircle(shiftedCenter, rad, pie2 / 2), C2);
	drawLine(frameBuffer, shiftedCenter, pointOnCircle(shiftedCenter, rad, -pie2 / 2), C2);
}

void render() {
	frameBuffer.clearColorAndDepthBuffers();

	closed5x5Square(50, 50, red);
	closed5x5Square(glm::vec2(100, 50), green);
	open5x5Square(glm::vec2(150, 50), blue);
	pieChart(glm::vec2(250, 100), 50, 0.25, red, green);

	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ESCAPE:	glutLeaveMainLoop();
					break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLuint world_Window = glutCreateWindow(__FILE__);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);

	frameBuffer.setClearColor(black);

	glutMainLoop();

	return 0;
}
