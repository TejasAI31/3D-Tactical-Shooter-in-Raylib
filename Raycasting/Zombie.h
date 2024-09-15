#pragma once
#include "Settings.h"
#include "WorldResources.h"
#include <vector>

#define speed 50

using namespace std;

/// <summary>
/// 0->ATTACK
/// 1->DEATH
/// 2->IDLE
/// 3->WALKING
/// </summary>

class Zombie
{
public:

	double health = 10000;

	short int currentAnimation = 1;
	int animframecount[4] = { 273 ,198,717,88};
	int animcount = 0;
	int animindex = 0;
	int animcurrentframe = 0;

	int currentzombiecell[2];

	int step[2][2];
	int pathcounter = 1;

	float rotation=0;

	Model model;
	ModelAnimation *animations;
	BoundingBox hitbox;
	Vector3 scale = { 0.3,0.3,0.3};
	Vector3 position;

	vector<vector<int>> path;

	bool startmoving = false;

	void updateHitbox()
	{
		hitbox = { {position.x - 15,0,position.z - 10},{position.x + 15,55,position.z + 20} };
	}

	void setCurrentCell()
	{
		currentzombiecell[0] = position.z / worldcellside;
		currentzombiecell[1] = position.x / worldcellside;
	}

	vector<int> checkZombieNeighbor()
	{
		vector<vector<int>> neighbors;

		if (cells[currentzombiecell[0]][currentzombiecell[1]].walls[0] == false&& cells[currentzombiecell[0]-1][currentzombiecell[1]].initexplored==false&&currentzombiecell[0]!=0)
		{
			neighbors.push_back({ currentzombiecell[0] - 1,currentzombiecell[1] });
		}
		if (cells[currentzombiecell[0]][currentzombiecell[1]].walls[1] == false && cells[currentzombiecell[0]][currentzombiecell[1]+1].initexplored == false && currentzombiecell[1] != widthcells-1)
		{
			neighbors.push_back({ currentzombiecell[0],currentzombiecell[1]+1 });
		}
		if (cells[currentzombiecell[0]][currentzombiecell[1]].walls[2] == false && cells[currentzombiecell[0]+1][currentzombiecell[1]].initexplored == false && currentzombiecell[0] != heightcells-1)
		{
			neighbors.push_back({ currentzombiecell[0] + 1,currentzombiecell[1] });
		}
		if (cells[currentzombiecell[0]][currentzombiecell[1]].walls[3] == false && cells[currentzombiecell[0]][currentzombiecell[1]-1].initexplored == false && currentzombiecell[1] != 0)
		{
			neighbors.push_back({ currentzombiecell[0],currentzombiecell[1]-1 });
		}

		if (neighbors.size() == 0)
		{
			return { -1,-1 };
		}

		int random;
		do {
			random = rand() % neighbors.size();
		} while (random >= neighbors.size());
		vector<int> neighbor = { neighbors[random][0],neighbors[random][1]};
		return neighbor;
	}

	void InitiateZombie(float a,float b,float c)
	{
		model = LoadModel("../Models/Zombie.glb");
		animations = LoadModelAnimations("../Models/Zombie.glb", &animcount);
		position = { a,b,c };
		setCurrentCell();
		updateHitbox();
	}

	void SetPath(int playercell[2])
	{
		//clear cells explored
		for (int x = 0; x < heightcells; x++)
		{
			for (int y = 0; y < widthcells; y++)
			{
				cells[x][y].initexplored = false;
			}
		}

		bool pathfound = false;
		
		while (pathfound == false)
		{
			vector<int> neighbor = checkZombieNeighbor();

			if(neighbor[0]!=-1&&neighbor[1]!=-1)
			{
				cells[currentzombiecell[0]][currentzombiecell[1]].initexplored = true;

				path.push_back({ currentzombiecell[0],currentzombiecell[1] });

				currentzombiecell[0] = neighbor[0];
				currentzombiecell[1] = neighbor[1];

				if (currentzombiecell[0] == playercell[0] && currentzombiecell[1] == playercell[1])
				{
					pathfound = true;
					path.push_back({ currentzombiecell[0],currentzombiecell[1] });
				}
			}
			
			else
			{
				path.pop_back();
				currentzombiecell[0] = path[path.size() - 1][0];
				currentzombiecell[1] = path[path.size() - 1][1];
			}

		}

		step[0][0] = path[0][0] * worldcellside + worldcellside / 2;
		step[0][1] = path[0][1] * worldcellside + worldcellside / 2;
		step[1][0] = path[1][0] * worldcellside + worldcellside / 2;
		step[1][1] = path[1][1] * worldcellside + worldcellside / 2;

	}   

	void Move()
	{

		float frametime = GetFrameTime();

		setCurrentCell();
		if (abs(position.z - step[1][0])<speed*frametime*20&& abs(position.x - step[1][1]) < speed*frametime*20&&pathcounter!=path.size()-1)
		{
				pathcounter++;
				step[0][0] = step[1][0];
				step[0][1] = step[1][1];
				step[1][0] = path[pathcounter][0] * worldcellside + worldcellside / 2;
				step[1][1] = path[pathcounter][1] * worldcellside + worldcellside / 2;
		}

		if (step[1][1]==step[0][1]&&step[1][0] > step[0][0])
		{
			position.z += speed * frametime;
			if (rotation != 0)
				rotation = 0;
		}
		else if (step[1][1] == step[0][1] && step[1][0] < step[0][0])
		{
			position.z -= speed * frametime;
			if (rotation != 180)
				rotation = 180;
		}

		else if (step[1][0] == step[0][0] && step[1][1] > step[0][1])
		{
			position.x += speed * frametime;
			if (rotation != 90)
				rotation = 90;
		}
		else
		{
			position.x -= speed *frametime;
			if (rotation != 270)
				rotation = 270;
		}
		
	}
};