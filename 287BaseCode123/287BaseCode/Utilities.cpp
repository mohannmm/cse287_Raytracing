#include <iostream>
#include <algorithm>
#include <cmath>

#include "defs.h"
#include "Utilities.h"

/**
* @fn	ostream &operator << (std::ostream &os, const glm::vec2 &V)
* @brief	Output stream for vec2.
* @param	os		Output stream.
* @param	V		The vector.
*/

std::ostream &operator << (std::ostream &os, const glm::vec2 &V) {
	os << "[ " << V.x << " " << V.y << " ]";
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const glm::vec3 &V)
* @brief	Output stream for vec3.
* @param	os		Output stream.
* @param	V		The vector.
*/

std::ostream &operator << (std::ostream &os, const glm::vec3 &V) {
	os << "[ " << V.x << " " << V.y << " " << V.z << " ]";
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const glm::vec4 &V)
* @brief	Output stream for vec4.
* @param	os		Output stream.
* @param	V		The vector.
*/

std::ostream &operator << (std::ostream &os, const glm::vec4 &V) {
	os << "[ " << V.x << " " << V.y << " " << V.z << " " << V.w << " ]";
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const glm::mat2 &M)
* @brief	Output stream for mat2.
* @param	os		Output stream.
* @param	M		The matrix.
*/

