#pragma once
#include<iostream>
#include<GLM/glm.hpp>
#include<vector>
#include"Ray.h"

class Camera
{
public:
	glm::mat4 proj, view, model;

	Ray GetRay(glm::ivec2 windowPos);
private:

};