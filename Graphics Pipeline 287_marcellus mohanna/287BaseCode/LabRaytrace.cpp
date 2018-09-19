#include <ctime>
#include "Defs.h"
#include "IShape.h"
#include "FrameBuffer.h"
#include "Raytracer.h"
#include "IScene.h"
#include "Light.h"
#include "Image.h"
#include "Camera.h"
#include "Rasterization.h"
#include "Utilities.h"

int currLight = 0;
float z = 0.0f;
float inc = 0.2f;

std::vector<PositionalLightPtr> lights = {
						new PositionalLight(glm::vec3(10, 10, 10), pureWhiteLight),
						new SpotLight(glm::vec3(2, 5, -2), glm::vec3(0,-1,0), glm::radians(45.0f), pureWhiteLight)
};

PositionalLightPtr posLight = lights[0];
SpotLightPtr spotLight = (SpotLightPtr)lights[1];

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(lightGray);
PerspectiveCamera pCamera(glm::vec3(0, 5, 10), glm::vec3(0,5,0), Y_AXIS, M_PI_2);
OrthographicCamera oCamera(glm::vec3(0, 5, 10), glm::vec3(0, 5, 0), Y_AXIS, 25.0f);
RaytracingCamera *cameras[] = { &pCamera, &oCamera };
int currCamera = 0;
IScene scene(cameras[currCamera], true);

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);

	float N = 10.0f;
	cameras[currCamera]->changeConfiguration(glm::vec3(0, 5, 10), glm::vec3(0, 5, 0), Y_AXIS);
	rayTrace.raytraceScene(frameBuffer, 0, scene);

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	float totalTimeSec = (frameEndTime - frameStartTime) / 1000.0f;
	std::cout << "Render time: " << totalTimeSec << " sec." << std::endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	cameras[currCamera]->calculateViewingParameters(width, height);
	glutPostRedisplay();
	std::cout << cameras[currCamera]->getProjectionPlaneCoordinates(0, 0) << std::endl;
}

void buildScene() {
	IShape *plane = new IPlane(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ISphere *sphere1 = new ISphere(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f);
	ISphere *sphere2 = new ISphere(glm::vec3(-4.0f, 0.0f, -10.0f), 2.0f);
	IEllipsoid *ellipsoid = new IEllipsoid(glm::vec3(4.0f, 0.0f, 3.0f), glm::vec3(2.0f, 1.0f, 2.0f));

	scene.addObject(new VisibleIShape(plane, tin));
	scene.addObject(new VisibleIShape(sphere1, silver));
	scene.addObject(new VisibleIShape(sphere2, bronze));
	scene.addObject(new VisibleIShape(ellipsoid, redPlastic));

	scene.addObject(lights[0]);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case ESCAPE:
			glutLeaveMainLoop();
			break;
		default:
			std::cout << (int)key << "unmapped key pressed." << std::endl;
	}

	glutPostRedisplay();
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
	buildScene();

	rayTrace.defaultColor = green;
	glutMainLoop();

	return 0;
}



