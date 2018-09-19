#include <ctime>
#include <utility>
#include <cctype>
#include <ctime> 

#include "ColorAndMaterials.h"
#include "FrameBuffer.h"
#include "IScene.h"
#include "IShape.h"
#include "RayTracer.h"
#include "Camera.h"
#include "Image.h"

int main(int argc, char *argv[]) {
	glm::vec3 A(0, 0, 0);
	glm::vec3 B(5, 2, -3);
	glm::vec3 C(4, 4, 0);
	const glm::vec3 &THEVERT = B;

	// 3 Ambient, 3 diffuse, 3 specular
	Material mat(std::vector<float>{0.4f, 0.5f, 0.6f, 0.9f, 1.0f, 0.9f, 0.9f, 0.8f, 0.7f, 1.0f});
	float shininess = 1;

	// 3 Ambient, 3 diffuse, 3 specular
	LightColor lightColor(std::vector<float>{0.3f, 0.2f, 0.1f, 1, 1, 1, 0.5f, 0.6f, 0.7f});
	LightAttenuationParameters ATparams(1, 2, 0);

	glm::vec3 eyePos(3, 0, 1);
	glm::vec3 lightPos(6, 1, 0);
	glm::vec3 n = normalFrom3Points(A, B, C);
	glm::vec3 l = glm::normalize(lightPos - THEVERT);
	glm::vec3 v = glm::normalize(eyePos - THEVERT);
	glm::vec3 r = 2.0f * glm::dot(l, n) * n - l;
	//::vec3 r = glm::reflect(-l, n);   glm::reflect requires a negated light vector

	std::cout << "n: " << n << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "l: " << l << std::endl;
	std::cout << "r: " << r << std::endl;

	color amb = ambientColor(mat.ambient, lightColor.ambient);
	color diff = diffuseColor(mat.diffuse, lightColor.diffuse, l, n);
	color spec = specularColor(mat.specular, lightColor.specular, shininess, r, v);
	color sum = glm::clamp(amb + diff + spec, 0.0f, 1.0f);

	std::cout << "Ambient: " << amb << std::endl;
	std::cout << "Diffuse: " << diff << std::endl;
	std::cout << "Specular: " << spec << std::endl;
	std::cout << "Summation: " << sum << std::endl;
	color COLOR = totalColor(mat, lightColor, v, n, lightPos, THEVERT, false, ATparams);
	std::cout << COLOR << std::endl;

	float dist = glm::distance(lightPos, THEVERT);
	std::cout << "Attenuation factor: " << ATparams.factor(dist) << std::endl;

	std::cout << std::endl;
	HitRecord hit;
	hit.interceptPoint = THEVERT;
	hit.material = mat;
	hit.surfaceNormal = n;

	AmbientLight ambientLight(lightColor.ambient);
	PositionalLight positionalLight(lightPos, lightColor);

	// The camera's origin is important at this point (but not u, v, w)
	PerspectiveCamera camera(eyePos, glm::vec3(0,0,0), glm::vec3(0,1,0), M_PI_2);
	Frame eyeFrame = camera.cameraFrame;

	color ambientOutput = ambientLight.illuminate(hit, v, eyeFrame, false);
	color positionalOutput = positionalLight.illuminate(hit, v, eyeFrame, false);
	color positionalOutputInShadow = positionalLight.illuminate(hit, v, eyeFrame, true);

	std::cout << "Ambient light: " << ambientOutput << std::endl;
	std::cout << "Positional light: " << positionalOutput << std::endl;
	std::cout << "Positional light (shadow): " << positionalOutputInShadow << std::endl;

	return 0;
}
/*
n: [ 0.57735 -0.57735 0.57735 ]
v: [ -0.408248 -0.408248 0.816497 ]
l: [ 0.301511 -0.301511 0.904534 ]
r: [ 0.703526 -0.703526 0.100504 ]
Ambient: [ 0.12 0.1 0.06 ]
Diffuse: [ 0.783349 0.870388 0.783349 ]
Specular: [ 0.0369274 0.0393893 0.0402099 ]
Summation: [ 0.940277 1 0.883559 ]
Attenuation factor: 0.131006

Ambient light: [ 0.12 0.1 0.06 ]
Positional light: [ 0.940277 1 0.883559 ]
Positional light (shadow): [ 0.12 0.1 0.06 ]
*/