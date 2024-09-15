#pragma once
#include "IncludeHeaders.h"

class worldcell
{
public:
	Vector3 position;
	worldwall worldcellwalls[4];


	Mesh leftwallmesh;
	Mesh rightwallmesh;
	Mesh bottomwallmesh;
	Mesh topwallmesh;
	Mesh floormesh;
	Mesh ceilingmesh;

	Model floormodel;
	Model leftwallmodel;
	Model rightwallmodel;
	Model bottomwallmodel;
	Model topwallmodel;
	Model ceilingmodel;
};