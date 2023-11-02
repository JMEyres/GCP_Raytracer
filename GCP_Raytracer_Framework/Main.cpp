
#include "GCP_GFX_Framework.h"


#undef main


int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(640, 480);

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

	_myFramework.SetAllPixels(glm::vec3(0));

	_rayTracer.CreateSphere();

	for (int i = 0; i < winSize.x; i++)
	{
		for (int j = 0; j < winSize.y; j++)
		{
			glm::ivec2 pixelPosition = {i, j};
			Ray ray = _camera.GetRay(pixelPosition);
			glm::vec3 pixelColour = _rayTracer.TraceRay(ray);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
		}
	}


	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;
}
