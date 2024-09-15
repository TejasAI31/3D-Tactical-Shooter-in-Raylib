#pragma once


//Global Variables
Vector2 playerpos;
Vector2 mousepos;
Vector3 worldplayerpos;

Texture2D floortexture;

BoundingBox hitbox;

ray rays[maxrays];
cell cells[heightcells][widthcells];
worldcell worldcells[heightcells][widthcells];

Camera3D playercam = { 0 };

int currentcell[2];
int currentworldcell[2];

float playerfov = fov;
float lineofsight;

bool minimapstage = true;
bool worldinit = false;
