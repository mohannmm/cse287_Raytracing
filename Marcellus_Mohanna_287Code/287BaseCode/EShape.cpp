#include "EShape.h"

/**
 * @fn	EShapeData EShape::createEDisk(const Material &mat, float radius, int slices)
 * @brief	Creates a disk.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	slices	Number of slices.
 * @return	The new disk.
 * @todo Lab 3D Transformations.
 */

EShapeData EShape::createEDisk(const Material &mat, float radius, int slices) {
	EShapeData result;
	return result;
}

/**
 * @fn	EShapeData EShape::createEPyramid(const Material &mat, float width, float height)
 * @brief	Creates a pyramid with origin at (0,0,0) and pointing toward +y.
 * @param	mat   	Material.
 * @param	width 	Width.
 * @param	height	Height.
 * @return	The new pyramid.
 * @todo Lab 3D Transformations.
 */

EShapeData EShape::createEPyramid(const Material &mat, float width, float height) {
	EShapeData verts;
	return verts;
}

/**
 * @fn	EShapeData EShape::createECylinder(const Material &mat, float radius, float height, int slices, int stacks)
 * @brief	Creates cylinder, which is centered on (0,0,0) and aligned with y axis.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @param	stacks	Stacks.
 * @return	The new cylinder.
 * @todo Lab 3D Transformations.
 */

EShapeData EShape::createECylinder(const Material &mat, float radius, float height, int slices, int stacks) {
	EShapeData verts;
	float angle1, angle2;

	for (int i = 0; i < slices; i++) {
		angle1 = (M_2PI / slices) * i;
		angle2 = (M_2PI / slices) * (i + 1);

		float xa = radius * std::cos(angle1);
		float za = radius * std::sin(angle1);

		float xb = radius * std::cos(angle2);
		float zb = radius * std::sin(angle2);

		glm::vec4 top1(xa, height, za, 1);
		glm::vec4 top2(xb, height, zb, 1);

		glm::vec4 a(xa, 0 , za, 1);
		glm::vec4 b(xb, 0, zb, 1);
		glm::vec3 n1 = normalFrom3Points(top1.xyz,  b.xyz, a.xyz);
		glm::vec3 n2 = normalFrom3Points(b.xyz, top1.xyz, top2.xyz);

		verts.push_back(VertexData(top1, n1, mat));
		verts.push_back(VertexData(b, n1, mat));
		verts.push_back(VertexData(a, n1, mat));

		verts.push_back(VertexData(b, n2, mat));
		verts.push_back(VertexData(top1, n2, mat));
		verts.push_back(VertexData(top2, n1, mat));
	}
	return verts;
}

/**
* @fn	EShapeData EShape::createEClosedCylinder(const Material &mat, float radius, float height, int slices, int stacks)
* @brief	Creates Closed cylinder, which is centered on (0,0,0) and aligned with y axis.
* @param	mat   	Material.
* @param	radius	Radius.
* @param	height	Height.
* @param	slices	Slices.
* @param	stacks	Stacks.
* @return	The new cylinder.
* @todo Lab 3D Transformations.
*/

EShapeData EShape::createEClosedCylinder(const Material &mat, float radius, float height, int slices, int stacks) {
	EShapeData verts;
	float angle1, angle2;

	for (int i = 0; i < slices; i++) {
		angle1 = (M_2PI / slices) * i;
		angle2 = (M_2PI / slices) * (i + 1);

		//x and z cords
		float xa = radius * std::cos(angle1);
		float za = radius * std::sin(angle1);
		float xb = radius * std::cos(angle2);
		float zb = radius * std::sin(angle2);

		//Points
		glm::vec4 top1(xa, height, za, 1);
		glm::vec4 top2(xb, height, zb, 1);
		glm::vec4 btm1(xa, 0, za, 1);
		glm::vec4 btm2(xb, 0, zb, 1);
		glm::vec4 topCenter(0, height, 0, 1);
		glm::vec4 btmCenter(0, 0, 0, 1);
		glm::vec4 a(xa, 0, za, 1); 
		glm::vec4 b(xb, 0, zb, 1);

		glm::vec3 n1 = normalFrom3Points(top1.xyz, b.xyz, a.xyz );
		glm::vec3 n2 = normalFrom3Points(b.xyz, top1.xyz, top2.xyz );
		glm::vec3 nTop = normalFrom3Points(topCenter.xyz, top2.xyz, top1.xyz);
		glm::vec3 nBtm = normalFrom3Points(btmCenter.xyz, btm2.xyz, btm1.xyz);

		verts.push_back(VertexData(top1, n1, mat));
		verts.push_back(VertexData(a, n1, mat));
		verts.push_back(VertexData(b, n1, mat));

		verts.push_back(VertexData(b, n2, mat));
		verts.push_back(VertexData(top2, n2, mat));
		verts.push_back(VertexData(top1, n2, mat));

		verts.push_back(VertexData(topCenter, nTop, mat));
		verts.push_back(VertexData(top1, nTop, mat));
		verts.push_back(VertexData(top2, nTop, mat));

		verts.push_back(VertexData(btmCenter, nBtm, mat));
		verts.push_back(VertexData(btm1, nBtm, mat));
		verts.push_back(VertexData(btm2, nBtm, mat));
	}
	return verts;
}

/**
 * @fn	EShapeData EShape::createECone(const Material &mat, float radius, float height, int slices, int stacks)
 * @brief	Creates cone, which is aligned with y axis.
 * @param	mat   	Material.
 * @param	radius	Radius.
 * @param	height	Height.
 * @param	slices	Slices.
 * @param	stacks	Stacks.
 * @return	The new cone.
 * @todo Lab 3D Transformations.
 */

