#include "RayTracer.h"
#include "IShape.h"

/**
 * @fn	RayTracer::RayTracer(const color &defa)
 * @brief	Constructs a raytracers.
 * @param	defa	The clear color.
 */

RayTracer::RayTracer(const color &defa)
	: defaultColor(defa) {
}


/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 * @todo Lab
 */

void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth,
	const IScene &theScene) const {

	const RaytracingCamera &camera = *theScene.camera;
	const std::vector<VisibleIShapePtr> &objs = theScene.visibleObjects;
	const std::vector<PositionalLightPtr> &lights = theScene.lights;

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {

			Ray ray = camera.getRay((float)x, (float)y);
			color colorForPixel = traceIndividualRay(ray, theScene, depth);
			frameBuffer.setColor(x, y, colorForPixel);
		}
	}

	frameBuffer.showColorBuffer();
}


/**
* @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
* @brief	Raytrace scene
* @param [in,out]	frameBuffer	Framebuffer.
* @param 		  	depth	   	The current depth of recursion.
* @param 		  	theScene   	The scene.
* @todo Lab
*/

void RayTracer::raytraceSceneAntiAliasing(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const {

	const RaytracingCamera &camera = *theScene.camera;
	const std::vector<VisibleIShapePtr> &objs = theScene.visibleObjects;
	const std::vector<PositionalLightPtr> &lights = theScene.lights;

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
			float pixelOffset = 1.0f / 3.0f;
			color colorForPixel(0.0f, 0.0f, 0.0f);

			for (float i = -pixelOffset; i <= pixelOffset; i += pixelOffset) { //add each subpixel
				for (float j = -pixelOffset; j <= pixelOffset; j += pixelOffset) {
					Ray ray = camera.getRay((float)x + i, (float)y + j);
					colorForPixel += traceIndividualRay(ray, theScene, depth);
				}
			}
			colorForPixel = colorForPixel / 9.0f; //get average color
			frameBuffer.setColor(x, y, colorForPixel);
		}
	}

	frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 * @todo Lab
 */

color RayTracer::colorCalculations(const HitRecord hit, const Ray &ray, const IScene &theScene, int recursionLevel) const {
	color result = defaultColor;
	color lightedColor;
	if (hit.t < FLT_MAX) {
		result = color(0.0f, 0.0f, 0.0f);

		bool shadow = false, spotShadow = false;;
		float acneOffset = EPSILON;

		if (recursionLevel > 1) {
			Ray reflectedRay(hit.interceptPoint + acneOffset, glm::normalize(glm::reflect(ray.direction, hit.surfaceNormal))); // reflections
			color temp = traceIndividualRay(reflectedRay, theScene, recursionLevel - 1);
			if (temp != defaultColor) //Avoids showing the default color if reflected ray never hits
				lightedColor += temp;
		}

		Ray shadowFeeler(hit.interceptPoint + acneOffset, glm::normalize(theScene.lights[0]->lightPosition - hit.interceptPoint));
		HitRecord shadowHit = VisibleIShape::findIntersection(shadowFeeler, theScene.visibleObjects);

		Ray spotShadowFeeler(hit.interceptPoint + acneOffset, glm::normalize(theScene.lights[1]->lightPosition - hit.interceptPoint));
		HitRecord spotShadowHit = VisibleIShape::findIntersection(shadowFeeler, theScene.visibleObjects);


		if (shadowHit.t < FLT_MAX || shadowHit.t < acneOffset) {
			shadow = true;
		}
		if (spotShadowHit.t < FLT_MAX || shadowHit.t < acneOffset) {
			spotShadow = true;
		}

		glm::vec3 v = glm::normalize(theScene.camera->cameraFrame.origin - hit.interceptPoint); //calculate viewing dir
	
			lightedColor += theScene.lights[0]->illuminate(hit, v, theScene.camera->cameraFrame, shadow);
			lightedColor += theScene.lights[1]->illuminate(hit, v, theScene.camera->cameraFrame, spotShadow);

	}

		if (hit.texture != nullptr) {
			float u = glm::clamp(hit.u, 0.0f, 1.0f);
			float v = glm::clamp(hit.v, 0.0f, 1.0f);
			result = (0.50f * hit.texture->getPixel(u, v)) + (0.50f * lightedColor);

		}
		else {
			result = lightedColor;
	}

	return result;
}

color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const {
	HitRecord opaqueHit = VisibleIShape::findIntersection(ray, theScene.visibleObjects);
	HitRecord transHit = VisibleIShape::findIntersection(ray, theScene.transparentObjects);
	color opaque = colorCalculations(opaqueHit, ray, theScene, recursionLevel);
	color result = defaultColor;
	float d1 = glm::distance(opaqueHit.interceptPoint, ray.origin);
	float d2 = glm::distance(transHit.interceptPoint, ray.origin);

	if (opaqueHit.t < FLT_MAX && transHit.t == FLT_MAX || (opaqueHit.t < FLT_MAX && transHit.t < FLT_MAX && d1 < d2) ) { //transparency
		result = opaque;
	}
	else if (opaqueHit.t == FLT_MAX && transHit.t < FLT_MAX) {
		result = glm::clamp((transHit.material.alpha * transHit.material.ambient) + (1.0f - defaultColor), 0.0f, 1.0f);
		//std::cout << transHit.material.alpha << ", " << transHit.material.ambient << std::endl;
		
	}
	else if (transHit.t < FLT_MAX && opaqueHit.t < FLT_MAX && d2 < d1) {
		result = glm::clamp((transHit.material.alpha * transHit.material.ambient) + (1.0f - transHit.material.alpha) * opaque, 0.0f, 1.0f);
		//std::cout << transHit.material.alpha << ", " << transHit.material.ambient << std::endl;
	}

	return result;
}
