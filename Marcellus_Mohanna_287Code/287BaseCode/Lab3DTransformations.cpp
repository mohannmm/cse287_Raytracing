#include <ctime> 
#include <iostream> 
#include <algorithm>
#include <cmath>

#include "EShape.h"
#include "FrameBuffer.h"
#include "Raytracer.h"
#include "IScene.h"
#include "Light.h"
#include "Camera.h"
#include "Utilities.h"
#include "VertexOps.h"

PositionalLightPtr theLight = new PositionalLight(glm::vec3(2, 1, 3), pureWhiteLight);
std::vector<LightSourcePtr> lights = { theLight };

const float WIDTH = 10.0f;
const int DIV = 20;

glm::vec3 position(0, 1, 4);
float angle = 0;
bool isMoving = true;
bool twoViewOn = false;
const float SPEED = 0.1f;

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

EShapeData plane = EShape::createECheckerBoard(copper, polishedCopper, 10, 10, 10);
EShapeData cone1 = EShape::createECone(gold, 0.5, 0.5, 10, 10);
EShapeData cone2 = EShape::createECone(brass, 0.5, 0.5, 10, 10);
EShapeData cyl1 = EShape::createEClosedCylinder(silver, 0.5f, 1, 20, 20);
EShapeData cyl2 = EShape::createECylinder(silver, 0.5f, 1, 20, 20);

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, glm::mat4());
	VertexOps::render(frameBuffer, cone1, lights, Ry(2*angle)* T(0, 1, -3) * Rx(4*angle));
	VertexOps::render(frameBuffer, cone2, lights, T(2, 1, 0) * Rx(3*angle));
	VertexOps::render(frameBuffer, cyl1, lights, T(-2, 0, 0) * Rx(3*angle));
	VertexOps::render(frameBuffer, cyl2, lights, T(0, 0, 1));
}

static void render() {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	VertexOps::viewingTransformation = glm::lookAt(position, ORIGIN3D, Y_AXIS);
	float AR = (float)width / height;
	VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);
	VertexOps::setViewport(0.0f, (float)width - 1, 0.0f, (float)height - 1);
	renderObjects();
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	float AR = (float)width / height;

	VertexOps::setViewport(0.0f, (float)width - 1, 0.0f, (float)height - 1);
	VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	const float INC = 0.5f;
	switch (key) {
	case 'X':
	case 'x': theLight->lightPosition.x += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'Y':
	case 'y': theLight->lightPosition.y += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'Z':
	case 'z': theLight->lightPosition.z += (isupper(key) ? INC : -INC);
				std::cout << theLight->lightPosition << std::endl;
				break;
	case 'P':
	case 'p':	isMoving = !isMoving;
				break;
	case 'C':
	case 'c':	break;
	case '?':	twoViewOn = !twoViewOn;
				break;
	case ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		std::cout << (int)key << "unmapped key pressed." << std::endl;
	}

	glutPostRedisplay();
}

static void special(int key, int x, int y) {
	static const float rotateInc = glm::radians(10.0f);
	switch (key) {
	case(GLUT_KEY_LEFT):
		break;
	case(GLUT_KEY_RIGHT):
		break;
	case(GLUT_KEY_DOWN):
		break;
	case(GLUT_KEY_UP):
		break;
	}
	glutPostRedisplay();
}

static void timer(int id) {
	if (isMoving) {
		angle += glm::radians(5.0f);
	}
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {

	std::cout << glm::perspective(glm::radians(90.f), 2.0f, 1.0f, 21.0f) << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLuint world_Window = glutCreateWindow(extractBaseFilename(__FILE__).c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);

	frameBuffer.setClearColor(lightGray);

	glutMainLoop();







	return 0;
}