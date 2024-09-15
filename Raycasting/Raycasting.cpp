//ALL ANGLES ARE IN RADIANS
#include "IncludeHeaders.h"
#include "math.h"

using namespace std;

Zombie zombie;

Model gunmodel;


//MINIMAP FUNCTIONS

/*void shoot()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{

		for(int x=maxrays/2-maxrays/3;x<maxrays/2+maxrays/3;x++)
		for (int y = 0; y < maxwalls; y++)
		{
			Vector2 temppos = { playerpos.x + maxlightdistance * cos(rays[x].dir), playerpos.y + maxlightdistance * sin(rays[x].dir) };

			float denom = (playerpos.x - temppos.x) * (walls[y].startpos.y - walls[y].endpos.y) - (playerpos.y - temppos.y) * (walls[y].startpos.x - walls[y].endpos.x);
			if (denom == 0)
				continue;

			float t = ((playerpos.x - walls[y].startpos.x) * (walls[y].startpos.y - walls[y].endpos.y) - (playerpos.y - walls[y].startpos.y) * (walls[y].startpos.x - walls[y].endpos.x)) / denom;
			float u = -((playerpos.x - temppos.x) * (playerpos.y - walls[y].startpos.y) - (playerpos.y - temppos.y) * (playerpos.x - walls[y].startpos.x)) / denom;

			if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			{
				Vector2 intersectionpoint = { playerpos.x + t * (temppos.x - playerpos.x),playerpos.y + t * (temppos.y - playerpos.y) };
				DrawLineEx(playerpos, intersectionpoint, 10, YELLOW);

			}
			else
			{
				DrawLineEx(playerpos, temppos, 10, YELLOW);
			}
		}
	}
}
*/

void playerMovement()
{
	if (IsKeyDown(KEY_W))
	{
		if (cells[currentcell[0]][currentcell[1]].walls[0] == true && CheckCollisionPointLine(playerpos, cells[currentcell[0]][currentcell[1]].cellwalls[0].startpos, cells[currentcell[0]][currentcell[1]].cellwalls[0].endpos, 10))
			return;
		else
		playerpos.y -= playerspeed*GetFrameTime();
	}
	else if (IsKeyDown(KEY_A))
	{
		if (cells[currentcell[0]][currentcell[1]].walls[3] == true && CheckCollisionPointLine(playerpos, cells[currentcell[0]][currentcell[1]].cellwalls[3].startpos, cells[currentcell[0]][currentcell[1]].cellwalls[3].endpos, 10))
			return;
		else
		playerpos.x -= playerspeed * GetFrameTime();
	}
	if (IsKeyDown(KEY_S))
	{
		if (cells[currentcell[0]][currentcell[1]].walls[2] == true && CheckCollisionPointLine(playerpos, cells[currentcell[0]][currentcell[1]].cellwalls[2].startpos, cells[currentcell[0]][currentcell[1]].cellwalls[2].endpos, 10))
			return;
		else
		playerpos.y += playerspeed * GetFrameTime();
	}
	if (IsKeyDown(KEY_D))
	{
		if (cells[currentcell[0]][currentcell[1]].walls[1] == true && CheckCollisionPointLine(playerpos, cells[currentcell[0]][currentcell[1]].cellwalls[1].startpos, cells[currentcell[0]][currentcell[1]].cellwalls[1].endpos, 10))
			return;
		else
		playerpos.x += playerspeed * GetFrameTime();
	}
}

void setLineOfSight(Vector2 mousepos)
{
	lineofsight = atan((mousepos.y-playerpos.y) / (float)(mousepos.x-playerpos.x));
	if (mousepos.x - playerpos.x < 0)
		lineofsight -= pi;


}

void drawPlayer()
{
	DrawCircleV(playerpos, 10, WHITE);
}

