#include "RayTracer.h"
#include "GCP_GFX_Framework.h"
#include <sstream>

void RayTracer::Render(Camera& camera, GCP_Framework& framework)
{
	activeCamera = &camera;
	myFramework = &framework;

	buffer.resize(camera.viewport.width * camera.viewport.height);

	glm::vec2 winsize = glm::vec2(camera.viewport.width, camera.viewport.height);
	//std::thread::hardware_concurrency()
	int numThreads = 4;
	totalPassTimes.resize(numThreads);
	CreateThreads(numThreads, winsize);

}

void RayTracer::CreateSphere(glm::vec3 pos, float radius, int matIndex)
{
	Sphere sphere;
	sphere.position = pos;;
	sphere.radius = radius;
	sphere.matIndex = matIndex;
	objectList.push_back(sphere);
}


void RayTracer::CreateMats()
{
	Material orangeSphere;
	orangeSphere.albedo = glm::vec3(0.8f, 0.5f, 0.2f);
	orangeSphere.roughness = 0.1f;
	orangeSphere.emissionColor = orangeSphere.albedo;
	orangeSphere.emissionStrength = 2.0f;
	materialList.push_back(orangeSphere);

	Material blueSphere;
	blueSphere.albedo = glm::vec3(0, 0, 1);
	blueSphere.roughness = 1.0f;
	materialList.push_back(blueSphere);

	Material redSphere;
	redSphere.albedo = glm::vec3(1, 0, 0);
	redSphere.roughness = 0.0f;
	materialList.push_back(redSphere);

	Material greenSphere;
	greenSphere.albedo = glm::vec3(0, 1, 0);
	greenSphere.roughness = 0.0f;
	materialList.push_back(greenSphere);

	Material whiteSphere;
	whiteSphere.albedo = glm::vec3(1, 1, 1);
	whiteSphere.roughness = 0.1f;
	materialList.push_back(whiteSphere);

}
glm::vec4 RayTracer::PerPixel(int x, int y)
{
	Ray ray = activeCamera->castRay(x, y, activeCamera->proj, activeCamera->view); // complex ray generation per pixel on screen
	Ray shadowRay;

	// for emissive materials
	glm::vec3 light(0.0f); 
	glm::vec3 throughput = glm::vec3(1.0f);

	// for standard lighting with fixed light
	glm::vec3 color(0.0f);
	float multiplier = 1.0f;
	int bounces = 5;

	for (int i = 0; i < bounces; ++i)
	{
		// actual intersection check returning hit distance, position, normal and the object index of what is hit
		RayTracer::HitInfo hitInfo = TraceRay(ray);

		if (hitInfo.hitDistance < 0.0f) // if ray hits nothing
		{
			glm::vec3 skyColor = glm::vec3(0.6f, 0.7f, 0.9f); // spheres appear to reflect the sky giving them a strange tint
			color += skyColor * multiplier;
			break;
		}

		Sphere& sphere = objectList[hitInfo.objectIndex]; // set sphere to object that was hit

		glm::vec3 lightDir = glm::normalize(glm::vec3(0,10,0)); // light direction not position, so from the sphere rather than to it
		float lightIntensity = glm::max(glm::dot(hitInfo.hitNormal, -lightDir), 0.0f);

		glm::vec3 sphereColor = materialList[sphere.matIndex].albedo;
		sphereColor *= lightIntensity;
		color += sphereColor * multiplier;

		multiplier *= 0.05f;
		
		throughput *= materialList[sphere.matIndex].albedo;
		light += materialList[sphere.matIndex].GetEmission();

		ray.origin = hitInfo.hitPos + hitInfo.hitNormal * 0.0001f; // have to add a small offset so that the new ray isnt inside the sphere
		shadowRay.origin = hitInfo.hitPos + hitInfo.hitNormal * 0.0001f;
		shadowRay.direction = -lightDir;
		HitInfo shadowHitInfo = TraceRay(shadowRay);
		if (shadowHitInfo.hitDistance > 0.0f)
		{
			color = glm::vec3(0.0f);
		}

#define E
#ifdef EM 
		ray.direction = glm::normalize(hitInfo.hitNormal + Utils::InUnitSphere()); // use emissive lights
	}
	return glm::vec4(light, 1.0f); // return color with an alpha of 1

#else
		ray.direction = glm::reflect(hitInfo.hitPos, hitInfo.hitNormal + materialList[sphere.matIndex].roughness * Utils::InUnitSphere()); // reflect the ray incoming 
		
	}
	return glm::vec4(color, 1.0f); // return color with an alpha of 1