std::ostream &operator << (std::ostream &os, const glm::mat2 &M) {
	os << "\n";
	for (int row = 0; row < 2; row++) {
		os << "|\t";
		for (int col = 0; col < 2; col++) {
			os << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const glm::mat3 &M)
* @brief	Output stream for mat3.
* @param	os		Output stream.
* @param	M		The matrix.
*/

std::ostream &operator << (std::ostream &os, const glm::mat3 &M) {
	os << "\n";
	for (int row = 0; row < 3; row++) {
		os << "|\t";
		for (int col = 0; col < 3; col++) {
			os << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const glm::mat4 &M)
* @brief	Output stream for mat4.
* @param	os		Output stream.
* @param	M		The matrix.
*/

std::ostream &operator << (std::ostream &os, const glm::mat4 &M) {
	os << "\n";
	for (int row = 0; row < 4; row++) {
		os << "|\t";
		for (int col = 0; col < 4; col++) {
			os << M[col][row] << "\t";
		}
		os << "|\n";
	}
	os << "\n";
	return os;
}

/**
 * @fn	void swap(float &a, float &b)
 * @brief	Swaps that values of two floating point numbers, without
 * 			using std.
 * @param [in,out]	a	First float.
 * @param [in,out]	b	Second float.
 * @todo Lab CPP
 */

void swap(float &a, float &b) {
	float tmp = a;
	a = b;
	b = tmp;
}

/**
 * @fn	bool approximatelyEqual(float a, float b)
 * @brief	Determines if two values are approximately equal.
 * 			That is, their values within EPSILON of each other.
 * @param	a	The first value.
 * @param	b	The second value.
 * @return	true iff (a-b) is in [-EPSILON, EPSILON].
 * @todo Lab CPP
 */

bool approximatelyEqual(float a, float b) {
	return (std::abs(a-b) <= EPSILON);
}

/**
 * @fn	bool approximatelyZero(float a)
 * @brief	Determines if a value is approximately zero.
 * 			That is, the value is within EPSILON of zero.
 * @param	a	The value.
 * @return	true iff a is in [-EPSILON, EPSILON].
 * @todo Lab CPP
 */

bool approximatelyZero(float a) {
	return (std::abs(a) <= EPSILON);
}

/**
 * @fn	float normalizeDegrees(float degrees)
 * @brief	Converts an arbitrary number of degrees to an equivalent
 * 			number of degrees in the range [0, 360).
 * @param	degrees	The degrees.
 * @return	Normalized degrees in the range [0, 360).
 * @test	normalizeDegrees(0) --> 0
 * @test	normalizeDegrees(1) --> 1
 * @test	normalizeDegrees(-1) --> 359
 * @test	normalizeDegrees(-721) --> 359
 * @todo Lab CPP
 */

float normalizeDegrees(float degrees) {
	float piece = (float) std::fmod(degrees, 360);
	return (piece >= 0) ? piece : 360 - std::abs(piece);
}

/**
 * @fn	float normalizeRadians(float rads)
 * @brief	Converts an arbitrary number of radians to an equivalent
 * 			number of radians in the range [0, 2*M_PI).
 * @param	rads	The radians.
 * @return	Normalized radians in the range [0, 2*M_PI).
 * @test	normalizeRadians(0) --> 0
 * @test	normalizeRadians(1) --> 1
 * @test	normalizeRadians(3*M_PI) --> M_PI
 * @test	normalizeRadians(-31*M_PI) --> M_PI
 * @todo Lab CPP
 */

float normalizeRadians(float rads) {
	float piece = std::fmod(rads, M_2PI);
	return (piece >= 0) ? piece : M_2PI - std::abs(piece);
}

/**
 * @fn	float rad2deg(float rads)
 * @brief	Converts radians to degrees, without using GLM.
 * @param	rads	The radians.
 * @return	Degrees.
 * @todo Lab CPP
 */

float rad2deg(float rads) {
	return rads * 180.0f / M_PI;
}

/**
 * @fn	float deg2rad(float degs)
 * @brief	Converts degrees to radians, without using GLM.
 * @param	degs	The degrees.
 * @return	Radians.
 * @todo Lab CPP
 */

float deg2rad(float degs) {
	return degs * M_PI / 180.0f;
}

/**
* @fn	float min(float A, float B, float C)
* @brief	Determines the minimum of three values, using std::min.
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The minimum value.
* @todo Lab CPP
*/

float min(float A, float B, float C) {
	return std::min(std::min(A,B),C);
}

/**
* @fn	float max(float A, float B, float C)
* @brief	Determines the maximum of three values, using std::max.
* @param	A	First value.
* @param	B	Second value
* @param	C	Third value.
* @return	The maximum value.
* @todo Lab CPP
*/

float max(float A, float B, float C) {
	return std::max(std::max(A, B), C);
}

/**
 * @fn	void pointOnUnitCircle(float angleRads, float &x, float &y)
 * @brief	Determines the (x,y) position of a point on the standard
 * 			unit circle.
 * @param 		  	angleRads	The angle in radians.
 * @param [in,out]	x		 	A float to process.
 * @param [in,out]	y		 	A float to process.
 * @todo Lab CPP
 */

void pointOnUnitCircle(float angleRads, float &x, float &y) {
	x = std::cos(normalizeRadians(angleRads));
	y = std::sin(normalizeRadians(angleRads));
}

/**
* @fn	glm::vec2 pointOnCircle(const glm::vec2 &center, float R, float angleRads)
* @brief	Computes the (x,y) value of a point on the circle centered on 'center',
* 			having radius R. The point is determined by sweeping an arc 'angleRads'.
* @param	center   	The center of the circle
* @param	R		 	Radius of circle.
* @param	angleRads	The angle in radians.
* @return	The point on the circle.
* @todo Lab GLM and Graphics
*/

glm::vec2 pointOnCircle(const glm::vec2 &center, float R, float angleRads) {
	
	return glm::vec2(center.x + (R * cos(angleRads)) , center.y + (R * sin(angleRads)));
}

/**
* @fn	float directionInDegrees(float x1, float y1, float x2, float y2)
* @brief	Compute the direction/heading of (x2,y2), relative
* 			to (x1,y1). Result is in range [0, 360).
* @param	x1
* @param	y1
* @param	x2
* @param	y2
* @return	The angle of (x2,y2) relative to (x1,y1).
* @test	directionInDegrees(2, 10, 3, 11) --> 45
* @test	directionInDegrees(3, 11, 2, 10) --> 225
* @test	directionInDegrees(0, 0, 10, 10) --> 45
* @test	directionInDegrees(2, 2, 2, 0) --> 270
* @todo Lab GLM and Graphics
*/

float directionInDegrees(float x1, float y1, float x2, float y2) {
	return rad2deg( std::atan((y2 - y1) / (x2 - x1)) );
	
}

/**
* @fn	float directionInDegrees(const glm::vec2 &pt1, const glm::vec2 &pt2)
* @brief	Compute the direction/heading of 'pt2', relative
* 			to pt1.
* @param	pt1	Reference point.
* @param	pt2	Target point point.
* @return	A float.
* @test	directionInDegrees((2,10), (3,11)) --> 45
* @todo Lab GLM and Graphics
*/

float directionInDegrees(const glm::vec2 &pt1, const glm::vec2 &pt2) {
	return rad2deg( std::atan((pt2.y - pt1.y) / (pt2.x - pt1.x)) );
}

/**
* @fn	float directionInDegrees(const glm::vec2 &targetPt)
* @brief	Compute the direction/heading of 'targetPt', relative
* 			to the origin.
* @param	targetPt	Target point.
* @return	The direction in degrees.
* @test	directionInDegrees((1,0)) --> 0
* @test	directionInDegrees((1,1)) --> 45
* @todo Lab GLM and Graphics
*/

float directionInDegrees(const glm::vec2 &targetPt) {
	return rad2deg( std::atan((targetPt.y) / (targetPt.x)) );
}


/**
* @fn	glm::vec2 doubleIt(const glm::vec2 &V)
* @brief	Computes 2*V
* @param	V	The vector.
* @return	2*V.
* @todo Lab Vector Operations (GLM)
*/

glm::vec2 doubleIt(const glm::vec2 &V) {
	return V * 2.0f;
}

/**
* @fn	glm::vec3 myNormalize(const glm::vec3 &V)
* @brief	Computes the normalization of V, without calling glm::normalize.
* @param	V	The vector.
* @return	Normalized vector V.
* @todo Lab Vector Operations (GLM)
*/

glm::vec3 myNormalize(const glm::vec3 &V) {
	return V / glm::length(V);
}

/**
* @fn	bool isOrthogonal(const glm::vec3 &a, const glm::vec3 &b)
* @brief	Determines if two vectors are orthogonal, or nearly orthogonal.
* @param	a	The first vector.
* @param	b	The second vector.
* @return	True iff the two vector are orthogonal.
* @todo Lab Vector Operations (GLM)
*/

bool isOrthogonal(const glm::vec3 &a, const glm::vec3 &b) {
	return (glm::dot(a,b) == 0); // do product  = 0 means perpendicular vectors
}

/**
 * @fn	float cosBetween(const glm::vec2 &v1, const glm::vec2 &v2)
 * @brief	Cosine between v1 and v2. 
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The cosine between v1 and v2.
 * @todo Lab Vector Operations (GLM)
 */

float cosBetween(const glm::vec2 &v1, const glm::vec2 &v2) {
	return glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2));
}

/**
 * @fn	float cosBetween(const glm::vec3 &v1, const glm::vec3 &v2)
 * @brief	Computes the cosine between v1 and v2.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	A float.
 * @todo Lab Vector Operations (GLM)
 */

float cosBetween(const glm::vec3 &v1, const glm::vec3 &v2) {
	return glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2));
}