void drawRays()
{
	int emptycells[9][2];

	emptycells[0][0] = currentcell[0];
	emptycells[0][1] = currentcell[1];

	emptycells[1][0] = currentcell[0]+1;
	emptycells[1][1] = currentcell[1];

	emptycells[2][0] = currentcell[0]-1;
	emptycells[2][1] = currentcell[1];

	emptycells[3][0] = currentcell[0];
	emptycells[3][1] = currentcell[1]+1;

	emptycells[4][0] = currentcell[0];
	emptycells[4][1] = currentcell[1]-1;

	emptycells[5][0] = currentcell[0]+1;
	emptycells[5][1] = currentcell[1]-1;

	emptycells[6][0] = currentcell[0]-1;
	emptycells[6][1] = currentcell[1]+1;

	emptycells[7][0] = currentcell[0]+1;
	emptycells[7][1] = currentcell[1]+1;

	emptycells[8][0] = currentcell[0]-1;
	emptycells[8][1] = currentcell[1]-1;


	for (int x = 0; x < maxrays; x++)
	{
		bool flag = false;
		Vector2 temppos={ playerpos.x + maxlightdistance * (float)cos(rays[x].dir), playerpos.y + maxlightdistance * (float)sin(rays[x].dir) };

		for (int z = 0; z < 9; z++)
		{
			bool flag2 = false;
			for (int y = 0; y < 4; y++)
			{

				float x1 = playerpos.x;
				float x2 = temppos.x;
				float x3 = cells[emptycells[z][0]][emptycells[z][1]].cellwalls[y].startpos.x;
				float x4 = cells[emptycells[z][0]][emptycells[z][1]].cellwalls[y].endpos.x;

				float y1 = playerpos.y;
				float y2 = temppos.y;
				float y3 = cells[emptycells[z][0]][emptycells[z][1]].cellwalls[y].startpos.y;
				float y4 = cells[emptycells[z][0]][emptycells[z][1]].cellwalls[y].endpos.y;

				float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
				if (denom == 0)
					continue;


				float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
				float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;

				if (t >= 0 && t <= 1 && u >= 0 && u <= 1 && cells[emptycells[z][0]][emptycells[z][1]].walls[y] == true)
				{
					Vector2 intersectionpoint = { playerpos.x + t * (temppos.x - playerpos.x),playerpos.y + t * (temppos.y - playerpos.y) };
					if (x == maxrays / 2)
					{
						DrawLineEx(playerpos, intersectionpoint, 3, RED);
					}
					else
					{
						DrawLineV(playerpos, intersectionpoint, WHITE);
					}

					flag = true;
					flag2 = true;
					break;
				}
			}
			if (flag2 == true)
				break;
		}
		if (flag == false)
		{
			if (x == maxrays / 2)
			{
				DrawLineEx(playerpos, temppos, 3, RED);
			}
			else
			{
				DrawLineV(playerpos, temppos, WHITE);
			}
		}
	}
}

void drawCells()
{
	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			for(int z=0;z<4;z++)
			if (cells[x][y].walls[z] == true)
			{
				DrawLineEx(cells[x][y].cellwalls[z].startpos, cells[x][y].cellwalls[z].endpos, cells[x][y].cellwalls[z].thickness,WHITE);
			}
		}
	}

	DrawLineEx(cells[heightcells-1][widthcells-1].cellwalls[1].startpos, cells[heightcells-1][widthcells-1].cellwalls[1].endpos, cells[heightcells-1][widthcells-1].cellwalls[1].thickness, GREEN);

}

void initPlayerPos(float a,float b)
{
	playerpos.x = a;
	playerpos.y = b;
	return;
}

void initRays(float playerfov,float lineofsight)
{
	float angle = lineofsight-playerfov / 2;
	for (int x = 0; x < maxrays; x++)
	{
		rays[x].dir = angle;

		angle += playerfov / (float)maxrays;
	}
}

void initCells()
{
	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			cells[x][y].position = { float(y * cellside),float(x * cellside)+25 };

			//TopWall
			cells[x][y].cellwalls[0].startpos = { cells[x][y].position.x-wallthickness/2, cells[x][y].position.y};
			cells[x][y].cellwalls[0].endpos = { cells[x][y].position.x + cellside+wallthickness/2,cells[x][y].position.y };

			//RightWall
			cells[x][y].cellwalls[1].startpos = { cells[x][y].position.x+cellside, cells[x][y].position.y-wallthickness/2 };
			cells[x][y].cellwalls[1].endpos = { cells[x][y].position.x + cellside,cells[x][y].position.y+cellside+wallthickness/2 };

			//LeftWall
			cells[x][y].cellwalls[2].startpos = { cells[x][y].position.x+cellside+wallthickness/2, cells[x][y].position.y+ cellside };
			cells[x][y].cellwalls[2].endpos = { cells[x][y].position.x-wallthickness/2 ,cells[x][y].position.y+cellside };

			//BottomWall
			cells[x][y].cellwalls[3].startpos = { cells[x][y].position.x, cells[x][y].position.y+cellside+wallthickness/2 };
			cells[x][y].cellwalls[3].endpos = { cells[x][y].position.x ,cells[x][y].position.y-wallthickness/2 };
		}
	}
}

