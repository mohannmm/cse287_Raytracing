#pragma once
#include <vector>
#include <map>
#include "Defs.h"
#include "Light.h"
#include "Camera.h"
#include "Light.h"
#include "EShape.h"
#include "IShape.h"

/**
 * @struct	IScene
 * @brief	Represents an scene of implicitly represented objects. Used mostly in ray tracing.
 */

struct IScene {
	AmbientLight *globalAmbientLight;					//!< The one global ambient light
	std::vector<PositionalLightPtr> lights;				//!< All the positional lights in the scene
	std::vector<VisibleIShapePtr> visibleObjects;		//!< All the visible objects in the scene
	RaytracingCamera *camera;							//!< The one camera in the scene
	IScene(RaytracingCamera *theCamera, bool withAxis = false);
	void addObject(const VisibleIShapePtr &obj);
	void addObject(const PositionalLightPtr &light);
	void changeCamera(RaytracingCamera *cam);
	void setGlobalAmbientLight(const color &C);
};

