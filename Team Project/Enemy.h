// Enemy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <stdio.h>
#include "yspng.h"
#include "fssimplewindow.h"
#include <cmath>
#include "Map.h"

#define rabbits 10 //defines number of enemies. I've put 10 as an example but this can change. 

class Enemy {
public:
    Enemy(); //constructor. Sets values for pixelX, pixelY, direction, HP, attackDamage, and following=false.
    int tileX; //x-position of tile
    int tileY; //y-position of tile
    int pixelX; //number of pixels of enemy pictures in x direction (40)
    int pixelY; //number of pixels of enemy pictures in x direction (40)
    int direction; //number from 0 to 3, keeps track of where enemy is facing (0 = up, 1 = right, 2 = left, 3 = down)
    int rabbitIdentity; //keeps track of index of rabbit when enemy class is declared. Ex: Enemy rabbit[10], i could be 0 to 9. needs to be set when enemy is declared
    double HP; //health = 100
    double attackDamage; //attack damage done by enemy
    int speed; //speed (value from 50 to 100)
    bool following; //set to false in constructor. When following criteria is met, following = true
    int gameTime;
    void SpawnEnemy(int x, int y);
    void Draw(unsigned char front[], unsigned char right[], unsigned char left[], unsigned char back[]) const; //draws sprites. the char lists are the .rgba lists for each sprite. is called constantly in main loop for each rabbit instance
    void IsFollowing(int playertileX, int playertileY);  //Changes following to true if character is near the enemy. playertilex and playertiley is tileX and tileY of hero instance. is called constantly in main loop for each rabbit instance
    void FollowHero(int playertileX, int playertileY, Enemy rabbit[], Map map); //follows character if following = true. playergameTime is from hero instance. is called constantly in main loop for each rabbit instance. 

    //Ex: 
    /*
     Enemy rabbit[10]
     while (true)

        for (int i = 0; i < rabbits; i++)
        {
            rabbit[i].Draw(rabbitFrontPNG.rgba, rabbitRightPNG.rgba, rabbitLeftPNG.rgba, rabbitBackPNG.rgba);
            rabbit[i].IsFollowing(player.tileX, player.tileY);
            rabbit[i].FollowHero(player.tileX, player.tileY, player.gameTime, rabbit);
        }
    */
};

#endif // ENEMY_H

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

