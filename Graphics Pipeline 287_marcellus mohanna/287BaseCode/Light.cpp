#include "Light.h"

/**
 * @fn	color ambientColor(const color &mat, const color &light)
 * @brief	Computes the ambient color produced by a single light at a single point.
 * @param	mat  	Ambient material property.
 * @param	light	Light's ambient color.
 * @return	Ambient color.
 * @todo Lab
 */

color ambientColor(const color &mat, const color &light) {
	return glm::clamp(mat * light, 0.0f, 1.0f);
}

/**
 * @fn	color diffuseColor(const color &mat, const color &light, const glm::vec3 &l, const glm::vec3 &n)
 * @brief	Computes diffuse color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	light	 	The light.
 * @param	l		 	Light vector.
 * @param	n		 	Normal vector.
 * @return	Diffuse color.
 * @todo Lab
 */

color diffuseColor(const color &mat, const color &light,
					const glm::vec3 &l, const glm::vec3 &n) {
	return glm::clamp (mat * light * glm::dot(l,n), 0.0f, 1.0f);
}

/**
 * @fn	color specularColor(const color &mat, const color &light, float shininess, const glm::vec3 &r, const glm::vec3 &v)
 * @brief	Computes specular color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	light	 	Light.
 * @param	shininess	Material shininess.
 * @param	r		 	Reflection vector.
 * @param	v		 	Viewing vector.
 * @return	Specular color.
 * @todo Lab
 */

color specularColor(const color &mat, const color &light,
					float shininess,
					const glm::vec3 &r, const glm::vec3 &v) {

	float dp = glm::clamp(glm::dot(r, v), 0.0f, 1.0f);
	return glm::clamp(mat * light * std::pow(dp, shininess), 0.0f, 1.0f);
}

/**
 * @fn	color totalColor(const Material &mat, const LightColor &lightColor, const glm::vec3 &viewingDir, const glm::vec3 &normal, const glm::vec3 &lightPos, const glm::vec3 &intersectionPt, bool attenuationOn, const LightAttenuationParameters &ATparams)
 * @brief	Color produced by a single light at a single point.
 * @param	mat			  	Material.
 * @param	lightColor	  	The light's color.
 * @param	viewingDir	  	Viewing direction.
 * @param	normal		  	Normal vector.
 * @param	lightPos	  	Light position.
 * @param	intersectionPt	(x,y,z) of intersection point.
 * @param	attenuationOn 	true if attenuation is on.
 * @param	ATparams	  	Attenuation parameters.
 * @return	Color produced by a single light at a single point.
 * @todo Lab
 */
 
color totalColor(const Material &mat, const LightColor &lightColor,
				const glm::vec3 &viewingDir, const glm::vec3 &normal,
				const glm::vec3 &lightPos, const glm::vec3 &intersectionPt,
				bool attenuationOn, 
				const LightAttenuationParameters &ATparams) {

	glm::vec3 l = glm::normalize(lightPos - intersectionPt);
	glm::vec3 r = 2.0f * glm::dot(l, normal) * normal - l;

	color amb = ambientColor(mat.ambient, lightColor.ambient);
	color diff = diffuseColor(mat.diffuse, lightColor.diffuse, l, normal);
	color spec = specularColor(mat.specular, lightColor.specular, mat.shininess, r, viewingDir); 

	if (attenuationOn) {
			float c = ATparams.constant;
			float l = ATparams.linear;
			float q = ATparams.quadratic;
			float d = glm::distance(lightPos, intersectionPt);
			float atten = 1.0f / (c + l*d + q*d*d);
			return glm::clamp( atten * (amb + diff + spec), 0.0f, 1.0f);
	} else
	return glm::clamp(amb + diff + spec, 0.0f, 1.0f);
}

/**
 * @fn	color AmbientLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir, const Frame &eyeFrame, bool inShadow) const
 * @param	hit					The surface properties of the intercept point.
 * @param	viewingDir			Viewing direction.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 * @todo Lab
 */

color AmbientLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir,
								const Frame &eyeFrame, bool inShadow) const {
	
	
	if (!isOn) return black;
	return hit.material.ambient * ambientColor;
}

/**
 * @fn	color AmbientLight::illuminate(const Material &material, const glm::vec3 &normal, const glm::vec3 &interceptWorldCoords, const glm::vec3 &eyeWorldCoord, const glm::mat4 &viewingMatrix) const
 * @brief	Computes the color this light produces in pipeline applications.
 * @param	material				Material properties.
 * @param	normal					Surface normal vector.
 * @param	interceptWorldCoords	Intercept point in world coordinates.
 * @param	eyeWorldCoord			Eye world coordinate.
 * @param	viewingMatrix			Viewing matrix.
 * @return	The color produced at the intercept point, given this light.
 */

color AmbientLight::illuminate(const Material &material,
						const glm::vec3 &normal,
						const glm::vec3 &interceptWorldCoords,
						const glm::vec3 &eyeWorldCoord,
						const glm::mat4 &viewingMatrix) const {
	if (!isOn) return black;
	return ambientColor * material.ambient;
}

