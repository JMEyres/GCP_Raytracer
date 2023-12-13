#include "GCP_GFX_Framework.h"

#undef main

int main(int argc, char* argv[]) 
{
	// Set window size
	glm::ivec2 winSize(640, 480);
	int numThreads = 4;

	std::ofstream fs;
	fs.open("../perfomance.txt");
	fs << "";
	fs.close();

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

	_camera.setupCamera(winSize); // if i want to make the camera move i need to do it directly in the show and hold function in the framework

	_myFramework.SetAllPixels(glm::vec3(0)); // just make all pixels black to begin with

	_rayTracer.CreateMats(); // 0:orange, 1: blue, 2: red, 3:green, 4:white

	_rayTracer.CreateSphere(glm::vec3(-1.5f, 0.0f, -5.0f), 1.0f, 2); // Position, Radius and material of sphere respectively
	_rayTracer.CreateSphere(glm::vec3(1.5f, 0.0f, -5.0f), 1.0f, 3);
	_rayTracer.CreateSphere(glm::vec3(5.0f, -4.0f, -10.0f), 5.0f, 0);
	_rayTracer.CreateSphere(glm::vec3(0.0f, 102.0f, -5.0f), 100.0f, 1);

	std::chrono::steady_clock::time_point time1 =
		std::chrono::high_resolution_clock::now(); // Take the time before the render

	_rayTracer.Render(_camera, _myFramework, numThreads); // do the actual ray tracing

	std::chrono::steady_clock::time_point time2 =
		std::chrono::high_resolution_clock::now(); // take the time after the render

	std::chrono::milliseconds milliseconds =
		std::chrono::duration_cast<std::chrono::milliseconds> (time2 - time1); // find the difference and you have how long it took to render

	// write performance to file
	//std::ofstream fs;
	fs.open("../perfomance.txt", std::ofstream::app);
	fs << "Total time taken to render: " << milliseconds.count() << "\n";
	fs.close();

	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;
}
