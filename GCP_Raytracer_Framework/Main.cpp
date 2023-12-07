#include "GCP_GFX_Framework.h"

#undef main

int main(int argc, char* argv[]) // Render function
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

	_camera.setupCamera(winSize);

	/*while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
			switch (incomingEvent.key.keysym.sym)
		case SDLK_DOWN:
			_camera.cameraAngleY -= 0.1f;
		case SDLK_UP:
			_camera.cameraAngleY += 0.1f;
		case SDLK_LEFT:
			_camera.cameraAngleX -= 0.1f;
		case SDLK_RIGHT:
			_camera.cameraAngleX += 0.1f;
		}
	}

	_camera.view = glm::translate((glm::rotate(glm::mat4(1.0f), _camera.cameraAngleY, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), _camera.cameraAngleX, glm::vec3(0, 1, 0))), glm::vec3(0, 0, -3.5f));*/
	_myFramework.SetAllPixels(glm::vec3(0));

	_rayTracer.CreateSphere(glm::vec3(-1.5f, 0.0f, -10.0f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Position, Radius and color of sphere
	_rayTracer.CreateSphere(glm::vec3(1.5f, 0.0f, -10.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	_rayTracer.CreateSphere(glm::vec3(0.0f, 2.0f, -10.0f), 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	_rayTracer.CreateSphere(glm::vec3(0.0f, -2.0f, -10.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	std::chrono::steady_clock::time_point time1 =
		std::chrono::high_resolution_clock::now();
	
	_rayTracer.Render(_camera, _myFramework);

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
