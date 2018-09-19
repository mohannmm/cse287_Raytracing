#include <iostream>
#include "Defs.h"
#include "Utilities.h"

int main(int argc, char *argv[]) {
	glm::vec2 a(2, 3);
	glm::vec2 b(-3, 2);
	glm::vec2 c(1, 0);
	glm::vec3 diag3Da(1, 1, 1);
	glm::vec3 diag3Db(1, 1, 0);
	glm::vec3 diag3Dc(0, 1, -1);

	std::cout << doubleIt(a) << std::endl;
	std::cout << myNormalize(diag3Da) << std::endl;
	std::cout << isOrthogonal(diag3Da, diag3Dc) << std::endl;

	std::cout << cosBetween(a, b) << std::endl;
	std::cout << cosBetween(diag3Da, diag3Db) << std::endl;
	std::cout << radsBetween(a, b) << std::endl;
	std::cout << radsBetween(diag3Da, diag3Db) << std::endl;
	std::cout << project(diag3Da, glm::vec3(1, 0, 1)) << std::endl;
	std::cout << rotate90CCW(a) << std::endl;

	std::cout << areaOfParallelogram(glm::vec3(1, 0, 0), glm::vec3(1, 1, 0)) << std::endl;
	std::cout << areaOfTriangle(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0)) << std::endl;
	std::cout << isOrthoNormalBasis(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0,0,1)) << std::endl;
	std::cout << isRightHandedOrthoNormalBasis(glm::vec3(0, 0, -1), glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0)) << std::endl;
	std::cout << pointingVector(ORIGIN3D, diag3Da) << std::endl;
	std::cout << normalFrom3Points(glm::vec3(0,0,0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1)) << std::endl;
	std::cout << normalFrom3Points({ glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1) }) << std::endl;
}