#endif // EM 0
}

RayTracer::HitInfo RayTracer::TraceRay(const Ray& ray) // intersection check
{
	// init vars
	int closestSphere = -1;
	float hitDistance = std::numeric_limits<float>::max();

	for (int i = 0; i < RayTracer::objectList.size(); i++) // loop through all created objects
	{
		Sphere sphere = RayTracer::objectList[i]; // set sphere to current object

		// intersection check using quadratic formula is cleaner than the other method and works properly to find out the closest sphere
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
	}
		if (closestSphere < 0) // if nothing hit ray has missed
			return Miss(ray);

		return ClosestHit(ray, hitDistance, closestSphere);
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

void RayTracer::ParallelRayTrace(Chunk chunk)
{
	std::vector<glm::vec4> parallelBuffer;
	std::vector<std::string> passTimes;

	std::chrono::steady_clock::time_point time1 =
		std::chrono::high_resolution_clock::now();
	for (int p = 0; p < passes; p++)
	{
		for (int i = 0; i < chunk.colSize; i++) // chunk starting x pos should always be 0
		{
			for (int j = chunk.rowStart; j < chunk.rowEnd; j++) // chunk starting y pos should iterate up
			{
				glm::ivec2 pixelPosition = { i, j }; // get the current pixel position
				glm::vec4 pixelColor = PerPixel(pixelPosition.x, pixelPosition.y); // pass that pixel into our per pixel function
				float y = pixelPosition.y;
				float x = pixelPosition.x;
				buffer[(float)(y * chunk.colSize + x)] += pixelColor;
				glm::vec4 bufferPixelColor = buffer[(float)(y * chunk.colSize + x)];
				//glm::ivec2 pixelPosition = { x, y }; // get the current pixel position
				bufferPixelColor = glm::clamp(bufferPixelColor, glm::vec4(0), glm::vec4(1));
				myFramework->DrawPixel(pixelPosition, bufferPixelColor); // draw the pixel
			}
		}

		std::chrono::steady_clock::time_point time2 =
			std::chrono::high_resolution_clock::now(); // take the time after the render

		std::chrono::milliseconds milliseconds =
			std::chrono::duration_cast<std::chrono::milliseconds> (time2 - time1);

		std::ostringstream passString;
		passString << "Pass " << p << ":" << milliseconds.count() << "\n";
		std::string test = passString.str();
		passTimes.push_back(test);
	}
	std::chrono::steady_clock::time_point time3 =
		std::chrono::high_resolution_clock::now(); // take the time after the render

	std::chrono::milliseconds milliseconds =
		std::chrono::duration_cast<std::chrono::milliseconds> (time3 - time1);
	// write performance to file
		std::ofstream fs;
		fs.open("../perfomance.txt", std::ofstream::app);
		for (int i = 0; i < passTimes.size(); i++)
			fs << passTimes[i];
		fs << "Thread time: " << milliseconds.count() << "\n" << "\n";
		fs.close();
}

void RayTracer::CreateThreads(int numThreads, glm::ivec2 winSize)
{
	int rowsPerThread = winSize.y / numThreads;

	for (int i = 0; i < numThreads; i++)
	{
		Chunk chunk;
		chunk.colSize = winSize.x;
		chunk.rowStart = i * rowsPerThread;
		chunk.rowEnd = chunk.rowStart + rowsPerThread;
		std::cout << "chunk: " << i << " colSize: " << chunk.colSize << " rowStart: " << chunk.rowStart << " rowEnd: " << chunk.rowEnd << std::endl;
		std::thread chunkThread([chunk, this] { this->ParallelRayTrace(chunk); });
		threads.push_back(std::move(chunkThread));
	}
	std::cout << threads.size() << std::endl;
	for (std::thread& t : threads)
	{
		t.join();
	}
}