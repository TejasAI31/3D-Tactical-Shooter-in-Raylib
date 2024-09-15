#pragma once
#include "IncludeHeaders.h"

class cell
{
public:
	Vector2 position;
	bool walls[4] = {true,true,true,true};
	wall cellwalls[4];

	bool initexplored = false;
};