#include "Camera.h"

void Camera::setupCamera(glm::ivec2 windowSize)
{
	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 1000.0f;
	
	wIterator.resize(viewport.width);
	hIterator.resize(viewport.height);

	for (int i = 0; i < viewport.width; i++)
		wIterator[i] = i;		
	for (int i = 0; i < viewport.height; i++)
		hIterator[i] = i;

	proj = glm::perspectiveFov(glm::radians(45.0f), (float)viewport.width, (float)viewport.height, viewport.near, viewport.far);
	view = glm::translate(glm::mat4(1.0f), pos);
	model = glm::mat4(1.0f);
}

Ray Camera::castRay(int x, int y, glm::mat4& proj, glm::mat4& view) // Complex ray generation
{
	Ray ray;

	glm::vec4 vp = glm::vec4(0, 0, viewport.width, viewport.height);
	y = (int)vp.w - y;

	glm::vec3 near = glm::unProject(glm::vec3(x, y, -1), view, proj, vp); // make function mine rather than using glm::unproject
	glm::vec3 far = glm::unProject(glm::vec3(x, y, 1), view, proj, vp);

	ray.direction = glm::normalize(far - near);
	ray.origin = near;
	
	return ray;
}

void Camera::CalculateRayDirections()
{
	m_RayDirections.resize(viewport.width * viewport.height);

	for (uint32_t y = 0; y < viewport.height; y++)
	{
		for (uint32_t x = 0; x < viewport.width; x++)
		{
			glm::vec2 coord = { (float)x / (float)viewport.width, (float)y / (float)viewport.height };
			coord = coord * 2.0f - 1.0f; // -1 -> 1

			glm::vec4 target = (glm::inverse(proj))*glm::vec4(coord.x, coord.y, 1, 1);
			glm::vec3 rayDirection = glm::vec3((glm::inverse(view)) * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			m_RayDirections[x + y * viewport.width] = rayDirection;
		}
	}
}

/*Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray _ray;

	_ray.Origin = glm::vec3((float)windowPos.x, (float)windowPos.y, 0.0f);
	_ray.Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	return _ray;
}*/ // old simple ray generation