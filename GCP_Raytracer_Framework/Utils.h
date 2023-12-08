#pragma once
#include<GLM/glm.hpp>
#include <random>

namespace Utils
{
	glm::vec3 GetNormal(glm::vec3 point, glm::vec3 spherePos);

	static float Float()
	{
		std::mt19937 s_RandomEngine;
		std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
		s_RandomEngine.seed(std::random_device()());
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}

	static glm::vec3 Vec3(float min, float max)
	{
		return glm::vec3(Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min);
	}

	static glm::vec3 InUnitSphere()
	{
		return glm::normalize(Vec3(-1.0f, 1.0f));
	}
}

 