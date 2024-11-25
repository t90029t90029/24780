// Hero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef HERO_H
#define HERO_H



#include <iostream>
#include <stdio.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include "Enemy.h"
#include "Map.h"
#include "ItemManage.h"


class Hero
{
private:
    int tileX;
    int tileY;
public:
    Hero(); //constructor. Sets values for pixelX, pixelY, direction, HP.
    //int tileX; //x-position of tile
    //int tileY; //y-position of tile
    int pixelX; //number of pixels of hero pictures in x direction (40)
    int pixelY; //number of pixels of hero pictures in y direction (40)
    int direction; //number from 0 to 3, keeps track of where enemy is facing (0 = up, 1 = right, 2 = left, 3 = down)
    int gameTime;
    double HP; //health = 100
    int GetPlayerRow();
    int GetPlayerCol();
    bool itemHeld;
    int range;
    int damage;
    int health;
    void PickItemIfAny(); //for testing use an item instant, otherwise there is no argument.
    void Attack(Enemy rabbit[]); //attacks enemy when space key is pressed in gamecontroller
    void SpawnPlayer(int tileX, int tileY);
    void Draw(const unsigned char front[], const unsigned char right[], const unsigned char left[], const unsigned char back[]) const; //draws sprites. the char lists are the .rgba lists for each sprite. is called constantly in main loop
    void Move(int key, Enemy rabbit[],Map map); //moves character based on keyboard input and checks collision with rabbits. 
};

#endif
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
