#include <stdio.h>
#include <vector>
#include <array>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
using namespace std;

//class Door;
//class Tile;
//
//class Map
//{
//private:
//	// At GameBegin, animate spawn
//	int playerSpawn[2] = { 0, 0 };
//
//	bool enemyState[]; // Alive or not, start with True
//
//	bool itemState[]; // Collected or not, start with True
//	Room rooms[2];
//	Map(Player& player, Item& items[], Enemy& enemies[], Room& rms[]);
//	void RemoveItem(Item& item);
//
//};
//
//Map::Map(Player& player, Item& items[], Enemy& enemies[], Room& rms[])
//{
//	room[] = rms[];
//	// Decide which enemies go where here
//		// Should enemies respawn once a room has been left? If not, put enemySpawn as responsibility of Maps
//	// Decide which items go where here
//		// Once items are collected, they are gone for good
//}
//
//void Map::RemoveItem(int n)
//{
//	itemState[n] = false;
//}
//
//void Map::RemoveEnemy(int n)
//{
//	enemyState[n] = false;
//}


class Wall
{
private:
	int x;
	int y;
	int size = 40;

public:
	Wall() : x(0), y(0) {} //Default constructor
	Wall(int x, int y);
	void Draw(void);
};

Wall::Wall(int x, int y)
{
	this->x = size * x;
	this->y = size * y;
}

void Wall::Draw(void)
{
	glColor3i(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + size, y);
	glVertex2i(x + size, y + size);
	glVertex2i(x, y + size);
	glEnd();

	glColor3i(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(x + 1, y + 1);
	glVertex2i(x + size - 1, y + 1);
	glVertex2i(x + size - 1, y + size - 1);
	glVertex2i(x + 1, y + size - 1);
	glEnd();
}

class Room
{
private:
	int size = 800;

	//int enemyCount;
	//vector<array<int, 2>> enemyPos;
	//Enemy enemies[enemyCount];

	//int itemCount;
	//int itemSpawn[itemCount][2];
	
	bool wallPos[20][20] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	Wall walls[20][20];

	//Door doors[2][2];

public:
	Room(); /*int wallCount, int enemyCount, int itemCount*/
	void Draw(void);
};

Room::Room()
{
	/*this->enemyCount = enemyCount;
	this->itemCount = itemCount;
	this->wallCount = wallCount;*/
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (wallPos[i][j] == 1)
			{
				walls[i][j] = Wall(j, i);
			}
		}
	}
}

void Room::Draw(void)
{

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			walls[i][j].Draw();
		}
	}
}


int main() {
	Room room;

	FsOpenWindow(0, 0, 800, 800, 1);
	for (;;)
	{
		FsPollDevice();
		auto key = FsInkey();

		if (key == FSKEY_ESC)
		{
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		room.Draw();

		FsSwapBuffers();
		FsSleep(25);
	}

	

	return 0;
}