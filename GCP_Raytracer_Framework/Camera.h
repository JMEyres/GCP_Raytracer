#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include"Ray.h"

class Camera
{
public:
	glm::mat4 view1, view2, view3;

	Ray GetRay(glm::ivec2 windowPos);
private:

};