/**
 * @fn	float radsBetween(const glm::vec2 &v1, const glm::vec2 &v2)
 * @brief	Computes the radians between two vectors. Uses trig functions.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The number of radians between the two vectors.
 * @todo Lab Vector Operations (GLM)
 */

float radsBetween(const glm::vec2 &v1, const glm::vec2 &v2) {
	float var = glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2));
	var = glm::clamp(var, -1.0f, 1.0f);
	return std::acosf(var);
}

/**
 * @fn	float radsBetween(const glm::vec3 &v1, const glm::vec3 &v2)
 * @brief	Computes the radians between two vectors. Uses trig functions.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	The number of radians between the two vectors.
 * @todo Lab Vector Operations (GLM)
 */

float radsBetween(const glm::vec3 &v1, const glm::vec3 &v2) {
	float var = glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2));
	var = glm::clamp(var, -1.0f, 1.0f);
	return std::acosf(var);
}

/**
* @fn	glm::vec3 project(const glm::vec3 &from, const glm::vec3 &onto)
* @brief	Project the vector 'from' onto the vector 'onto'
* @param	from	Source for the.
* @param	onto	The onto.
* @return	'from' projected onto 'onto'
* @todo Lab Vector Operations (GLM)
*/

glm::vec3 project(const glm::vec3 &from, const glm::vec3 &onto) {
	return (glm::dot(from, onto)/ std::pow(glm::length(onto), 2) ) * onto;
}

/**
* @fn	glm::vec2 rotate90CCW(const glm::vec2 &pt)
* @brief	Rotate a 2D point about the origin, 90 degrees counterclockwise.
* @param	pt	A glm::vec2 to process.
* @return	The point rotated 90 degrees counterclockwise.
* @test	rotate90CCW((-4,-10)) -> (10,-4)
* @test	rotate90CCW((10,-4)) -> (4,10)
* @todo Lab Vector Operations (GLM)
*/

glm::vec2 rotate90CCW(const glm::vec2 &pt) {
	return glm::vec2(-(pt.y), pt.x);
}

/**
 * @fn	float map(float x, float xLow, float xHigh, float yLow, float yHigh)
 * @brief	Linearlly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @test	map(2, 0, 5, 10, 11) --> 10.4
 * @todo Lab Vector Operations (GLM)
 */

float map(float x, float xLow, float xHigh, float yLow, float yHigh) {
	return ( ((x - xLow) / (xHigh - xLow)) * (yHigh - yLow) ) + yLow;
}

