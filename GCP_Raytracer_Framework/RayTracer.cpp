#include "RayTracer.h"
#include "GCP_GFX_Framework.h"

void RayTracer::Render(Camera& camera, GCP_Framework& framework)
{
	activeCamera = &camera;

	// essentially need to split this up into multiple rows and have a thread per row so would have window x the same and then window y/num threads to give each block
	// then would would loop through all pixels in window x by block y

	//std::thread::hardware_concurrency(); // tells you how many cores are available
	
	// loop through every pixel on the screen

#define MT 1
#if MT 1 // This method just uses all avaliable cores
	std::for_each(std::execution::par, camera.hIterator.begin(), camera.hIterator.end(), [&](int y)
		{
			std::for_each(std::execution::par, camera.wIterator.begin(), camera.wIterator.end(), [&, y](int x)
				{
					glm::ivec2 pixelPosition = { x, y }; // get the current pixel position
					glm::vec4 pixelColour = PerPixel(pixelPosition.x, pixelPosition.y); // pass that pixel into our per pixel function
					framework.DrawPixel(pixelPosition, pixelColour); // draw the pixel
				});
		});
//#elseif MT 2
	//	int numThreads = 2;
	//for (int i = 0; i < numThreads; i++)
	//{

	//}
#else
	for (int i = 0; i < camera.viewport.width; i++)
	{
		for (int j = 0; j < camera.viewport.height; j++)
		{
			glm::ivec2 pixelPosition = { i, j }; // get the current pixel position
			glm::vec4 pixelColour = PerPixel(pixelPosition.x, pixelPosition.y); // pass that pixel into our per pixel function
			framework.DrawPixel(pixelPosition, pixelColour); // draw the pixel
		}
	}
#endif

}

void RayTracer::CreateSphere(glm::vec3 pos, float radius, glm::vec3 color, float roughness, float metalness)
{
	Sphere sphere;
	sphere.position = pos;;
	sphere.radius = radius;
	sphere.mat.albedo = color;
	sphere.mat.roughness = roughness;
	sphere.mat.metalness = metalness;

	objectList.push_back(sphere);
}

glm::vec4 RayTracer::PerPixel(int x, int y)
{
	Ray ray = activeCamera->castRay(x, y, activeCamera->proj, activeCamera->view); // complex ray generation per pixel on screen

	glm::vec3 color(0.0f); // initialise color
	float multiplier = 1.0f; // have multiplier so it isnt just full color forever


	int bounces = 5;
	for (int i = 0; i < bounces; ++i)
	{
		// actual intersection check returning hit distance, position, normal and the object index of what is hit
		RayTracer::HitInfo hitInfo = TraceRay(ray);

		if (hitInfo.hitDistance < 0) // if ray hits nothing
		{
			//glm::vec3 skyColor = glm::vec3(0.6f, 0.7f, 0.9f);
			glm::vec3 skyColor = glm::vec3(0);
			color += skyColor * multiplier;
			break;
		}

		glm::vec3 lightDir = glm::normalize(glm::vec3(-1.0f)); // light direction not position, so from the sphere rather than to it
		float lightIntensity = glm::max(glm::dot(hitInfo.hitNormal, -lightDir), 0.0f);

		Sphere& sphere = RayTracer::objectList[hitInfo.objectIndex]; // set sphere to object that was hit

		glm::vec3 sphereColor = sphere.mat.albedo;
		sphereColor *= lightIntensity;
		color += sphereColor * multiplier;
		multiplier *= 0.5f; // makes it properly fade in the reflection

		ray.origin = hitInfo.hitPos + 0.0001f; // have to add a small offset so that the new ray isnt inside the sphere
		ray.direction = glm::reflect(hitInfo.hitPos, hitInfo.hitNormal + sphere.mat.roughness * Utils::RandomVector()); // reflect the ray incoming 
		// introduced roughness this could be improved with path tracing and accumulating images so they improve over time
	}

	return glm::vec4(color, 1.0f); // return color with an alpha of 1
}

RayTracer::HitInfo RayTracer::TraceRay(const Ray& ray) // intersection check
{
	// init vars
	int closestSphere = -1;
	float hitDistance = std::numeric_limits<float>::max();

	for (int i = 0; i < RayTracer::objectList.size(); i++) // loop through all created objects
	{
		Sphere sphere = RayTracer::objectList[i]; // set sphere to current object

		// intersection check using quadratic formula
		glm::vec3 origin = ray.origin - sphere.position;
		float a = glm::dot(ray.direction, ray.direction);
		float b = 2.0f * glm::dot(origin, ray.direction);
		float c = glm::dot(origin, origin) - sphere.radius * sphere.radius;

		float discriminant = b * b - 4.0f * a * c;
		if (discriminant < 0.0f)
			continue;

		float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);
		if (closestT > 0 && closestT < hitDistance)
		{
			hitDistance = closestT;
			closestSphere = (int)i;
		}

		if (closestSphere < 0) // if nothing hit ray has missed
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
	glm::vec3 origin = ray.origin - closestSphere.position;
	hitInfo.hitPos = origin + ray.direction * hitDistance;
	hitInfo.hitNormal = glm::normalize(hitInfo.hitPos);

	hitInfo.hitPos += closestSphere.position;

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