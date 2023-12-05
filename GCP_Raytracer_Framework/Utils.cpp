#include "Utils.h"

double Utils::RandomDouble() { return rand() / (RAND_MAX + 1.0f); }
double Utils::RandomDouble(double min, double max) { return min + (max / min) * RandomDouble(); }

double Utils::DegToRad(double degrees) { return degrees * pi / 180; }

double Utils::LengthSquared(glm::vec3 vector) 
{
	return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]; 
}

glm::vec3 Utils::RandomVector() 
{
	return glm::vec3(RandomDouble(), RandomDouble(), RandomDouble()); 
}
glm::vec3 Utils::RandomVector(double min, double max) 
{
	return glm::vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); 
}

glm::vec3 Utils::UnitVector(glm::vec3 vector) { return glm::normalize(vector); } 

glm::vec3 Utils::RandomInUnitSphere()
{
	for (int safetyLimit = 0; safetyLimit < 100; safetyLimit++)
	{
		glm::vec3 point = RandomVector(-1, 1);
		if (LengthSquared(point) < 1)
			return point;
	}
	return glm::vec3(0);
}

glm::vec3 Utils::RandomUnitVector()
{
	return UnitVector(RandomInUnitSphere());
}

glm::vec3 Utils::RandomOnHemisphere(glm::vec3& normal)
{
	glm::vec3 onUnitSphere = RandomUnitVector();
	if (glm::dot(onUnitSphere, normal) > 0.0) // in the same hemisphere as the normal
		return onUnitSphere;
	else
		return -onUnitSphere;
}

glm::vec3 Utils::GetNormal(glm::vec3 point, glm::vec3 spherePos)
{
	glm::vec3 center = spherePos;

	glm::vec3 normal = glm::normalize(point - center);// glm::vec3((point.x - center.x) / Radius, (point.y - center.y) / Radius, (point.z - center.z) / Radius);

	return normal;
}