#include "RayTracer.h"
#include "GCP_GFX_Framework.h"

void RayTracer::Render(Camera& camera, GCP_Framework& framework)
{
	activeCamera = &camera;

	// essentially need to split this up into multiple rows and have a thread per row so would have window x the same and then window y/num threads to give each block
	// then would would loop through all pixels in window x by block y

	// loop through every pixel on the screen
	for (int i = 0; i < camera.viewport.width; i++)
	{
		for (int j = 0; j < camera.viewport.height; j++)
		{
			glm::ivec2 pixelPosition = { i, j };
			glm::vec4 pixelColour = PerPixel(pixelPosition.x, pixelPosition.y);
			framework.DrawPixel(pixelPosition, pixelColour);
		}
	}
}

void RayTracer::CreateSphere(glm::vec3 _pos, float _radius, glm::vec3 _color)
{
	Sphere sphere;
	sphere.Position = _pos;;
	sphere.Radius = _radius;
	sphere.colour = _color;
	objectList.push_back(sphere);
}

glm::vec4 RayTracer::PerPixel(int x, int y)
{
	Ray ray = activeCamera->castRay(x, y, activeCamera->proj, activeCamera->view); // complex ray generation per pixel on screen

	glm::vec3 color(0.0f); // initialise color
	float multiplier = 1.0f; // have multiplier so it isnt just full color forever


	int bounces = 2;
	for (int i = 0; i < bounces; ++i)
	{
		// actual intersection check returning hit distance, position, normal and the object index of what is hit
		RayTracer::HitInfo hitInfo = TraceRay(ray);

		if (hitInfo.hitDistance < 0) // if ray hits nothing
		{
			glm::vec3 skyColor = glm::vec3(0.0f, 0.0f, 0.0f); // currently sky is just black, could be changed to something else
			color += skyColor * multiplier;
			break;
		}

		glm::vec3 lightDir = glm::normalize(glm::vec3(0.0f,1.0f,0.0f)); // light direction not position, so from the sphere rather than to it
		float lightIntensity = glm::max(glm::dot(hitInfo.hitNormal, -lightDir), 0.0f);

		Sphere& sphere = RayTracer::objectList[hitInfo.objectIndex];

		glm::vec3 sphereColor = sphere.colour;
		sphereColor *= lightIntensity;
		color += sphereColor * multiplier;
		multiplier *= 0.7f; // makes it properly fade in the reflection

		ray.Origin = hitInfo.hitPos + 0.0001f;
		ray.Direction = glm::reflect(hitInfo.hitPos, hitInfo.hitNormal); // reflect the ray incoming 
	}

	return glm::vec4(color, 1.0f);
}


RayTracer::HitInfo RayTracer::TraceRay(const Ray& ray) // intersection check
{
	int closestSphere = -1;
	float hitDistance = std::numeric_limits<float>::max();

	for (int i = 0; i < RayTracer::objectList.size(); i++)
	{
		Sphere sphere = RayTracer::objectList[i];

		glm::vec3 origin = ray.Origin - sphere.Position;
		float a = glm::dot(ray.Direction, ray.Direction);
		float b = 2.0f * glm::dot(origin, ray.Direction);
		float c = glm::dot(origin, origin) - sphere.Radius * sphere.Radius;

		float discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0.0f)
			continue;

		float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
		if (closestT > 0 && closestT < hitDistance)
		{
			hitDistance = closestT;
			closestSphere = (int)i;
		}

		if (closestSphere < 0)
			return Miss(ray);

		return ClosestHit(ray, hitDistance, closestSphere);
	}

	
}
RayTracer::HitInfo RayTracer::ClosestHit(const Ray& ray, float hitDistance, int objectIndex) // define what is the closest object to be hit
{
	RayTracer::HitInfo hitInfo;
	hitInfo.hitDistance = hitDistance;
	hitInfo.objectIndex = objectIndex;

	Sphere& closestSphere = RayTracer::objectList[objectIndex];
	glm::vec3 origin = ray.Origin - closestSphere.Position;
	hitInfo.hitPos = origin + ray.Direction * hitDistance;
	hitInfo.hitNormal = glm::normalize(hitInfo.hitPos);

	hitInfo.hitPos += closestSphere.Position;

	return hitInfo;
};
RayTracer::HitInfo RayTracer::Miss(const Ray& ray) 
{
	RayTracer::HitInfo hitinfo;
	hitinfo.hitDistance = -1.0f;
	return hitinfo;
};

/*float d = glm::length(Position - _ray.Origin - (glm::dot((Position - _ray.Origin), _ray.Direction)) * _ray.Direction);
	float x = glm::sqrt((Radius * Radius) - (d * d));
	glm::vec3 closestIntersect = _ray.Origin + ((glm::dot((Position - _ray.Origin), _ray.Direction) - x) * _ray.Direction);

	float direction = glm::dot((Position - _ray.Origin), _ray.Direction);

	if (direction < 0)
		return Sphere::HitInfo{ false, glm::vec3(0.0,0.0,0.0) };

	if (d > Radius)
		return Sphere::HitInfo{ false, glm::vec3(0.0,0.0,0.0) };

	return Sphere::HitInfo{ true, closestIntersect };*/