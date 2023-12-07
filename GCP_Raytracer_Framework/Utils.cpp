#include "Utils.h"

glm::vec3 Utils::GetNormal(glm::vec3 point, glm::vec3 spherePos)
{
	glm::vec3 center = spherePos;

	glm::vec3 normal = glm::normalize(point - center);// glm::vec3((point.x - center.x) / Radius, (point.y - center.y) / Radius, (point.z - center.z) / Radius);

	return normal;
}