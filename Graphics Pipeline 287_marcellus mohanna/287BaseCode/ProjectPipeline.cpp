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
glm::vec3 center(0, 0, 0);
glm::vec3 position(0, 1, 4);

//glm::mat4 calcVewingTransformation();
void changeCenter(float azimuthChange, float elevationChange);

float angle = 0;
float azimuth = 0, elevation = 0; //azimuth [-180,180] elevation [-80,80] 
bool isMoving = true;
bool twoViewOn = false;
const float SPEED = 0.1f;

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

EShapeData plane = EShape::createECheckerBoard(copper, polishedCopper, 10, 10, 10);
EShapeData cone1 = EShape::createECone(gold, 0.5, 0.5, 10, 10);
EShapeData cone2 = EShape::createECone(brass, 0.5, 0.5, 10, 10);
EShapeData cyl1 = EShape::createECylinder(blackRubber, 0.5f, 1, 200, 20);
EShapeData cyl2 = EShape::createECylinder(silver, 0.5f, 1, 20, 20);

std::vector<EShapeData> shapes = { plane, cone2, cone2, cyl1, cyl2 };

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, glm::mat4());
	VertexOps::render(frameBuffer, cone1, lights, T(0, 1, -3));
	VertexOps::render(frameBuffer, cone2, lights, T(2, 1, 0));
	VertexOps::render(frameBuffer, cyl1, lights, T(2, 0, 1) );
	VertexOps::render(frameBuffer, cyl2, lights, T(-2, 0.5, 1) * Rz(angle));
}


static void render() {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	float AR = (float)width / height;
	VertexOps::viewingTransformation = glm::lookAt(position, center, Y_AXIS);
	VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);

	if (twoViewOn) {
		VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);
		VertexOps::setViewport(0.0f, (float)(width / 2.0f) - 1, 0.0f, (float)height - 1);
		renderObjects();

		VertexOps::viewingTransformation = glm::lookAt(glm::vec3(3, 4, 2), ORIGIN3D, Y_AXIS);
		VertexOps::projectionTransformation = glm::perspective(M_PI_3, AR, 0.5f, 80.0f);
		VertexOps::setViewport((float)(width / 2.0f), (float)width - 1, 0.0f, (float)height - 1);
		renderObjects();
	}
	else {
		VertexOps::setViewport(0.0f, (float)width - 1, 0.0f, (float)height - 1);
		renderObjects();
	}
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

void changeCenter(float azimuthChange, float elevationChange) {
	azimuth = glm::clamp(azimuth + azimuthChange, -180.0f, 180.0f);
	elevation = glm::clamp(elevation + elevationChange, -80.0f, 80.0f);

	if (approximatelyZero(azimuthChange)) { //only elevation
		//center = glm::rotateY(center, glm::radians(azimuth));
		//glm::vec3 newCenter (center.x, center.y / std::cos(glm::radians(elevation)), center.z);
		//center = newCenter;
		center.y = 1 / std::cos(glm::radians(elevationChange));
	}
	if (approximatelyZero(elevation)) { //only azimuth

	}

	
}

static void special(int key, int x, int y) {
	static const float rotateInc = glm::radians(10.0f);
	switch (key) {
	case(GLUT_KEY_LEFT):
		changeCenter(-10, 0);
		break;
	case(GLUT_KEY_RIGHT):
		changeCenter(10, 0);
		break;
	case(GLUT_KEY_DOWN):
		changeCenter(0, -10);
		break;
	case(GLUT_KEY_UP):
		changeCenter(0, 10);
		break;
	}
	glutPostRedisplay();
}

static void timer(int id) {
	if (isMoving) {
		angle += glm::radians(5.0f);
		position.x = cos(angle / 5.0f) * 5; //50.0f;
		position.z = sin(angle / 5.0f) * 5; //50.0f;
	}
	glutTimerFunc(100, timer, 0);
	glutPostRedisplay();
}

static void mouse(int b, int s, int x, int y) {
	std::cout << x << std::endl;
	std::cout << y << std::endl;
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLuint world_Window = glutCreateWindow(extractBaseFilename(__FILE__).c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);

	frameBuffer.setClearColor(lightGray);

	glutMainLoop();

	return 0;
}