#include "Sphere.h"
#include <glm/gtx/string_cast.hpp>

/*glm::vec3 Sphere::Shade(glm::vec3 point, Ray ray)
{
	int bounces = 2;
	glm::vec3 colour(0.0f);
	float multiplier = 1.0f;

	glm::vec3 lightSource = glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f)); // vector pointing towards the light source not the light sources position in space
	//currently every sphere will have the same shading as its hard set here rather than from a seperate light and calculated from that
	glm::vec3 lightColour = glm::vec3(1, 1, 1);
	glm::vec3 surfaceNormal = Utils::GetNormal(point, Position);
	colour = glm::clamp(glm::dot(lightSource, surfaceNormal), 0.0f, 1.0f) * lightColour * sphere.colour; // light source is vector pointing towards the light, getnormal is the surface normal, glm::vec3 is the light colour and material colour

	Ray reflectionRay;
	reflectionRay.Origin = point;
	reflectionRay.Direction = glm::reflect(ray.Direction, surfaceNormal);

	return colour;
}*/