/**
 * @fn	void map(float x, float xLow, float xHigh, float yLow, float yHigh, float &y)
 * @brief	Linearlly map a value from one interval to another.
 * @param 		  	x	 	x value.
 * @param 		  	xLow 	The low value of the x range.
 * @param 		  	xHigh	The high value of the x range.
 * @param 		  	yLow 	The low value of the y range.
 * @param 		  	yHigh	The high value of the y range.
 * @param [in,out]	y	 	The mapped value in the y range.
 * @test	map(2, 0, 5, 10, 11, y) --> y = 10.4
 * @todo Lab Vector Operations (GLM)
 */

void map(float x, float xLow, float xHigh, float yLow, float yHigh, float &y) {
	y = ( ((x - xLow) / (xHigh - xLow)) * (yHigh - yLow) ) + yLow;
}

/**
 * @fn	std::vector<float> quaftic(float A, float B, float C)
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the array 'roots'0.
 * 			The roots are sortecd in ascending order.
 * @param	A	A.
 * @param	B	B.
 * @param	C	C.
 * @return	Vector containing the real roots.
 * @test	quadratic(1,4,3) --> (-3,-1)
 * @todo Lab Vector Operations (GLM)
 */

std::vector<float> quadratic(float A, float B, float C) {
	float root1, root2;

	if (A != 0 && ((B*B)-(4*A*C)) >= 0) {
		 root1 = (-B + (std::sqrt((B*B) - (4 * A * C)))) / (2 * A);
		 root2 = (-B - (std::sqrt((B*B) - (4 * A * C)))) / (2 * A);

		 if (root1 == root2) {
			 std::vector<float> result(1);
			 result[0] = root1;
			 return result;
		 }
		 std::vector<float> result(2);
		 if (root1 < root2) {
			 result[0] = root1;
			 result[1] = root2;
		 }
		 else {
			 result[0] = root2;
			 result[1] = root1;
		 }
		 return result;
	}
	return std::vector<float>();
}

/**
 * @fn	int quadratic(float A, float B, float C, float roots[2])
 * @brief	Solves the quadratic equation, given A, B, and C.
 * 			0, 1, or 2 roots are inserted into the array 'roots'0.
 * 			The roots are sortecd in ascending order.
 * @param	A	 	A.
 * @param	B	 	B.
 * @param	C	 	C.
 * @param	roots	The real roots.
 * @return	The number of real roots put into the array 'roots'
 * @todo Lab Vector Operations (GLM)
*/

int quadratic(float A, float B, float C, float roots[2]) {
	float root1, root2;

	if (A != 0 && ((B*B) - (4 * A*C)) >= 0) {
		root1 = (-B + ( std::sqrt( (B*B) - (4 * A*C)) ) ) / (2 * A);
		root2 = (-B - ( std::sqrt( (B*B) - (4 * A*C)) ) ) / (2 * A);

		roots[0] = std::min(root1, root2);

		if (approximatelyEqual(root1, root2) ) {
			return 1;
		}

		roots[1] = std::max(root1, root2);
		return 2;
	}
	return 0;
}

/**
 * @fn	float areaOfParallelogram(const glm::vec3 &v1, const glm::vec3 &v2)
 * @brief	Computes the area of parallelogram, given two vectors eminating
 * 			from the same corner of the parallelogram.
 * @param	v1	The first vector.
 * @param	v2	The second vector.
 * @return	Area of parallelogram.
 * @todo Lab Vector Operations (GLM)
 */

float areaOfParallelogram(const glm::vec3 &v1, const glm::vec3 &v2) {
	return glm::length(glm::cross(v1,v2));
}

/**
 * @fn	float areaOfTriangle(const glm::vec3 &pt1, const glm::vec3 &pt2, const glm::vec3 &pt3)
 * @brief	Computes the area of triangle.
 * @param	pt1	The first point.
 * @param	pt2	The second point.
 * @param	pt3	The third point.
 * @return	Area of triangle.
 * @todo Lab Vector Operations (GLM)
 */

float areaOfTriangle(const glm::vec3 &pt1, const glm::vec3 &pt2, const glm::vec3 &pt3) {
	return glm::length(glm::cross(pt3-pt1, pt2-pt1)) / 2;
}

/**
* @fn	bool isOrthoNormalBasis(const glm::vec3 &u, const glm::vec3 &v, const glm::vec3 &w)
* @brief	Determines if three vectors form an orthonormal basis.
* @param	u	The u vector.
* @param	v	The v vector.
* @param	w	The w vector.
* @return	True if ortho normal basis, false if not.
* @todo Lab Matrix Operations (GLM)
*/

