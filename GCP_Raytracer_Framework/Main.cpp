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
	SDL_Event incomingEvent;

	_camera.setupCamera(winSize); // if i want to make the camera move i need to do it directly in the show and hold function in the framework

	_myFramework.SetAllPixels(glm::vec3(0)); // just make all pixels black to begin with

	_rayTracer.CreateSphere(glm::vec3(-1.5f, 0.0f, -10.0f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Position, Radius and color of sphere respectively
	_rayTracer.CreateSphere(glm::vec3(1.5f, 0.0f, -10.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	_rayTracer.CreateSphere(glm::vec3(0.0f, 2.0f, -10.0f), 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	_rayTracer.CreateSphere(glm::vec3(0.0f, -2.0f, -10.0f), 1.0f, glm::vec3(0.975f, 0.382f, 0.0f));

	std::chrono::steady_clock::time_point time1 =
		std::chrono::high_resolution_clock::now(); // Take the time before the render

	_rayTracer.Render(_camera, _myFramework); // do the actual ray tracing

	/* 
	multithreading this wouldnt have a huge effect because it is currently just rendered once and thats it,
	so the impact of creating the threads may in fact just slow it down, however i should multithread it, take the performance, 
	then make it update in real time with moving the camera and then see the difference there.

	Would then allow me to compare 
	single threaded static performance
	multi threaded static performance
	single threaded real time performance
	multi threaded real time performance
	*/

	std::chrono::steady_clock::time_point time2 =
		std::chrono::high_resolution_clock::now(); // take the time after the render

	std::chrono::milliseconds milliseconds =
		std::chrono::duration_cast<std::chrono::milliseconds> (time2 - time1); // find the difference and you have how long it took to render

	// write performance to file
	std::ofstream fs;
	fs.open("../perfomance.txt");

	fs << "Time taken: " << milliseconds.count() << "\n";

	fs.close();

	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;
}