int* checkcellneighbors(int currentcell[2])
{
	int nextcell[2] = { -1,-1 };
	int possibilities[4] = {0,0,0,0};
	bool possible = false;

	if (cells[currentcell[0]][currentcell[1] + 1].initexplored == false && currentcell[1] < widthcells - 1)
	{
		possibilities[0] = 1;
		possible = true;
	}
	if (cells[currentcell[0] + 1][currentcell[1]].initexplored == false && currentcell[0] < heightcells - 1)
	{
		possible = true;
		possibilities[1] = 1;
	}
	if (cells[currentcell[0]][currentcell[1] - 1].initexplored == false && currentcell[1] > 0)
	{
		possible = true;
		possibilities[2] = 1;
	}
	if (cells[currentcell[0] - 1][currentcell[1]].initexplored == false && currentcell[0] > 0)
	{
		possible = true;
		possibilities[3] = 1;
	}

	int random=4;

	if(possible==true)
	do {
		random = rand() % 4;
	} while (possibilities[random]!=1);

	//RightCell
	if (random==0)
	{
		cells[currentcell[0]][currentcell[1]].walls[1] = false;
		cells[currentcell[0]][currentcell[1]+1].walls[3] = false;
		nextcell[0] = currentcell[0];
		nextcell[1] = currentcell[1]+1;
	}

	//BottomCell
	else if (random==1)
	{
		cells[currentcell[0]][currentcell[1]].walls[2] = false;
		cells[currentcell[0] + 1][currentcell[1]].walls[0] = false;
		nextcell[0] = currentcell[0]+1;
		nextcell[1] = currentcell[1];
	}

	//LeftCell
	else if (random==2)
	{
		cells[currentcell[0]][currentcell[1]].walls[3] = false;
		cells[currentcell[0]][currentcell[1]-1].walls[1] = false;
		nextcell[0] = currentcell[0];
		nextcell[1] = currentcell[1]-1;
	}

	//TopCell
	else if (random==3)
	{
		cells[currentcell[0]][currentcell[1]].walls[0] = false;
		cells[currentcell[0] - 1][currentcell[1]].walls[2] = false;
		nextcell[0] = currentcell[0]-1;
		nextcell[1] = currentcell[1];
	}
	return nextcell;
}

void winCondition()
{
	cells[heightcells - 1][widthcells - 1].walls[1] = false;
}

void initMaze()
{
	int currentcell[2] = { 0,0 };
	cells[currentcell[0], currentcell[1]]->initexplored = true;

	bool finishflag = false;
	int stack[widthcells * heightcells][2];
	int stackcounter = 0;
	

	while (finishflag == false)
	{
		drawCells();
		int* neighbor =checkcellneighbors(currentcell);

		if (neighbor[0] != -1 && neighbor[1] != -1)
		{
			stack[stackcounter][0] = currentcell[0];
			stack[stackcounter][1] = currentcell[1];

			stackcounter++;

			currentcell[0] = neighbor[0];
			currentcell[1] = neighbor[1];

			cells[currentcell[0]][ currentcell[1]].initexplored = true;
		}
		
		else
		{
			stackcounter--;
			if (stackcounter == 0)
			{
				finishflag = true;
				break;
			}
			currentcell[0] = stack[stackcounter][0];
			currentcell[1] = stack[stackcounter][1];
		}
	}
	
	winCondition();
}

void getcurrentCell(int* currentcell)
{

	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			Rectangle rect;
			rect.x = cells[x][y].position.x;
			rect.y = cells[x][y].position.y;
			rect.width = cellside;
			rect.height = cellside;
			if (CheckCollisionPointRec(playerpos, rect))
			{
				currentcell[0] = x;
				currentcell[1] = y;
				return;
			}
		}
	}
}

bool checkWinCondition()
{
	if (CheckCollisionPointLine(playerpos, cells[heightcells - 1][widthcells - 1].cellwalls[1].startpos, cells[heightcells - 1][widthcells - 1].cellwalls[1].endpos, 10))
	{
		return true;
	}
	else
		return false;
}