bool isOrthoNormalBasis(const glm::vec3 &u, const glm::vec3 &v, const glm::vec3 &w) {
	// if orthogonal/linearly independent (dot product == 0) and orthonormal (of length 1) 
	if (isOrthogonal(u, v) && isOrthogonal(v, w) && isOrthogonal(w, u)) {
		if (glm::length(u) == 1 && glm::length(v) == 1 && glm::length(w) == 1) {
			return true;
		}
	}
	return false;
}

/**
 * @fn	bool isRightHandedOrthoNormalBasis(const glm::vec3 &u, const glm::vec3 &v, const glm::vec3 &w)
 * @brief	Determines if three vectors form a right-handed orthonormal basis.
 * @param	u	The u vector.
 * @param	v	The v vector.
 * @param	w	The w vector.
 * @todo Lab Matrix Operations (GLM)
 * @return	true iff right handed ortho normal basis.
 */

bool isRightHandedOrthoNormalBasis(const glm::vec3 &u, const glm::vec3 &v, const glm::vec3 &w) {
	// if negative, then left handed
	if (isOrthoNormalBasis(u, v, w)) {
		if (glm::cross(u, v) == w) {
			return true;
		}
	}
	return false;
}

/**
* @fn	glm::vec3 pointingVector(const glm::vec3 &pt1, const glm::vec3 &pt2)
* @brief	Computes unit-length pointing vector.
* @param	pt1	The first point.
* @param	pt2	The second point.
* @return	Unit length vector that points from pt1 to pt2.
* @todo Lab Matrix Operations (GLM)
*/

glm::vec3 pointingVector(const glm::vec3 &pt1, const glm::vec3 &pt2) {
	return glm::normalize(pt2 - pt1);
}

/**
* @fn	glm::vec3 normalFrom3Points(const glm::vec3 &pt0, const glm::vec3 &pt1, const glm::vec3 &pt2)
* @brief	Computes a normal vector from 3 points, specified in counterclockwise order.
* @param	pt0	The first point.
* @param	pt1	The second point.
* @param	pt2	The third point.
* @return	Normal vector.
* @todo Lab Matrix Operations (GLM)
*/

glm::vec3 normalFrom3Points(const glm::vec3 &pt0, const glm::vec3 &pt1, const glm::vec3 &pt2) {
	return glm::normalize( glm::cross((pt1 - pt0), (pt2 - pt0)) );
}

/**
* @fn	glm::vec3 normalFrom3Points(const std::vector<glm::vec3> pts)
* @brief	Computes a normal vector from 3 points, specified in counterclockwise order.
* @param	pts	The points.
* @return	The normal vector.
* @todo Lab Matrix Operations (GLM)
*/

glm::vec3 normalFrom3Points(const std::vector<glm::vec3> pts) {
	return glm::normalize( glm::cross(pts[1] - pts[0], pts[2] - pts[0]) );
}

/**
* @fn	glm::vec3 getRow(const glm::mat3 &mat, int row)
* @brief	Retrieves a particular row out of a matrix.
* @param	mat	The matrix.
* @param	row	The row.
* @return	The extracted row.
* @todo Lab Matrix Operations (GLM)
*/

glm::vec3 getRow(const glm::mat3 &mat, int row) {
	return glm::vec3(mat[0][row], mat[1][row], mat[2][row]);
}

/**
 * @fn	glm::vec3 getCol(const glm::mat3 &mat, int col)
 * @brief	Retrieves a particular column out of a matrix.
 * @param	mat	The matrix.
 * @param	col	The column.
 * @return	The extracted column.
 * @todo Lab Matrix Operations (GLM)
 */

glm::vec3 getCol(const glm::mat3 &mat, int col) {
	return glm::vec3(mat[col][0], mat[col][1], mat[col][2]);
}

/**
* @fn	bool isInvertible(const glm::mat2 &mat)
* @brief	Determines if mat is invertible
* @param	mat	The matrix.
* @return	true if invertible, false if not.
* @todo Lab Matrix Operations (GLM)
*/

bool isInvertible(const glm::mat2 &mat) {
	return glm::determinant(mat) != 0;
}

/**
 * @fn	bool isInvertible(const glm::mat3 &mat)
 * @brief	Determines if mat is invertible
 * @param	mat	The matrix.
 * @return	true if invertible, false if not.
 * @todo Lab Matrix Operations (GLM)
 */

bool isInvertible(const glm::mat3 &mat) {
	return glm::determinant(mat) != 0;
}