/**
 * @fn	color PositionalLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir, const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	hit					The surface properties of the intercept point.
 * @param	viewingDir			Viewing direction.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 * @todo Lab Lighting Calculations (GLM)
 */

color PositionalLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir,
									const Frame &eyeFrame, bool inShadow) const {
	color result;
	if (inShadow) {
		result = hit.material.ambient * this->lightColorComponents.ambient;
		//result = yellow; //  Test Shadows here  //
	}
	else {
		result = totalColor(hit.material, this->lightColorComponents, viewingDir, hit.surfaceNormal, this->lightPosition, hit.interceptPoint, this->attenuationIsTurnedOn, this->attenuationParams);
		
	}


	return result;
}

/**
 * @fn	color PositionalLight::illuminate(const Material &material, const glm::vec3 &normal, const glm::vec3 &interceptWorldCoords, const glm::vec3 &eyeWorldCoord, const glm::mat4 &viewingMatrix) const
 * @brief	Computes the color this light produces in pipeline applications.
 * @param	material				Material properties.
 * @param	normal					Surface normal vector.
 * @param	interceptWorldCoords	Intercept point in world coordinates.
 * @param	eyeWorldCoord			Eye world coordinate.
 * @param	viewingMatrix			Viewing matrix.
 * @return	The color produced at the intercept point, given this light.
 * @todo Lab
 */

color PositionalLight::illuminate(const Material &material, 
									const glm::vec3 &normal,
									const glm::vec3 &interceptWorldCoords,
									const glm::vec3 &eyeWorldCoord,
									const glm::mat4 &viewingMatrix) const {
	if (!isOn) return material.ambient;

	//glm::vec3 l = glm::normalize(lightPosition - interceptWorldCoords);
	glm::vec3 v = glm::normalize(eyeWorldCoord - interceptWorldCoords);
	color result = totalColor(material, lightColorComponents, v, normal, this->lightPosition, interceptWorldCoords, this-> attenuationIsTurnedOn, this->attenuationParams);
	return result;
	//already did this calculation for raytracing, reusing

}

/**
 * @fn	color SpotLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir, const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	hit					The surface properties of the intercept point.
 * @param	viewingDir			Viewing direction.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 * @todo Lab
 */

color SpotLight::illuminate(const HitRecord &hit, const glm::vec3 &viewingDir, const Frame &eyeFrame, bool inShadow) const {
	color result;
	if (inShadow) {
		result = hit.material.ambient * this->lightColorComponents.ambient;
		//result = yellow; //  Test Shadows here  //
	}
	else {
		result = totalColor(hit.material, this->lightColorComponents, viewingDir, hit.surfaceNormal, this->lightPosition, hit.interceptPoint, this->attenuationIsTurnedOn, this->attenuationParams);
	}

	return result;
}

/**
 * @fn	color SpotLight::illuminate(const Material &material, const glm::vec3 &normal, const glm::vec3 &interceptWorldCoords, const glm::vec3 &eyeWorldCoord, const glm::mat4 &viewingMatrix) const
 * @brief	Computes the color this light produces in pipeline applications.
 * @param	material				Material properties.
 * @param	normal					Surface normal vector.
 * @param	interceptWorldCoords	Intercept point in world coordinates.
 * @param	eyeWorldCoord			Eye world coordinate.
 * @param	viewingMatrix			Viewing matrix.
 * @return	The color produced at the intercept point, given this light.
 * @todo Lab
 */

color SpotLight::illuminate(const Material &material,
							const glm::vec3 &normal,
							const glm::vec3 &interceptWorldCoords,
							const glm::vec3 &eyeWorldCoord,
							const glm::mat4 &viewingMatrix) const {
	return material.ambient;
}

/**
* @fn	ostream &operator << (std::ostream &os, const LightAttenuationParameters &at)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	at		Attenuation parameters.
* @return	The output stream.
*/

std::ostream &operator << (std::ostream &os, const LightAttenuationParameters &at) {
	os << glm::vec3(at.constant, at.linear, at.quadratic) << std::endl;
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const PositionalLight &pl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	pl		Positional light.
* @return	The output stream.
*/

std::ostream &operator << (std::ostream &os, const PositionalLight &pl) {
	os << (pl.isOn ? "ON" : "OFF") << std::endl;
	os << (pl.isTiedToWorld? "WORLD" : "CAMERA") << std::endl;
	os << " position " << pl.lightPosition << std::endl;
	os << " ambient " << pl.lightColorComponents.ambient << std::endl;
	os << " diffuse " << pl.lightColorComponents.diffuse << std::endl;
	os << " specular " << pl.lightColorComponents.specular << std::endl;
	os << "Attenuation: " << (pl.attenuationIsTurnedOn ? "ON" : "OFF")
		<< " " << pl.attenuationParams << std::endl;
	return os;
}

/**
* @fn	ostream &operator << (std::ostream &os, const SpotLight &sl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	sl		Spotlight.
* @return	The output stream.
*/

std::ostream &operator << (std::ostream &os, const SpotLight &sl) {
	PositionalLight pl = (sl);
	os << pl;
	os << " FOV " << sl.fov << std::endl;
	return os;
}