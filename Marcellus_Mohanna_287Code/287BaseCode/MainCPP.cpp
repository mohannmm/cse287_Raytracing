#include <ctime>
#include <utility>
#include <algorithm>
#include <cctype>

#include "ColorAndMaterials.h"
#include "FrameBuffer.h"
#include "IScene.h"
#include "IShape.h"
#include "RayTracer.h"
#include "Camera.h"
#include "Image.h"
#include "Utilities.h"

#define START()			int attempts = 0, correct = 0; \
						std::cout << "---------" << __FUNCTION__ << "---------" << std::endl;

#define END()			if (correct < attempts) std::cout << correct <<"/" << attempts << std::endl;
#define CHECK(VALUE)	attempts++; \
						if (!(VALUE)) { \
								std::cout << "ERR in " <<	\
											 __FUNCTION__ << " at " << __LINE__ << std::endl; \
						} else { \
								correct++; \
						}

namespace CPP {
	template <class T> bool OK(const T &a, const T &b) {
		return a == b;
	}

	void cosBetweenTestd() {
		START();

		glm::vec2 v1(1, 1);
		glm::vec2 v2(4, -4);
		glm::vec2 v3(1, 0);
		float l1 = glm::length(v1);
		float l2 = glm::length(v1);
		float dp = glm::dot(v1, v1);
		float x = cosBetween(v1, v1);

		CHECK(approximatelyEqual(cosBetween(v1, v2), 0));
		CHECK(approximatelyEqual(cosBetween(v2, v1), 0));
		CHECK(approximatelyEqual(cosBetween(v1, v3), 1 / std::sqrt(2.0f)));
		CHECK(approximatelyEqual(cosBetween(v3, v1), 1 / std::sqrt(2.0f)));

		END();
	}

	void radsBetweenTeste() {
		START();
		glm::vec2 v1(1, 1);
		glm::vec2 v2(4, -4);
		glm::vec2 v3(1, 0);

		CHECK(approximatelyEqual(radsBetween(v1, v2), M_PI_2));
		CHECK(approximatelyEqual(radsBetween(v2, v1), M_PI_2));
		CHECK(approximatelyEqual(radsBetween(v1, v1), 0));
		CHECK(approximatelyEqual(radsBetween(v2, v2), 0));
		CHECK(approximatelyEqual(radsBetween(v1, v3), M_PI_4));
		CHECK(approximatelyEqual(radsBetween(v3, v1), M_PI_4));

		END();
	}
	void radsBetweenTestf() {
		START();
		glm::vec3 v1(0, 1, 1);
		glm::vec3 v2(0, 4, -4);
		glm::vec3 v3(0, 1, 0);

		CHECK(approximatelyEqual(radsBetween(v1, v2), M_PI_2));
		CHECK(approximatelyEqual(radsBetween(v2, v1), M_PI_2));
		CHECK(approximatelyEqual(radsBetween(v1, v1), 0));
		CHECK(approximatelyEqual(radsBetween(v2, v2), 0));
		CHECK(approximatelyEqual(radsBetween(v1, v3), M_PI_4));
		CHECK(approximatelyEqual(radsBetween(v3, v1), M_PI_4));

		glm::vec3 v4(-std::sqrt(3), -1, 0);
		glm::vec3 v5(2 * std::sqrt(3), -2, 0);
		CHECK(approximatelyEqual(radsBetween(v4, v5), 2 * M_PI_3));
		CHECK(approximatelyEqual(radsBetween(v5, v4), 2 * M_PI_3));

		END();
	}

	void normalizeDegreesTesta() {
		START();

		for (int i = 0; i<1000; i++) {
			CHECK(approximatelyEqual(normalizeDegrees((float)i), (float)(i % 360)));
			int negAnswer = 360 - i % 360;
			if (negAnswer == 360) negAnswer = 0;

			CHECK(approximatelyEqual(normalizeDegrees((float)(-i)), (float)(negAnswer)));
		}

		END();
	}