/**
 * @fn	glm::vec3 solveLinearSystem(const glm::mat3 &M, const glm::vec3 &y)
 * @brief	Solves a linear system
 * @param	M	The matrix.
 * @param	y	The vector.
 * @return	x, such that M*x = y. Returns (0,0,0) if no solution exists (i.e., M is singular).
 * @todo Lab Matrix Operations (GLM)
 */

glm::vec3 solveLinearSystem(const glm::mat3 &M, const glm::vec3 &y) {
	if (!isInvertible(M)) {
		return  glm::vec3(0, 0, 0);
	}
	return glm::inverse(M) * y;
}

/**
 * @fn	glm::mat3 addMatrices(const std::vector<glm::mat3> &M)
 * @brief	Adds the several matrices together.
 * @param	M	Vector of matrices.
 * @return	M[0]+M[1]+...+M[n-1]
 * @todo Lab Matrix Operations (GLM)
 */

glm::mat3 addMatrices(const std::vector<glm::mat3> &M) {
	glm::mat3 result(0, 0, 0, 0, 0, 0, 0, 0, 0);

	for (int i = 0; i < (int) M.size(); i++) {
		result = result + M[i];
	}
	return result;
}

/**
 * @fn	glm::mat3 multiplyMatrices(const std::vector<glm::mat3> &M)
 * @brief	Multiply many matrices together.
 * @param	M	The vector of matrices.
 * @return	Returns M[0]*M[1]*...M[n-1].
 * @todo Lab Matrix Operations (GLM)
 */

glm::mat3 multiplyMatrices(const std::vector<glm::mat3> &M) {
	if (M.size() == 0) return glm::mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);

	glm::mat3 result;

	for (int i = 0; i < (int) M.size(); i++) {
		result = result * M[i];
	}
	return result;
}

/**
 * @fn	glm::vec3 multiplyMatrixAndVertex(const glm::mat3 &M, const glm::vec3 &x)
 * @brief	Multiply matrix and vertex
 * @param	M	A matrix.
 * @param	x	A vector.
 * @return	Returns M*x.
 * @todo Lab Matrix Operations (GLM)
 */

glm::vec3 multiplyMatrixAndVertex(const glm::mat3 &M, const glm::vec3 &x) {
	return M*x;
}

/**
 * @fn	glm::vec3 multiplyMatricesAndVertex(const std::vector<glm::mat3> &M, const glm::vec3 &x)
 * @brief	Multiply matrices and vertex
 * @param	M	A vector of matrices to process.
 * @param	x	The vertex to process.
 * @return	Returns the result of M[0]*M[1]*...M[n-1]*x
 * @todo Lab Matrix Operations (GLM)
 */

glm::vec3 multiplyMatricesAndVertex(const std::vector<glm::mat3> &M, const glm::vec3 &x) {
	
	return multiplyMatrixAndVertex(multiplyMatrices(M), x);
}

/**
 * @fn	std::vector<glm::vec3> multiplyMatrixAndVertices(const glm::mat3 &M, const std::vector<glm::vec3> &verts)
 * @brief	Returns the vector containing: <M*x[0], M*x[1], ... M*x[n-1]>
 * @param	M	 	A glm::mat3 to process.
 * @param	verts	The vertices.
 * @return	Returns the vector: <M*x[0], M*x[1], ... M*x[n-1]>
 * @todo Lab Matrix Operations (GLM)
 */

std::vector<glm::vec3> multiplyMatrixAndVertices(const glm::mat3 &M, const std::vector<glm::vec3> &verts) {
	std::vector<glm::vec3> result;
	for (int i = 0; i < (int) verts.size(); i++) {
		result.push_back( multiplyMatrixAndVertex(M, verts[i]) );
	}
	return result;
}

/**
 * @fn	std::vector<glm::vec3> multiplyMatricesAndVertices(const std::vector<glm::mat3> &M, const std::vector<glm::vec3> &verts)
 * @brief	Multiply matrices and vertices
 * @param	M	 	Vector of matrices.
 * @param	verts	Vector of vertices.
 * @return	Returns: <BIGMAT*x[0], BIGMAT*x[1], ... BIGMAT*x[n-1]>, where BIGMAT = M[0]*M[1]*...M[n-1]
 * @todo Lab Matrix Operations (GLM)
 */

std::vector<glm::vec3> multiplyMatricesAndVertices(const std::vector<glm::mat3> &M, const std::vector<glm::vec3> &verts) {
	std::vector<glm::vec3> result;
	glm::mat3 bigMat = multiplyMatrices(M);

	for (int i = 0; i < (int) verts.size(); i++) {
		result.push_back( multiplyMatrixAndVertex(bigMat, verts[i]) );
	}
	return result;
}

