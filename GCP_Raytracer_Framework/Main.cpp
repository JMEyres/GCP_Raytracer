#include "GCP_GFX_Framework.h"

#undef main

int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(640, 480);

	int numThreads = 2;

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}

	// init raytracer stuff
	RayTracer _rayTracer;
	Camera _camera;

	_camera.setupCamera(winSize);
	_myFramework.SetAllPixels(glm::vec3(0));

	_rayTracer.CreateSphere(glm::vec3(1.0f, 1.0f, -10.0f), 1.0f, glm::vec3 (1.0f,0.0f,0.0f),0);
	_rayTracer.CreateSphere(glm::vec3(0.0f, 0.0f, -10.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f),10.0f);


	std::chrono::steady_clock::time_point time1 =
		std::chrono::high_resolution_clock::now();

	

	// essentially need to split this up into multiple rows and have a thread per row so would have window x the same and then window y/num threads to give each block
	// then would would loop through all pixels in window x by block y

	for (int i = 0; i < winSize.x; i++)
	{
		for (int j = 0; j < winSize.y; j++)
		{
			glm::ivec2 pixelPosition = {i, j};
			Ray ray = _camera.castRay(pixelPosition.x, pixelPosition.y, _camera.proj, _camera.view);
			glm::vec3 pixelColour = _rayTracer.TraceRay(ray);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
		}
	}

	std::chrono::steady_clock::time_point time2 =
		std::chrono::high_resolution_clock::now();

	std::chrono::milliseconds milliseconds =
		std::chrono::duration_cast<std::chrono::milliseconds> (time2 - time1);

	std::ofstream fs;
	fs.open("../perfomance.txt");

	fs << "Time taken: " << milliseconds.count() << "\n";

	fs.close();

	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;
}
