#include "Sphere.h"
#include <glm/gtx/string_cast.hpp>


Sphere::intersect Sphere::RayIntersect(Ray _ray)
{
	float d = glm::length(Position - _ray.Origin - (glm::dot((Position - _ray.Origin), _ray.Direction)) * _ray.Direction);
	float x = glm::sqrt((Radius * Radius) - (d * d));
	glm::vec3 closestIntersect = _ray.Origin + ((glm::dot((Position - _ray.Origin), _ray.Direction) - x) * _ray.Direction);

	glm::vec3 _delta = Position -_ray.Origin;
	float mag = glm::length(_delta);

	//if (mag < (Radius))
		//return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	float direction = glm::dot((Position - _ray.Origin), _ray.Direction);

	if(direction < 0)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	if(d > Radius)
		return Sphere::intersect{ false, glm::vec3(0.0,0.0,0.0) };

	return Sphere::intersect{ true, closestIntersect };
}

glm::vec3 Sphere::Shade(glm::vec3 point)
{
	glm::vec3 lightSource = glm::normalize(glm::vec3(320.0f, 240.0f, -300.0f)); // vector pointing towards the light source not the light sources position in space
	//currently every sphere will have the same shading as its hard set here rather than from a seperate light and calculated from that

	glm::vec3 colour = glm::clamp(glm::dot(lightSource, GetNormal(point)), 0.0f, 1.0f) * glm::vec3(1, 1, 1) * glm::vec3(1, 0, 0);
	return colour;
}

glm::vec3 Sphere::GetNormal(glm::vec3 point)
{
	glm::vec3 center = Position;

	glm::vec3 normal = glm::normalize(point - center);// glm::vec3((point.x - center.x) / Radius, (point.y - center.y) / Radius, (point.z - center.z) / Radius);

	return normal;
}

Sphere Sphere::convertSphereToNDC(Sphere& sphere, glm::mat4& view, glm::mat4& proj, int vpWidth, int vpHeight)
{
	std::cout << "\nSphere Pos: " << glm::to_string(sphere.Position) << std::endl;
	std::cout << "Sphere Radius: " << sphere.Radius << std::endl;

	glm::mat4 viewProjMatrix = proj * glm::inverse(view);
	std::cout << "View-Projection Matrix: " << glm::to_string(viewProjMatrix) << std::endl;
	glm::vec4 csPos = viewProjMatrix * glm::vec4(sphere.Position, 1.0f); // convert to clip space
	std::cout << "Clip Space Coordinates: " << glm::to_string(csPos) << std::endl;

	csPos = csPos / csPos.w; // normalize

	glm::vec2 ndcPos; // convert to ndc
	ndcPos.x = 0.5f * (csPos.x + 1.0f);
	ndcPos.y = 0.5f * (1.0f + csPos.y);
	std::cout << "NDC Coordinates: " << glm::to_string(ndcPos) << std::endl;

	float ndcRad = (glm::length(viewProjMatrix * glm::vec4(sphere.Position + 
		glm::vec3(sphere.Radius, 0.0f, 0.0f), 1.0f)) - csPos.x) / 2; // convert radius to ndc

	//float ndcRad = sphere.Radius / std::abs (csPos.w);
	std::cout << "Radius in NDC: " << ndcRad << std::endl;

	glm::vec2 vpPos = glm::vec2((ndcPos.x*vpWidth),(ndcPos.y*vpHeight));
	std::cout << "Viewport Coordinates: " << glm::to_string(vpPos) << std::endl;
	return { glm::vec3(vpPos, csPos.z), ndcRad };
}