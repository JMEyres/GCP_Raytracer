#include "Utils.h"

glm::vec3 Utils::GetNormal(glm::vec3 point, glm::vec3 spherePos)
{
	glm::vec3 center = spherePos;

	glm::vec3 normal = glm::normalize(point - center);// glm::vec3((point.x - center.x) / Radius, (point.y - center.y) / Radius, (point.z - center.z) / Radius);

	return normal;
}

float Utils::RandomValue()
{
	float randomNum = rand();
	return randomNum;
}

glm::vec3 Utils::RandomHemisphereDirection(glm::vec3 normal)
{
	glm::vec3 dir = Utils::RandomDirection();
	return dir * glm::sign(glm::dot(normal, dir));
}

glm::vec3 Utils::RandomDirection()
{
	float x = RandomValue();
	float y = RandomValue();
	float z = RandomValue();
	return glm::normalize(glm::vec3(x, y, z));
}