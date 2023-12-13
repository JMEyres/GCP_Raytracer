#include "Camera.h"

/// <summary>
/// Define the parameters of the camera here
/// </summary>
/// <param name="windowSize"></param>
void Camera::SetupCamera(glm::ivec2 windowSize)
{

	viewport.width = (float)windowSize.x;
	viewport.height = (float)windowSize.y;
	viewport.near = 0.1f;
	viewport.far = 1000.0f;

	proj = glm::perspective(glm::radians(45.0f), viewport.width/viewport.height, viewport.near, viewport.far);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.5f));;
	model = glm::mat4(1.0f);
}

/// <summary>
/// The function used to cast rays from the camera onto the scene using complex ray generation with near planes and far planes
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="proj"></param>
/// <param name="view"></param>
/// <returns> The ray generated </returns>
Ray Camera::CastRay(int x, int y, glm::mat4& proj, glm::mat4& view) // Complex ray generation
{
	Ray ray;

	glm::vec4 vp = glm::vec4(0, 0, viewport.width, viewport.height);
	y = (int)vp.w - y;

	glm::vec3 near = ConvertToNDC(glm::vec3(x, y, -1), view, proj, vp);
	glm::vec3 far = ConvertToNDC(glm::vec3(x, y, 1), view, proj, vp);

	ray.direction = glm::normalize(far - near);
	ray.origin = near;
	
	return ray;
}

/// <summary>
/// This function is used to convert coordinates into normalised device coordinates which gets them into a -1 to 1 scale
/// </summary>
/// <param name="coords"></param>
/// <param name="view"></param>
/// <param name="proj"></param>
/// <param name="viewport"></param>
/// <returns> Normalised device coordinates of inputted pixels </returns>
glm::vec3 const Camera::ConvertToNDC(glm::vec3 const coords, glm::mat4 const view, glm::mat4 const proj, glm::vec4 const viewport)
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