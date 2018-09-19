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

Image im1("usflag.ppm");

int currLight = 0;
float z = 0.0f;
float inc = 0.2f;
bool isAnimated = false;
int numReflections = 2;
int antiAliasing = 1;
bool twoViewOn = false;

std::vector<PositionalLightPtr> lights = {
	new PositionalLight(glm::vec3(10, 10, 10), yellow),
	new SpotLight(glm::vec3(2, 5, -2), glm::vec3(0,-1,0), glm::radians(45.0f), pureWhiteLight)
};

PositionalLightPtr posLight = lights[0];
SpotLightPtr spotLight = (SpotLightPtr)lights[1];

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(red);
PerspectiveCamera pCamera(glm::vec3(0, 10, 10), ORIGIN3D, Y_AXIS, M_PI_2);
IScene scene(&pCamera, true);

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);

	int left = 0;
	int right = frameBuffer.getWindowWidth() - 1;
	int bottom = 0;
	int top = frameBuffer.getWindowHeight() - 1;
	float N = 6.0f;
	pCamera.calculateViewingParameters(frameBuffer.getWindowWidth(), frameBuffer.getWindowHeight());
	pCamera.changeConfiguration(glm::vec3(-N, 5, -N), ORIGIN3D, Y_AXIS);

	if(antiAliasing == 1)
	rayTrace.raytraceScene(frameBuffer, numReflections, scene);
	else
	rayTrace.raytraceSceneAntiAliasing(frameBuffer, numReflections, scene);


	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	float totalTimeSec = (frameEndTime - frameStartTime) / 1000.0f;
	std::cout << "Render time: " << totalTimeSec << " sec." << std::endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	pCamera.calculateViewingParameters(width, height);
	glutPostRedisplay();
}
void buildScene() {
	IShape *plane = new IPlane(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//IShape *planeX = new IPlane(glm::vec3(0.0f, 5.0f, z), glm::vec3(0.0f, 0.0f, 1.0f)); //translucent
	ISphere *sphere = new ISphere(glm::vec3(-4.0f, 0.0f, 0.0f), 2.0f);
	ICylinderY *cylY = new ICylinderY(glm::vec3(2.0f, 0.0f, -8.0f), 1.0f, 3.0f); 
	ICylinderX *cylx = new ICylinderX(glm::vec3(6.0f, 0.0f, -7.0f), 1.0f, 3.0f);
	ICylinderYClosed *cylYC = new ICylinderYClosed(glm::vec3(2.0f, 0.0f, -4.0f), 1.0f, 3.0f);

	//cyl
	//cone

	VisibleIShape *p;
	scene.addObject(new VisibleIShape(plane, tin));
	//scene.addTransparentObject(new VisibleIShape(planeX, emerald.ambient), 0.25); // transluscent
	scene.addObject(new VisibleIShape(sphere, silver));
	scene.addObject(new VisibleIShape(cylx, redRubber));
	scene.addObject(new VisibleIShape(cylY, cyanPlastic));
	scene.addObject(p = new VisibleIShape(cylYC, cyanPlastic));

	p->setTexture(&im1);

	scene.addObject(lights[0]);
	scene.addObject(lights[1]);
}

void incrementClamp(float &v, float delta, float lo, float hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void incrementClamp(int &v, int delta, int lo, int hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void timer(int id) {
	if (isAnimated) {
		z += inc;
		if (z <= -5.0f) {
			inc = -inc;
		}
		else if (z >= 5.0f) {
			inc = -inc;
		}
	}
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	const float INC = 0.5f;
	switch (key) {
	case 'A':
	case 'a':	currLight = 0;
				std::cout << *lights[0] << std::endl;
				break;
	case 'B':
	case 'b':	currLight = 1;
				std::cout << *lights[1] << std::endl;
				break;
	case 'O':
	case 'o':	lights[currLight]->isOn = !lights[currLight]->isOn;
				std::cout << (lights[currLight]->isOn ? "ON" : "OFF") << std::endl;
				break;
	case 'V':
	case 'v':	lights[currLight]->isTiedToWorld = !lights[currLight]->isTiedToWorld;
				std::cout << (lights[currLight]->isTiedToWorld ? "World" : "Camera") << std::endl;
				break;
	case 'Q':
	case 'q':	lights[currLight]->setAttenuation(!lights[currLight]->attenuationIsTurnedOn);
				std::cout << (lights[currLight]->attenuationIsTurnedOn ? "Atten ON" : "Atten OFF") << std::endl;
				break;
	case 'W':
	case 'w':	incrementClamp(lights[currLight]->attenuationParams.constant, isupper(key) ? INC : -INC, 0.0f, 10.0f);
				std::cout << lights[currLight]->attenuationParams << std::endl;
				break;
	case 'E':
	case 'e':	incrementClamp(lights[currLight]->attenuationParams.linear, isupper(key) ? INC : -INC, 0.0f, 10.0f);
				std::cout << lights[currLight]->attenuationParams << std::endl;
				break;
	case 'R':
	case 'r':	incrementClamp(lights[currLight]->attenuationParams.quadratic, isupper(key) ? INC : -INC, 0.0f, 10.0f);
				std::cout << lights[currLight]->attenuationParams << std::endl;
				break;
	case 'X':
	case 'x':	lights[currLight]->lightPosition.x += (isupper(key) ? INC : -INC);
				std::cout << lights[currLight]->lightPosition << std::endl;
				break;
	case 'Y':
	case 'y':	 lights[currLight]->lightPosition.y += (isupper(key) ? INC : -INC);
				std::cout << lights[currLight]->lightPosition << std::endl;
				break;
	case 'Z':
	case 'z':	lights[currLight]->lightPosition.z += (isupper(key) ? INC : -INC);
				std::cout << lights[currLight]->lightPosition << std::endl;
				break;
	case 'J':
	case 'j':	spotLight->spotDirection.x += (isupper(key) ? INC : -INC);
				std::cout << spotLight->spotDirection << std::endl;
				break;
	case 'K':
	case 'k':	spotLight->spotDirection.y += (isupper(key) ? INC : -INC);
				std::cout << spotLight->spotDirection << std::endl;
				break;
	case 'L':
	case 'l':	spotLight->spotDirection.z += (isupper(key) ? INC : -INC);
				std::cout << spotLight->spotDirection << std::endl;
				break;
	case 'F':
	case 'f':	incrementClamp(spotLight->fov, isupper(key) ? 0.2f : -0.2f, 0.1f, M_PI);
				std::cout << spotLight->fov << std::endl;
				break;
	case 'D':
	case 'd':
	case 'P':
	case 'p':	isAnimated = !isAnimated;
				break;
	case 'C':
	case 'c':
				break;
	case 'U':
	case 'u':	break;
	case 'M':
	case 'm':	break;
	case '+':	antiAliasing = 3;
		std::cout << "Anti aliasing: " << antiAliasing << std::endl;
		break;
	case '-':	antiAliasing = 1;
		std::cout << "Anti aliasing: " << antiAliasing << std::endl;
		break;
	case '0':
	case '1':
	case '2':	numReflections = key - '0';
		std::cout << "Num reflections: " << numReflections << std::endl;
		break;
	case '?':	twoViewOn = !twoViewOn;
				break;
	case ESCAPE:
				glutLeaveMainLoop();
				break;
	default:	std::cout << (int)key << "unmapped key pressed." << std::endl;
	}

	glutPostRedisplay();
}

void special(int key, int x, int y) {
	const float INC = 0.5f;
	switch (key) {
	case GLUT_KEY_PAGE_DOWN: break;
	case GLUT_KEY_PAGE_UP: break;
	case GLUT_KEY_RIGHT: break;
	case GLUT_KEY_LEFT: break;
	default:
		std::cout << key << " special key pressed." << std::endl;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int X = x;
		int Y = frameBuffer.getWindowHeight() - 1 - y;
		color C = frameBuffer.getColor(X, Y);
		std::cout << "(" << X << "," << Y << ") = " << C << std::endl;
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
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutTimerFunc(TIME_INTERVAL, timer, 0);
	buildScene();

	glutMainLoop();

	return 0;
}