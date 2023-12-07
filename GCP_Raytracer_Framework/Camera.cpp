#include "Camera.h"

void Camera::setupCamera(glm::ivec2 windowSize)
{
	//cameraAngleX = 0.0f, cameraAngleY = 0.0f;

	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 1000.0f;
	
	proj = glm::perspective(glm::radians(45.0f), viewport.width/viewport.height, viewport.near, viewport.far);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.5f));;
	model = glm::mat4(1.0f);
}

void Camera::updateCamera()
{
	view = glm::translate((glm::rotate(glm::mat4(1.0f), cameraAngleY, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(1.0f), cameraAngleX, glm::vec3(0, 1, 0))), glm::vec3(0, 0, -3.5f));
}

Ray Camera::castRay(int x, int y, glm::mat4& proj, glm::mat4& view) // Complex ray generation
{
	Ray ray;

	glm::vec4 vp = glm::vec4(0, 0, viewport.width, viewport.height);
	y = (int)vp.w - y;

	glm::vec3 near = glm::unProject(glm::vec3(x, y, -1), view, proj, vp); // make function mine rather than using glm::unproject
	glm::vec3 far = glm::unProject(glm::vec3(x, y, 1), view, proj, vp);

	ray.Direction = glm::normalize(far - near);
	ray.Origin = near;
	
	return ray;
}

/*Ray Camera::GetRay(glm::ivec2 windowPos)
{
	Ray _ray;

	_ray.Origin = glm::vec3((float)windowPos.x, (float)windowPos.y, 0.0f);
	_ray.Direction = glm::vec3(0.0f, 0.0f, 1.0f);

	return _ray;
}*/ // old simple ray generation