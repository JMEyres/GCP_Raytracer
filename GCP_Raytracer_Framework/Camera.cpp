#include "Camera.h"

void Camera::setupCamera(glm::ivec2 windowSize)
{

	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 1000.0f;

	proj = glm::perspective(glm::radians(45.0f), viewport.width/viewport.height, viewport.near, viewport.far);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.5f));;
	model = glm::mat4(1.0f);
}

Ray Camera::castRay(int x, int y, glm::mat4& proj, glm::mat4& view) // Complex ray generation
{
	Ray ray;

	glm::vec4 vp = glm::vec4(0, 0, viewport.width, viewport.height);
	y = (int)vp.w - y;

	glm::vec3 near = convertToNDC(glm::vec3(x, y, -1), view, proj, vp);
	glm::vec3 far = convertToNDC(glm::vec3(x, y, 1), view, proj, vp);

	ray.direction = glm::normalize(far - near);
	ray.origin = near;
	
	return ray;
}

glm::vec3 const Camera::convertToNDC(glm::vec3 const coords, glm::mat4 const view, glm::mat4 const proj, glm::vec4 const viewport)
{
	glm::mat4 inverse = glm::inverse(proj * view);
	glm::vec4 tmp = glm::vec4(coords,1.0f);
	tmp.x = ((tmp.x - viewport[0]) / viewport[2]);
	tmp.y = ((tmp.y - viewport[1]) / viewport[3]);
	tmp = tmp * 2.0f - 1.0f;

	glm::vec4 obj = inverse * tmp;
	obj /= obj.w;
	return glm::vec3(obj);
}