EShapeData EShape::createECone(const Material &mat, float radius, float height, int slices, int stacks) {
	EShapeData verts;
	float angle1, angle2;

	for (int i = 0; i < slices; i++) {
		angle1 = (M_2PI / slices) * i;
		angle2 = (M_2PI / slices) * (i+1);

		float xa = radius * std::cos(angle1);
		float za = radius * std::sin(angle1);
		float xb = radius * std::cos(angle2);
		float zb = radius * std::sin(angle2);

		glm::vec4 top(0, height, 0, 1);
		glm::vec4 a(xa, 0, za, 1);
		glm::vec4 b(xb, 0, zb, 1);
		//glm::vec3 n = normalFrom3Points(top.xyz, a.xyz, b.xyz);
		glm::vec3 n = normalFrom3Points(top.xyz, b.xyz, a.xyz);

		verts.push_back(VertexData(top, n, mat));
		verts.push_back(VertexData(a, n, mat));
		verts.push_back(VertexData(b, n, mat));
	}
	return verts;
}

/**
 * @fn	EShapeData EShape::createECube(const Material &mat, float width, float height, float depth)
 * @brief	Creates cube
 * @param	mat   	Material.
 * @param	width 	Width.
 * @param	height	Height.
 * @param	depth 	Depth.
 * @return	The new cube.
 */

EShapeData EShape::createECube(const Material &mat, float width, float height, float depth) {
	EShapeData verts;
	return verts;
}

/**
 * @fn	EShapeData EShape::createETriangles(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates triangles
 * @param	mat	Material.
 * @param	V  	Vector of objects to process.
 * @return	The new triangles.
 */

EShapeData EShape::createETriangles(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	unsigned int numTris = V.size() / 3;
	for (unsigned int i = 0; i < numTris; i++) {
		int start = 3 * i;
		const glm::vec4 &A = V[start];
		const glm::vec4 &B = V[start + 1];
		const glm::vec4 &C = V[start + 2];
		VertexData::addTriVertsAndComputeNormal(result, A, B, C, mat);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createEPlanes(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates planes, which are defined by 4 corners.
 * @param	mat	Material.
 * @param	V  	Vector of points to process.
 * @return	The new planes.
 */

EShapeData EShape::createEPlanes(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	unsigned int numPlanes = V.size() / 4;
	for (unsigned int i = 0; i < numPlanes; i++) {
		int start = 4 * i;
		const glm::vec4 &A = V[start];
		const glm::vec4 &B = V[start + 1];
		const glm::vec4 &C = V[start + 2];
		const glm::vec4 &D = V[start + 3];
		VertexData::addConvexPolyVertsAndComputeNormals(result, A, B, C, D, mat);
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createELines(const Material &mat, const std::vector<glm::vec4> &V)
 * @brief	Creates lines
 * @param	mat	Material.
 * @param	V  	A vector of point-pairs.
 * @return	The new lines.
 */

EShapeData EShape::createELines(const Material &mat, const std::vector<glm::vec4> &V) {
	EShapeData result;
	for (unsigned int i = 0; i < V.size(); i++) {
		result.push_back(VertexData(V[i], ZEROVEC, mat));
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, float WIDTH, float HEIGHT, int DIV)
 * @brief	Creates checker board pattern.
 * @param	mat1  	Material #1.
 * @param	mat2  	Material #2.
 * @param	WIDTH 	Width of overall plane.
 * @param	HEIGHT	Height of overall plane.
 * @param	DIV   	Number of divisions.
 * @return	The vertices in the checker board.
 */

EShapeData EShape::createECheckerBoard(const Material &mat1, const Material &mat2, float WIDTH, float HEIGHT, int DIV) {
	EShapeData result;

	const float INC = (float)WIDTH / DIV;
	for (int X = 0; X < DIV; X++) {
		bool isMat1 = X % 2 == 0;
		for (float Z = 0; Z < DIV; Z++) {
			glm::vec4 V0(-WIDTH / 2.0f + X*INC, 0.0f, -WIDTH / 2 + Z*INC, 1.0f);
			glm::vec4 V1 = V0 + glm::vec4(0.0f, 0.0f, INC, 0.0f);
			glm::vec4 V2 = V0 + glm::vec4(INC, 0.0f, INC, 0.0f);
			glm::vec4 V3 = V0 + glm::vec4(INC, 0.0f, 0.0f, 0.0f);
			const Material &mat = isMat1 ? mat1 : mat2;

			result.push_back(VertexData(V0, Y_AXIS, mat));
			result.push_back(VertexData(V1, Y_AXIS, mat));
			result.push_back(VertexData(V2, Y_AXIS, mat));

			result.push_back(VertexData(V2, Y_AXIS, mat));
			result.push_back(VertexData(V3, Y_AXIS, mat));
			result.push_back(VertexData(V0, Y_AXIS, mat));
			isMat1 = !isMat1;
		}
	}
	return result;
}

/**
 * @fn	EShapeData EShape::createExtrusion(const Material &mat, const std::vector<glm::vec2> &V)
 * @brief	Creates an extrusion based on a 2D profile.
 * @param	mat	Material.
 * @param	V  	Vector of points defining the 2D profile, based on (x, y) points.
 * @return	The new extrusion.
 * @todo Lab 3D Transformations.
 */

EShapeData EShape::createExtrusion(const Material &mat, const std::vector<glm::vec2> &V) {
	EShapeData verts;
	return verts;
}