void reset()
{
	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			cells[x][y].initexplored = false;
			for (int z = 0; z < 4; z++)
			{
				cells[x][y].walls[z] = true;
			}
		}
	}

	initPlayerPos(30, 60);
	initCells();
	initMaze();
}

void minimap()
{
	getcurrentCell(currentcell);

	ClearBackground(BLACK);

	//Draws Cells
	drawCells();

	//Moves Player
	playerMovement();

	//Sets Line of sight to mousepos
	setLineOfSight(mousepos);


	//initialises rays
	initRays(playerfov, lineofsight);

	//Draws components
	drawRays();
	drawPlayer();

	//shoot();

	if (checkWinCondition())
	{
		minimapstage = false;
		return;
	}
}


//WORLD FUNCTIONS

void updateTilt()
{
	UpdateCameraPro(&playercam,{ 0,0,0},{GetMouseDelta().x * 0.05f,GetMouseDelta().y * 0.05f,0.0f},0);
}

void updateCam(int coll)
{
	Vector3 temppos;
	Vector3 temptarget;

	if (coll != -1)
	{
		temppos = playercam.position;
		temptarget = playercam.target;
	}

	UpdateCameraPro(&playercam,
		{(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * 0.5f -														 // Move forward-backward
			(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.5f,
			(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.5f -													 // Move right-left
			(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.5f,
			IsKeyDown(KEY_SPACE)*2.0f- IsKeyDown(KEY_LEFT_SHIFT) * 2.0f                                          // Move up-down
		},

		{
			GetMouseDelta().x * 0.05f,								// Rotation: yaw
			GetMouseDelta().y * 0.05f,                          // Rotation: pitch
			0.0f                                                // Rotation: roll
		},
		GetMouseWheelMove() * 2.0f);

	if (coll != -1)
	{
		switch (coll)
		{
		case 0:
			if (playercam.position.z < temppos.z)
			{
				playercam.position = temppos;
				playercam.target = temptarget;
				updateTilt();
			}
			return;
		case 1:
			if (playercam.position.x > temppos.x)
			{
				playercam.position = temppos;
				playercam.target = temptarget;
				updateTilt();
			}
			return;
		case 2:
			if (playercam.position.z > temppos.z)
			{
				playercam.position = temppos;
				playercam.target = temptarget;
				updateTilt();
			}
			return;
		case 3:
			if (playercam.position.x < temppos.x)
			{
				playercam.position = temppos;
				playercam.target = temptarget;
				updateTilt();
			}
			return;
		}
	}
}

void initCamera()
{
	playercam.position = { 10.0f,1.2*playerheight,10.0f };
	playercam.fovy = playerfov*52;
	playercam.target = { 50,15,50};
	playercam.up = { 0.0f, 1.0f, 0.0f };
	playercam.projection = CAMERA_PERSPECTIVE;
}

void initializeWorldCells()
{
	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			worldcells[x][y].position = { float(y * worldcellside)+worldcellside/2,0,float(x * worldcellside+worldcellside/2) };

			//TopWall
			worldcells[x][y].worldcellwalls[0].startpos = { worldcells[x][y].position.x-worldwallthickness/2 ,worldwallheight/2, worldcells[x][y].position.z-worldcellside/2 };
				
			//RightWall
			worldcells[x][y].worldcellwalls[1].startpos = { worldcells[x][y].position.x+worldcellside/2-worldwallthickness/2 ,worldwallheight/2, worldcells[x][y].position.z};

			//LeftWall
			worldcells[x][y].worldcellwalls[2].startpos = { worldcells[x][y].position.x+worldwallthickness/2 ,worldwallheight/2, worldcells[x][y].position.z + worldcellside/2 };

			//BottomWall
			worldcells[x][y].worldcellwalls[3].startpos = { worldcells[x][y].position.x-worldcellside/2, worldwallheight/2 , worldcells[x][y].position.z };
		}
	}
}

void drawWorldCells(Shader shader)
{
	for (int x = 0; x < heightcells; x++)
	{
		for (int y = 0; y < widthcells; y++)
		{
			DrawModel(worldcells[x][y].floormodel, worldcells[x][y].position, 1, LIGHTGRAY);

			DrawModel(worldcells[x][y].ceilingmodel, { worldcells[x][y].position.x,worldwallheight,worldcells[x][y].position.z }, 1, LIGHTGRAY);

			DrawCubeWires(worldcells[x][y].position, worldcellside, 0,worldcellside,BLACK);

			for (int z = 0; z < 4; z++)
			{
				if (z == 0&&cells[x][y].walls[0]==true)
				{
					DrawModel(worldcells[x][y].topwallmodel, worldcells[x][y].worldcellwalls[0].startpos, 1, BLACK);
					continue;
				}

				if (z == 1 && cells[x][y].walls[1] == true)
				{
					DrawModel(worldcells[x][y].rightwallmodel, worldcells[x][y].worldcellwalls[1].startpos, 1, BLACK);
					continue;
				}

				if (z == 2 && cells[x][y].walls[2] == true&&x==widthcells-1)
				{
					DrawModel(worldcells[x][y].bottomwallmodel, worldcells[x][y].worldcellwalls[2].startpos, 1, BLACK);
					continue;
				}

				if (z == 3 && cells[x][y].walls[3] == true&&y==0)
				{
					DrawModel(worldcells[x][y].leftwallmodel, worldcells[x][y].worldcellwalls[3].startpos, 1, BLACK);
					continue;
				}
			}
		}
	}
}

void worldPlayerMovement()
{
	worldplayerpos = { playercam.position.x,playerheight/2,playercam.position.z};
}

void drawWorldPlayer()
{
	DrawCube(worldplayerpos, 2, playerheight, 2, BLUE);
}

void checkcurrentworldcell()
{
	currentworldcell[0] = worldplayerpos.z / worldcellside;
	currentworldcell[1] = worldplayerpos.x / worldcellside;
}

int checkcollision()
{
	short int xindex = currentworldcell[0];
	short int yindex = currentworldcell[1];

	if (cells[xindex][yindex].walls[0] == true)
	{
		if (playercam.position.z+worldcellside/2-worldwallthickness- worldwallobjectbuffer < worldcells[xindex][yindex].position.z)
			return 0;
	}
	if (cells[xindex][yindex].walls[1] == true)
	{
		if (playercam.position.x-worldcellside/2+worldwallthickness + worldwallobjectbuffer > worldcells[xindex][yindex].position.x)
			return 1;
	}
	if (cells[xindex][yindex].walls[2] == true)
	{
		if (playercam.position.z -worldcellside/2+worldwallthickness+ worldwallobjectbuffer > worldcells[xindex][yindex].position.z)
			return 2;
	}
	if (cells[xindex][yindex].walls[3] == true)
	{
		if (playercam.position.x +worldcellside/2-worldwallthickness- worldwallobjectbuffer < worldcells[xindex][yindex].position.x)
			return 3;
	}
	
	return -1;
}

void drawEntities()
{
	DrawModelEx(zombie.model, zombie.position, { 0,1,0 }, zombie.rotation, zombie.scale, WHITE);
	DrawModelEx(gunmodel, { worldplayerpos.x, playercam.position.y - 0.5f, worldplayerpos.z + 1 }, { 0,1,0}, 30, { 0.1,0.1,0.1 }, RAYWHITE);

}

void initializeEntities()
{
	zombie.InitiateZombie(225,0,225);
}

void updateenemyanimations()
{
	DrawBoundingBox(zombie.hitbox, BLACK);
	DrawBoundingBox(hitbox, BLACK);
	UpdateModelAnimation(zombie.model, zombie.animations[zombie.currentAnimation], zombie.animcurrentframe);
	zombie.animcurrentframe = (zombie.animcurrentframe + 1) % zombie.animframecount[zombie.currentAnimation];
}

void updateplayerhitbox()
{
	hitbox = { {worldplayerpos.x - 3,0,worldplayerpos.z - 3},{worldplayerpos.x + 3,playerheight + 2,worldplayerpos.z + 3} };
}

void updatezombiehitbox()
{
	zombie.updateHitbox();
}

void initializeModels(Shader shader)
{

	for(int x=0;x<heightcells;x++)
		for (int y = 0; y < widthcells; y++)
		{
			worldcells[x][y].topwallmesh = GenMeshCube(worldcellside, worldwallheight, worldwallthickness);
			worldcells[x][y].rightwallmesh = GenMeshCube(worldwallthickness, worldwallheight, worldcellside);
			worldcells[x][y].bottomwallmesh = GenMeshCube(worldcellside, worldwallheight, worldwallthickness);
			worldcells[x][y].leftwallmesh = GenMeshCube(worldwallthickness, worldwallheight, worldcellside);
			worldcells[x][y].floormesh = GenMeshPlane(worldcellside, worldcellside, 1, 1);
			worldcells[x][y].ceilingmesh = GenMeshCube(worldcellside, 10, worldcellside);


			worldcells[x][y].topwallmodel = LoadModelFromMesh(worldcells[x][y].topwallmesh);
			worldcells[x][y].leftwallmodel = LoadModelFromMesh(worldcells[x][y].leftwallmesh);
			worldcells[x][y].rightwallmodel = LoadModelFromMesh(worldcells[x][y].rightwallmesh);
			worldcells[x][y].bottomwallmodel = LoadModelFromMesh(worldcells[x][y].bottomwallmesh);
			worldcells[x][y].floormodel = LoadModelFromMesh(worldcells[x][y].floormesh);
			worldcells[x][y].ceilingmodel = LoadModelFromMesh(worldcells[x][y].ceilingmesh);

			worldcells[x][y].topwallmodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;
			worldcells[x][y].rightwallmodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;
			worldcells[x][y].bottomwallmodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;
			worldcells[x][y].leftwallmodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;
			worldcells[x][y].floormodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;
			worldcells[x][y].ceilingmodel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floortexture;

			worldcells[x][y].topwallmodel.materials[0].shader = shader;
			worldcells[x][y].rightwallmodel.materials[0].shader = shader;
			worldcells[x][y].leftwallmodel.materials[0].shader = shader;
			worldcells[x][y].bottomwallmodel.materials[0].shader = shader;
			worldcells[x][y].floormodel.materials[0].shader = shader;
			worldcells[x][y].ceilingmodel.materials[0].shader = shader;
		}
}

void initializelightingshader(Shader* shader)
{
	shader->locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(*shader, "viewPos");
	int ambientLoc = GetShaderLocation(*shader, "ambient");
	const float ambientval[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	SetShaderValue(*shader, ambientLoc, ambientval, SHADER_UNIFORM_VEC4);
}

void renderworld(Shader shader)
{

	if (worldinit == false)
	{
		floortexture = LoadTextureFromImage(LoadImage("../Textures/gravel_concrete_03_diff_1k.png"));
		DisableCursor();
		initializeWorldCells();
		initializeEntities();
		initializeModels(shader);
		worldplayerpos = { 50,playerheight/2,50 };

		//zombie.SetPath(currentworldcell);

		gunmodel = LoadModel("../Models/41-pistol-beretta/Pistol Beretta/Pistol_Model.glb");

		worldinit = true;
		
	}

	else
	{
		BeginMode3D(playercam);
		ClearBackground(DARKGRAY);
		
		DrawSphere({ worldplayerpos.x,playerheight,worldplayerpos.z }, 5, BLUE);

		updateplayerhitbox();
		updatezombiehitbox();

		const float campos[3] = { playercam.position.x,playercam.position.y, playercam.position.z };
		SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], campos, SHADER_UNIFORM_VEC3);

		drawWorldCells(shader);
		drawEntities();
		drawWorldPlayer();

		updateenemyanimations();
		updateCam(checkcollision());
		worldPlayerMovement();
		//zombie.Move();

		checkcurrentworldcell();

		EndMode3D();
		DrawCircle(screenwidth / 2, screenheight / 2, 3, WHITE);
	}
}


//RUN GAME
int main()
{
	InitWindow(screenwidth, screenheight, "Raycasting");
	SetTargetFPS(144);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	srand(time(0));

	initPlayerPos(30, 60);
	initCells();
	initMaze();
	initCamera();

	Shader shader = LoadShader(TextFormat("C:/Users/Lenovo/source/repos/Raycasting/Shaders/WallVertexShader.vs", 330), TextFormat("C:/Users/Lenovo/source/repos/Raycasting/Shaders/WallFragmentShader.fs", 330));
	initializelightingshader(&shader);

	Light torch = CreateLight(LIGHT_POINT, {75,10,75}, {100,10,75}, WHITE, shader);


	while(!WindowShouldClose())
	{
		mousepos = GetMousePosition();

		BeginDrawing();


		if (minimapstage == true)
		{
			minimap();
		}

		else 
		{
			renderworld(shader);
		}

		EndDrawing();
	}
}