/**
 * @fn	glm::mat2 myinverse(const glm::mat2 &M)
 * @brief	Computes the inverse of a matrix. Assumes M has an inverse.
 * @param	M	The matrix to process.
 * @return	The inverse of the matrix M.
 * @todo Lab Matrix Operations (GLM)
 */

glm::mat2 myinverse(const glm::mat2 &M) {
	float det = 1.0f / (M[0][0] * M[1][1] - M[0][1] * M[1][0]);
	float a = M[1][1] * det;
	float b = -1 * M[0][1] * det;
	float c = -1 * M[1][0] * det;
	float d = M[0][0] * det;

	return glm::mat2x2(a,b,c,d);
}

/**
* @fn	glm::mat3 T(float dx, float dy)
* @brief	Creates the 3x3 translation matrix for 2D systems.
* @param	dx	x translation factor.
* @param	dy	y translation factor.
* @return	The scaling matrix.
* @todo Lab 2D Transformations (GLM)
*/

glm::mat3 T(float dx, float dy) {
	return glm::mat3();
}

/**
 * @fn	glm::mat3 S(float sx, float sy)
 * @brief	Creates the 3x3 scaling matrix for 2D systems.
 * @param	sx	x scale factor.
 * @param	sy	y scale factor.
 * @return	The scaling matrix.
 * @todo Lab 2D Transformations (GLM)
 */

glm::mat3 S(float sx, float sy) {
	return glm::mat3();
}

/**
 * @fn	glm::mat3 R(float deg)
 * @brief	Returns 3x3 rotation matrix for 2D rotations.
 * @param	deg	Degrees to rotate.
 * @return	The rotation matrix.
 * @todo Lab 2D Transformations (GLM)
 */

glm::mat3 R(float deg) {
	return glm::mat3();
}

/**
 * @fn	glm::mat3 horzShear(float a)
 * @brief	Horizontal shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 * @todo Lab 2D Transformations (GLM)
 */

glm::mat3 horzShear(float a) {
	return glm::mat3();
}

/**
 * @fn	glm::mat3 vertShear(float a)
 * @brief	Verticaal shear.
 * @param	a	Shearing parameter.
 * @return	The 3x3 shearing matrix.
 * @todo Lab 2D Transformations (GLM)
 */

glm::mat3 vertShear(float a) {
	return glm::mat3();
}


/**
* @fn	glm::mat4 T(float dx, float dy, float dz)
* @brief	Creates the 4x4 translation matrix for 3D systems.
* @param	dx	The x translation factor.
* @param	dy	The y translation factor.
* @param	dz	The z translation factor.
* @return	The 4x4 translation matrix for 3D systems.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 T(float dx, float dy, float dz) {
	return glm::mat4();
}

/**
* @fn	glm::mat4 S(float sx, float sy, float sz)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	sx	The x scaling factor.
* @param	sy	The y scaling factor.
* @param	sz	The z scaling factor.
* @return	The 4x4 scaling matrix for 3D systems.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 S(float sx, float sy, float sz) {
	return glm::mat4();
}

/**
* @fn	glm::mat4 S(float scale)
* @brief	Creates the 4x4 scaling matrix for 3D systems.
* @param	scale	The scale.
* @return	The 4x4 [uniform] scaling matrix for 3D systems.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 S(float scale) {
	return glm::mat4();
}

/**
* @fn	glm::mat3 Rx(float rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +x axis.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 Rx(float rads) {
	return glm::mat4();
}

/**
* @fn	glm::mat3 Ry(float rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +y axis.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 Ry(float rads) {
	return glm::mat4();
}

/**
* @fn	glm::mat3 Rz(float rads)
* @brief	Creates the 4x4 rotation matrix for 3D systems.
* @param	rads	Rotation amount, in radians.
* @return	The 4x4 matrix for rotation about the +z axis.
* @todo Lab 3D Transformations (GLM)
*/

glm::mat4 Rz(float rads) {
	return glm::mat4();
}


/**
* @fn	void computeXYZFromAzimuthAndElevation(float R, float az, float el, float &x, float &y, float &z)
* @brief	Computes (x,y,z), given a specific azimuth/elevation angles.
* @param 		  	R 	The radius of the sphere.
* @param 		  	az	Azimuth
* @param 		  	el	Elevation.
* @param [in,out]	x 	A float to process.
* @param [in,out]	y 	A float to process.
* @param [in,out]	z 	A float to process.
*/

