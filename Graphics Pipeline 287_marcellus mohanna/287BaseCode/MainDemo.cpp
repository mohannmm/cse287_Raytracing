#include <map>
#include <string>
#include "Defs.h"
#include "Utilities.h"

void test1();
void test2();


/*
Marcellus Mohanna
CSE 287 - Zmuda
*/

int main(int argc, char *argv[]) {

	glm::vec2 a(4,3);
	std::cout << a << std::endl;


	glm::vec2 b = glm::normalize(a);
	std::cout << b << std::endl;
}

void test1() {


	std::cout << "Testing all of my methods...\n" << std::endl;
	float a, b, c;

	// Swap //
	a = 25, b = 10;
	std::cout <<"Calling swap...a = 25, b = 10"<< std::endl;
	std::cout << " b should be 25, a should be 10" << std::endl;
	swap(a, b);
	std::cout << " a: "<<a<<" b: "<<b << std::endl;
	std::cout <<""<< std::endl;

	// Approximately Equal //
	a = 10.5, b = 10;
	std::cout << "Calling apprixmately equal...a = "<<a<<", b = "<<b<<", Epsilon = "<<EPSILON << std::endl;
	std::cout << " Should be false" << std::endl;
	std::cout << " Result " << approximatelyEqual(a, b) << std::endl;
	a = 10.0005, b = 10;
	std::cout << " Calling apprixmately equal...a = " << a << ", b = " << b << ", Epsilon = " << EPSILON << std::endl;
	std::cout << " Should be true" << std::endl;
	std::cout << " Result " << approximatelyEqual(a, b) << std::endl;
	std::cout << "" << std::endl;

	// Approximately Zero //
	a = 0.0125;
	std::cout << "Calling apprixmately zero...a = " << a << ", Epsilon = " << EPSILON << std::endl;
	std::cout << " Should be false" << std::endl;
	std::cout << " Result " << approximatelyZero(a) << std::endl;
	a = 0.0005;
	std::cout << " Calling apprixmately zero...a = " << a << ", Epsilon = " << EPSILON << std::endl;
	std::cout << " Should be true" << std::endl;
	std::cout << " Result " << approximatelyZero(a) << std::endl;
	std::cout << "" << std::endl;

	// Normalize Degrees //
	a = -365.5;
	std::cout << " Calling normalize degrees...a = " << a << std::endl;
	std::cout << " Should be 345.5"<< std::endl;
	std::cout << " Result " << normalizeDegrees(a) << std::endl;
	std::cout << "" << std::endl;

	// Normalize Radians //
	a = -3*M_PI;
	std::cout << " Calling normalize radians...a = " << a << std::endl;
	std::cout << " Should be 3.14" << std::endl;
	std::cout << " Result " << normalizeRadians(a) << std::endl;
	std::cout << "" << std::endl;

	// Radians to Degrees //
	a =  M_PI / 3;
	std::cout << " Calling radians to degrees...a = " << a << std::endl;
	std::cout << " Should be 60" << std::endl;
	std::cout << " Result " << rad2deg(a) << std::endl;
	std::cout << "" << std::endl;

	// Degrees to Radians //
	a = 270;
	std::cout << " Calling degrees to radians...a = " << a << std::endl;
	std::cout << " Should be 4.71" << std::endl;
	std::cout << " Result " << deg2rad(a) << std::endl;
	std::cout << "" << std::endl;

	// Min //
	a = -2, b = -2.1, c = 2;
	std::cout <<"Calling min...a = " << a << ", b = " << b << ", c = " << c << std::endl;
	std::cout <<" Should be b = -2.1" << std::endl;
	std::cout <<" Result " << min(a,b,c) << std::endl;
	std::cout << "" << std::endl;

	// Max //
	a = -1, b = 3.1, c = 3.2;
	std::cout << "Calling max...a = " << a << ", b = " << b << ", c = " << c << std::endl;
	std::cout << " Should be c = 3.2" << std::endl;
	std::cout << " Result " << max(a, b, c) << std::endl;
	std::cout << "" << std::endl;

	// Points on Unit Cirlce //
	a = M_PI_4, b = 0, c = 0;
	std::cout << "Calling points on unit circle...a = " << a << ", b = " << b << ", c = " << c << std::endl;
	pointOnUnitCircle(a, b, c);
	std::cout << " Should be b = 0.7, c = 0.7" << std::endl;
	std::cout << " Result b = " << b <<", c = "<< c << std::endl;



	// Extra Tests //
	std::cout << "\n\nExtra exstensive tests..." << std::endl;
	std::cout << normalizeDegrees(75) << std::endl;
	std::cout << normalizeDegrees(361) << std::endl;
	std::cout << normalizeDegrees(725) << std::endl;
	std::cout << normalizeDegrees(-721) << std::endl;
	std::cout << normalizeDegrees(50.125) << std::endl;
	std::cout << normalizeDegrees(370.125) << std::endl;
	std::cout << normalizeDegrees(-15.1275) << std::endl;
	std::cout << normalizeDegrees(719.333) << std::endl;

	std::cout << "\n" << std::endl;
	std::cout << normalizeDegrees(0) << std::endl;
	std::cout << normalizeDegrees(-45) << std::endl;
	std::cout << normalizeDegrees(180) << std::endl;
	std::cout << normalizeDegrees(-180) << std::endl;

	std::cout << "\n" << std::endl;
	std::cout << normalizeRadians(0) << std::endl;
	std::cout << normalizeRadians(M_2PI) << std::endl;
	std::cout << normalizeRadians(M_PI_3) << std::endl;
	std::cout << normalizeRadians(5) << std::endl;

	std::cout << "\n" << std::endl;
	std::cout << min(0,2,5) << std::endl;
	std::cout << min(-5,-5,-4) << std::endl;
	std::cout << max(1,56,56.1) << std::endl;
	std::cout << max(3,3,5) << std::endl;

	std::cout << "\n" << std::endl;
	float x = 0 , y = 0;
	pointOnUnitCircle(0, x, y);
	std::cout << "x: " << x << " y: " << y << std::endl;
	pointOnUnitCircle(M_PI, x, y);
	std::cout << "x: " << x << " y: " << y << std::endl;
	pointOnUnitCircle(M_2PI, x, y);
	std::cout << "x: " << x << " y: " << y << std::endl;
	pointOnUnitCircle(M_PI/2, x, y);
	std::cout << "x: " << x << " y: " << y << std::endl;
	pointOnUnitCircle(M_PI/4, x, y);
	std::cout << "x: " << x << " y: " << y << std::endl;

	

}

void test2() {
	// Mapping //
	std::cout << "Map..." << std::endl;
	std::cout << map(5, 0, 10, 0, 100) << std::endl;
	std::cout << map(2, 0, 5, 10, 11) << std::endl;

	float y = 0;
	map(5, 0, 10, 0, 100, y);
	std::cout << y << std::endl;

	y = 0;
	map(2, 0, 5, 10, 11, y);
	std::cout << "\n" << y << std::endl;

	// Quadratics //
	std::cout << "\nQuadratic..." << std::endl;
	std::cout << quadratic(9, 6, 1)[0] << "\n" << std::endl;
	std::cout << quadratic(-2, 1, 3)[0] << std::endl;
	std::cout << quadratic(-2, 1, 3)[1] << std::endl;

	float roots[2];
	std::cout << "\nRoots: " << quadratic(-2, 1, 3, roots) << std::endl;
	std::cout << roots[0] << std::endl;
	std::cout << roots[1] << std::endl;

	float roots2[2];
	std::cout << "\nRoots: " << quadratic(9, 6, 1, roots2) << std::endl;
	std::cout << roots2[0] << std::endl;
}