	void rad2degTestb() {
		START();
		const int DIV = 20;
		const float ANGLE_INC = 2.0f * M_PI / DIV;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < DIV; j++) {
				float rads = ANGLE_INC * j + i * 2 * M_PI;
				CHECK(approximatelyEqual(rad2deg(rads), glm::degrees(rads)));
				CHECK(approximatelyEqual(rad2deg(-rads), glm::degrees(-rads)));
			}
		}

		END();
	}
	void deg2radTestc() {
		START();
		const int DIV = 20;
		const float ANGLE_INC = +360.0f / DIV;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < DIV; j++) {
				float degs = ANGLE_INC * j + i * 360;
				CHECK(approximatelyEqual(deg2rad(degs), glm::radians(degs)));
				CHECK(approximatelyEqual(deg2rad(-degs), glm::radians(-degs)));
			}
		}

		END();
	}

	void directionTesti() {
		START();
		CHECK(approximatelyEqual(directionInDegrees(0, 0, 1, 1), 45));
		CHECK(approximatelyEqual(directionInDegrees(1, 1, 10, 10), 45));
		CHECK(approximatelyEqual(normalizeDegrees(directionInDegrees(-1, -1, -1, -10)), 270));
		END();
	}
	void directionTestj() {
		START();
		CHECK(approximatelyEqual(normalizeDegrees(directionInDegrees(glm::vec2(1, 2), glm::vec2(1, 1))), 270));
		CHECK(approximatelyEqual(directionInDegrees(glm::vec2(-1, -1), glm::vec2(0, 0)), 45));

		END();
	}
	void directionTestk() {
		START();

		CHECK(approximatelyEqual(directionInDegrees(glm::vec2(1, 1)), 45));
		CHECK(approximatelyEqual(directionInDegrees(glm::vec2(10, 10)), 45));
		CHECK(approximatelyEqual(directionInDegrees(glm::vec2(1, -1)), 315));

		END();
	}
	void mapTestl() {
		START();
		CHECK(approximatelyEqual(map(-3, -4, -2, 10, 11), 10.5));
		CHECK(approximatelyEqual(map(-3, -4, -2, -100, 300), 100));

		END();
	}
	void mapTestm() {
		START();
		float y;
		map(-3, -4, -2, 10, 11, y);
		CHECK(approximatelyEqual(y, 10.5));
		map(-3, -4, -2, -100, 300, y);
		CHECK(approximatelyEqual(y, 100));

		END();
	}
	void approximateVectorEqualityTestq() {
		START();
		CHECK(approximateVectorEquality(glm::vec3(2, 2, 2), glm::vec3(2, 2, 2)) == true);
		CHECK(approximateVectorEquality(glm::vec3(2, 2, 2), glm::vec3(2.00001, 1.99999, 2)) == true);
		CHECK(approximateVectorEquality(glm::vec3(2, 2, 2), glm::vec3(2.00001, 1.9, 2)) == false);
		CHECK(approximateVectorEquality(glm::vec3(2, 2, 2), glm::vec3(1.9, 1.9, 1.9)) == false);
		CHECK(approximateVectorEquality(glm::vec3(-100, 0, 0), glm::vec3(-100.0001, 0, 0)) == true);
		CHECK(approximateVectorEquality(glm::vec3(-100, 0, 0), glm::vec3(-100.1, 0, 0)) == false);
		CHECK(approximateVectorEquality(glm::vec3(-100, 0, 0), glm::vec3(100, 0, 0)) == false);

		END();
	}
	void quadraticTestn() {
		START();

		std::vector<float> roots;

		roots = quadratic(2, -5, -3);
		std::sort(roots.begin(), roots.end());
		CHECK(roots.size() == 2 && approximatelyEqual(roots[0], -0.5) && approximatelyEqual(roots[1], 3));

		roots = quadratic(5, 1, 3);
		CHECK(roots.size() == 0);

		roots = quadratic(1, 0, 0);
		CHECK(roots.size() == 1 && approximatelyEqual(roots[0], 0));

		roots = quadratic(1, 0, -1);
		std::sort(roots.begin(), roots.end());
		CHECK(roots.size() == 2 && approximatelyEqual(roots[0], -1) && approximatelyEqual(roots[1], 1));

		END();
	}
	void areaOfParallelogramTestr() {
		START();

		CHECK(approximatelyEqual(areaOfParallelogram(glm::vec3(0, 0, 1), glm::vec3(1, 0, 0)), 1));
		CHECK(approximatelyEqual(areaOfParallelogram(glm::vec3(0, 0, 1), glm::vec3(2, 0, 0)), 2));
		CHECK(approximatelyEqual(areaOfParallelogram(glm::vec3(1, 1, 0), glm::vec3(1, -1, 0)), std::sqrt(2.0f)*std::sqrt(2.0f)));

		END();
	}
	void areaOfTriangleTests() {
		START();

		glm::vec3 V1(0, 0, 0);
		glm::vec3 V2(1, 1, 1);
		glm::vec3 V3(1, 0, 1);
		CHECK(approximatelyEqual(areaOfTriangle(V1, V2, V3), 0.5f * sqrt(2.0f) * 1));
		CHECK(approximatelyEqual(areaOfTriangle(V2, V3, V1), 0.5f * sqrt(2.0f) * 1));
		CHECK(approximatelyEqual(areaOfTriangle(V3, V1, V2), 0.5f * sqrt(2.0f) * 1));
		glm::vec3 delta(-100, 34, 40);
		V1 += delta;
		V2 += delta;
		V3 += delta;
		CHECK(approximatelyEqual(areaOfTriangle(V1, V2, V3), 0.5f * sqrt(2.0f) * 1));
		CHECK(approximatelyEqual(areaOfTriangle(V2, V3, V1), 0.5f * sqrt(2.0f) * 1));
		CHECK(approximatelyEqual(areaOfTriangle(V3, V1, V2), 0.5f * sqrt(2.0f) * 1));

		END();
	}
	void pointingVectorTestt() {
		START();
		glm::vec3 v1(4, 5, -9);
		glm::vec3 v2(-10, 2, 4);
		CHECK(pointingVector(v1, v2) == glm::normalize(v2 - v1));
		CHECK(pointingVector(v2, v1) == glm::normalize(v1 - v2));
		glm::vec3 v3(2, 2, 4);
		glm::vec3 v4(2, 1, 4);
		CHECK(pointingVector(v3, v4) == glm::normalize(v4 - v3));
		CHECK(pointingVector(v4, v3) == glm::normalize(v3 - v4));

		END();
	}

	void basisTestu() {
		START();
		glm::vec3 x(1, 0, 0);
		glm::vec3 y(0, 1, 0);
		glm::vec3 z(0, 0, 1);
		CHECK(isRightHandedOrthoNormalBasis(x, y, z));
		CHECK(!isRightHandedOrthoNormalBasis(y, x, z));

		glm::vec4 X(1, 0, 0, 0);
		glm::vec4 Y(0, 1, 0, 0);
		glm::vec4 Z(0, 0, 1, 0);
		X = glm::rotateZ(glm::rotateX(X, 45.0f), -120.0f);
		Y = glm::rotateZ(glm::rotateX(Y, 45.0f), -120.0f);
		Z = glm::rotateZ(glm::rotateX(Z, 45.0f), -120.0f);

		x = glm::vec3(X.x, X.y, X.z);
		y = glm::vec3(Y.x, Y.y, Y.z);
		z = glm::vec3(Z.x, Z.y, Z.z);
		CHECK(isRightHandedOrthoNormalBasis(x, y, z));
		CHECK(!isRightHandedOrthoNormalBasis(y, x, z));
		CHECK(!isRightHandedOrthoNormalBasis(1.1f*x, y, z));

		END();
	}

	void darkenTestw() {
		START();
		color C1(0.5f, 0.3f, 1.0f);
		color C2 = darken(C1);
		CHECK(C2 == C1/2.0f);
		END();
	}

	int main(int argc, char* argv[]) {
		normalizeDegreesTesta();
		rad2degTestb();
		deg2radTestc();
		cosBetweenTestd();
		radsBetweenTeste();
		radsBetweenTestf();
		directionTesti();
		directionTestj();
		directionTestk();
		mapTestl();
		mapTestm();
		quadraticTestn();
		areaOfParallelogramTestr();
		areaOfTriangleTests();
		pointingVectorTestt();
		basisTestu();
		darkenTestw();
		return 0;
	}
}