void computeXYZFromAzimuthAndElevation(float R,
	float az, float el,
	float &x, float &y, float &z) {
		z = R*std::cos(el)*std::cos(az);
		x = R*std::cos(el)*std::sin(az);
		y = R*std::sin(el);
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(float x, float y, float z, float &R, float &az, float &el)
* @brief	Calculates the azimuth and elevation from xyz
* @param 		  	x 	The x coordinate.
* @param 		  	y 	The y coordinate.
* @param 		  	z 	The z coordinate.
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(float x, float y, float z,
	float &R, float &az, float &el) {
		R = glm::length(glm::vec3(x, y, z));
		az = std::atan2(x, z);
		el = std::atan2(y, glm::length(glm::vec2(x, z)));
}

/**
* @fn	void computeAzimuthAndElevationFromXYZ(const glm::vec3 &pt, float &R, float &az, float &el)
* @brief	Compute the azimuth/elevation (relative to the origin) of the point (x,y,z)
* @param 		  	pt	The point - (x,y,z).
* @param [in,out]	R 	The radius of the sphere.
* @param [in,out]	az	Azimuth.
* @param [in,out]	el	Elevation.
*/

void computeAzimuthAndElevationFromXYZ(const glm::vec3 &pt,
	float &R, float &az, float &el) {
		computeAzimuthAndElevationFromXYZ(pt.x, pt.y, pt.z, R, az, el);
}

/**
* @fn	bool inRangeInclusive(float val, float lo, float hi)
* @brief	Determines if value is in a range inclusive
* @param	val	The value.
* @param	lo 	The low end of the range.
* @param	hi 	The high end of the range.
* @return	True iff val in [lo, hi].
*/

bool inRangeInclusive(float val, float lo, float hi) {
	return val >= lo && val <= hi;
}

/**
* @fn	bool inRangeExclusive(float val, float lo, float hi)
* @brief	Determines if value is in a range exclusive
* @param	val	The value.
* @param	lo 	The low end of the range.
* @param	hi 	The high end of the range.
* @return	true iff val in (lo, hi).
*/

bool inRangeExclusive(float val, float lo, float hi) {
	return val > lo && val < hi;
}

/**
* @fn	bool inRectangle(float x, float y, float left, float bottom, float right, float top)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	x	  	The x coordinate.
* @param	y	  	The y coordinate.
* @param	left  	The left edge of rectangle.
* @param	bottom	The bottom edge of rectangle.
* @param	right 	The right edge of rectangle.
* @param	top   	The top edge of rectangle.
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(float x, float y, float left, float bottom, float right, float top) {
	return inRangeInclusive(x, left, right) &&
		inRangeInclusive(y, bottom, top);
}

/**
* @fn	bool inRectangle(const glm::vec2 &pt, const glm::vec2 &lowerLeft, const glm::vec2 &upperRight)
* @brief	Determines if (x,y) is inside (or on) a rectangle.
* @param	pt		  	The point - (x,y)
* @param	lowerLeft 	The lower left corner of the rectangle - (left, bottom).
* @param	upperRight	The upper right corner of the rectangle - (right, top).
* @return	true iff (x,y) is in/on the rectangle.
*/

bool inRectangle(const glm::vec2 &pt, const glm::vec2 &lowerLeft, const glm::vec2 &upperRight) {
	return inRangeInclusive(pt.x, lowerLeft.x, upperRight.x) &&
		inRangeInclusive(pt.y, lowerLeft.y, upperRight.y);
}

/**
* @fn	bool approximateVectorEquality(const glm::vec3 &v1, const glm::vec3 &v2)
* @brief	Determines if two vectors are equal, or nearly equal. Near equality
* 			is when the radians between the two vectors is less than EPSILON and
* 			the difference between the lengths is less than EPSILON.
* @param	v1	The first vector.
* @param	v2	The second vector.
* @return	true iff v1 == v2.
*/

bool approximateVectorEquality(const glm::vec3 &v1, const glm::vec3 &v2) {
	return radsBetween(v1, v2) < EPSILON && approximatelyEqual(glm::length(v1), glm::length(v2));
}


/**
* @fn	std::string extractBaseFilename(const std::string &str)
* @brief	Extracts the base filename described by str
* @param	str	The string.
* @return	The extracted base filename.
* @test	extractBaseFileName("/usr/etc/hosts.txt") --> "hosts.txt"
*/

std::string extractBaseFilename(const std::string &str) {
	unsigned int pos = str.rfind('\\');
	return str.substr(pos + 1);
}