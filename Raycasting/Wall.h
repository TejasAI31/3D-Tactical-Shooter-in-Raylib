#pragma once
#include "IncludeHeaders.h"

#define wallthickness 10

class wall
{
public:
	Vector2 startpos, endpos;
	double thickness = wallthickness;
	double height;
};