/*
int main(int argc, char *argv[])
{
	std::cout << "DoubleIT" << std::endl;
	std::cout << doubleIt(glm::vec2(0, 0)) << "   (" << glm::vec2(0, 0) << ")" << std::endl;
	std::cout << doubleIt(glm::vec2(-1, 2)) << "   (" << glm::vec2(-2, 4) << ")" << std::endl;
	std::cout << doubleIt(glm::vec2(.23, -.112)) << "   (" << glm::vec2(.46, -.224) << ")" << std::endl;
	std::cout << doubleIt(glm::vec2(3, 0)) << "   (" << glm::vec2(6, 0) << ")" << std::endl << std::endl;

	std::cout << "myNormalize" << std::endl;
	std::cout << myNormalize(glm::vec3(1, 1, 1)) << "   (" << glm::vec3(.557, .557, .557) << ")" << std::endl;
	std::cout << myNormalize(glm::vec3(1, 0, 0)) << "   (" << glm::vec3(1, 0, 0) << ")" << std::endl;
	std::cout << myNormalize(glm::vec3(-5, 6, 7)) << "   (" << glm::vec3(-.477, .572, .667) << ")" << std::endl;
	std::cout << myNormalize(glm::vec3(-3, -4, -5)) << "   (" << glm::vec3(-.424, -.566, -.707) << ")" << std::endl << std::endl;


	std::cout << "isOrthogonal" << std::endl;
	std::cout << isOrthogonal(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0)) << " (True)" << std::endl;
	std::cout << isOrthogonal(glm::vec3(1, 2, 3), glm::vec3(3, 2, 1)) << " (False)" << std::endl;
	std::cout << isOrthogonal(glm::vec3(1, 0, -1), glm::vec3(1, sqrt(2), 1)) << " (True)" << std::endl;
	std::cout << isOrthogonal(glm::vec3(3, 3, 3), glm::vec3(3, 3, 3)) << " (False)" << std::endl << std::endl;


	std::cout << "cosBetween" << std::endl;
	std::cout << cosBetween(glm::vec2(3, 2), glm::vec2(32, -12)) << " (.584)" << std::endl;
	std::cout << cosBetween(glm::vec2(-23, 1), glm::vec2(0, -.23)) << " (-.043)" << std::endl;
	std::cout << cosBetween(glm::vec2(1, 0), glm::vec2(0, 1)) << " (0)" << std::endl;
	std::cout << cosBetween(glm::vec2(-1234, 1234), glm::vec2(4321, -4321)) << " (-1)" << std::endl << std::endl;

	std::cout << "cosBetween 2" << std::endl;
	std::cout << cosBetween(glm::vec3(3, 2, 1), glm::vec3(32, -12, 14)) << " (.622)" << std::endl;
	std::cout << cosBetween(glm::vec3(-1, 23, 1), glm::vec3(0, 0, 1)) << " (.043)" << std::endl;
	std::cout << cosBetween(glm::vec3(-223, 223, 12345), glm::vec3(632, -234, -1)) << " (-.025)" << std::endl;
	std::cout << cosBetween(glm::vec3(1, 2, 3), glm::vec3(1, 2, 3)) << " (1)" << std::endl << std::endl;

	std::cout << "radsBetween" << std::endl;
	std::cout << radsBetween(glm::vec2(3, 2), glm::vec2(32, -12)) << " (.947)" << std::endl;
	std::cout << radsBetween(glm::vec2(-23, 1), glm::vec2(0, -.23)) << " (1.614)" << std::endl;
	std::cout << radsBetween(glm::vec2(1, 0), glm::vec2(0, 1)) << " (1.571)" << std::endl;
	std::cout << radsBetween(glm::vec2(-1234, 1234), glm::vec2(4321, -4321)) << " (-3.142)" << std::endl << std::endl;

	std::cout << "radsBetween 2" << std::endl;
	std::cout << radsBetween(glm::vec3(3, 2, 1), glm::vec3(32, -12, 14)) << " (.899)" << std::endl;
	std::cout << radsBetween(glm::vec3(-1, 23, 1), glm::vec3(0, 0, 1)) << " (1.527)" << std::endl;
	std::cout << radsBetween(glm::vec3(-223, 223, 12345), glm::vec3(632, -234, -1)) << " (1.597)" << std::endl;
	std::cout << radsBetween(glm::vec3(1, 2, 3), glm::vec3(1, 2, 3)) << " (0)" << std::endl << std::endl;


	std::cout << "project" << std::endl;
	std::cout << project(glm::vec3(1, 1, 1), glm::vec3(2, 2, 2)) << " ([1,1,1]" << std::endl;
	std::cout << project(glm::vec3(31, 98, -3), glm::vec3(32, 45, 3)) << " ([56.434,79.36,5.29]" << std::endl;
	std::cout << project(glm::vec3(-3, 42, -6), glm::vec3(1, 2, 4)) << " ([2.71,5.43,10.86]" << std::endl;
	std::cout << project(glm::vec3(2, 2, 2), glm::vec3(1, 1, 1)) << " ([2,2,2]" << std::endl << std::endl;

	std::cout << "rotate" << std::endl;
	std::cout << rotate90CCW(glm::vec2(1, 0)) << " ([0,1])" << std::endl;
	std::cout << rotate90CCW(glm::vec2(32, 43)) << " ([-43,32])" << std::endl;
	std::cout << rotate90CCW(glm::vec2(12.2, -1.3)) << " ([1.3,12.2])" << std::endl;
	std::cout << rotate90CCW(glm::vec2(2, 2)) << " ([-2,2])" << std::endl << std::endl;

	std::cout << "areaofparrallelogram" << std::endl;
	std::cout << areaOfParallelogram(glm::vec3(0, 0, 1), glm::vec3(1, 0, 0)) << " (1)" << std::endl;
	std::cout << areaOfParallelogram(glm::vec3(23, 3, 45), glm::vec3(-12, 0, -45)) << " (514.34)" << std::endl;
	std::cout << areaOfParallelogram(glm::vec3(-1111, -1111, -1111), glm::vec3(42, 42, 12345)) << " (19330366.16)" << std::endl;
	std::cout << areaOfParallelogram(glm::vec3(1, 0, 1000), glm::vec3(0, 1, 1000)) << " (1414.21)" << std::endl << std::endl;


	std::cout << "triangle" << std::endl;
	std::cout << areaOfTriangle(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)) << " (.87)" << std::endl;
	std::cout << areaOfTriangle(glm::vec3(23, -12, 0), glm::vec3(45, 1, 34), glm::vec3(9, 8, 12)) << " (549.79)" << std::endl;
	std::cout << areaOfTriangle(glm::vec3(-1, -2, -3), glm::vec3(3, 4, 5), glm::vec3(0, 0, 0)) << " (2.45)" << std::endl;
	std::cout << areaOfTriangle(glm::vec3(-1, -1, -1), glm::vec3(-1, 1, 1), glm::vec3(0, 0, 0)) << " (1.41)" << std::endl << std::endl;

	std::cout << "orthobasis" << std::endl;
	std::cout << isOrthoNormalBasis(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)) << " (1)" << std::endl;
	std::cout << isOrthoNormalBasis(glm::vec3(22, 0, 0), glm::vec3(0, 22, 0), glm::vec3(0, 0, 22)) << " (0)" << std::endl;
	std::cout << isOrthoNormalBasis(glm::vec3(-1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0)) << " (0)" << std::endl << std::endl;

	std::cout << "rightbasis" << std::endl;
	std::cout << isRightHandedOrthoNormalBasis(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)) << " (1)" << std::endl;
	std::cout << isRightHandedOrthoNormalBasis(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1)) << " (0)" << std::endl;
	std::cout << isRightHandedOrthoNormalBasis(glm::vec3(22, 0, 0), glm::vec3(0, 22, 0), glm::vec3(0, 0, 22)) << " (0)" << std::endl;

	std::cout << "pointing vec" << std::endl;
	std::cout << pointingVector(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0)) << " ([-1,0,0])" << std::endl;
	std::cout << pointingVector(glm::vec3(32, 87, 12), glm::vec3(-48, -43, -2)) << " ([-.521,-.849,-.091])" << std::endl;
	std::cout << pointingVector(glm::vec3(1, 0, 0), glm::vec3(2, -3, 4)) << " ([.196,-.588,.784])" << std::endl;
	std::cout << pointingVector(glm::vec3(1, 0, 0), glm::vec3(2, 0, 0)) << " ([1,0,0])" << std::endl << std::endl;

	std::cout << "norm3pts" << std::endl;
	std::cout << normalFrom3Points(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)) << "( [1,1,1])" << std::endl;
	std::cout << normalFrom3Points(glm::vec3(2, 3, 4), glm::vec3(-2, -3, -4), glm::vec3(0, 0, 1)) << "( [-6,4,0])" << std::endl;
	std::cout << normalFrom3Points(glm::vec3(1, 1, 1), glm::vec3(1, 2, 3), glm::vec3(3, 2, 1)) << "( [-2,4,-2])" << std::endl;
	std::cout << normalFrom3Points(glm::vec3(0, 2, 3), glm::vec3(1, 0, 3), glm::vec3(3, 2, 0)) << "( [2,1,2])" << std::endl << std::endl;



	std::cout << "norm3pts vec" << std::endl;
	std::cout << normalFrom3Points(std::vector<glm::vec3> { glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1) }) << "( [1,1,1])" << std::endl;
	std::cout << normalFrom3Points(std::vector<glm::vec3> {glm::vec3(2, 3, 4), glm::vec3(-2, -3, -4), glm::vec3(0, 0, 1)}) << "( [-6,4,0])" << std::endl;
	std::cout << normalFrom3Points(std::vector<glm::vec3> {glm::vec3(1, 1, 1), glm::vec3(1, 2, 3), glm::vec3(3, 2, 1) }) << "( [-2,4,-2])" << std::endl;
	std::cout << normalFrom3Points(std::vector<glm::vec3> {glm::vec3(0, 2, 3), glm::vec3(1, 0, 3), glm::vec3(3, 2, 0)}) << "( [2,1,2])" << std::endl << std::endl;


	float roots[2];
	int count;
	count = quadratic(0, 0, 0, roots);
	std::cout << "count" << count << std::endl;
	for (int i = 0; i < count; i++) {
		std::cout << "root" << i << ": " << roots[i] << std::endl;
	}
	
	std::vector<float> x = quadratic(0, 0, 0);

	//for (int i = 0; i < x.size; i++) {
	//	std::cout << "root" << i << ": " << x[i] << std::endl;
	//}



	return 0;
}
*/




