// Enemy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Enemy.h"
#include "Map.h"
#include "itemManage.h"
#include <cmath>
#include <math.h>
#include <time.h>


Enemy::Enemy()
{
    pixelX = 40;
    pixelY = 40;
    direction = 0;
    HP = 100;
    attackDamage = 1;
    following = false;
    gameTime = 0;
    speed = rand() % 50 + 50;

    FsChangeToProgramDir();

    YsRawPngDecoder rabbitFrontPNG;
    YsRawPngDecoder rabbitBackPNG;
    YsRawPngDecoder rabbitLeftPNG;
    YsRawPngDecoder rabbitRightPNG;

    if (YSOK == rabbitFrontPNG.Decode("rabbitFront.png"))
    {
        printf("Wid %d Hei %d\n", rabbitFrontPNG.wid, rabbitFrontPNG.hei);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    rabbitFrontPNG.Flip();



    if (YSOK == rabbitBackPNG.Decode("rabbitBack.png"))
    {
        printf("Wid %d Hei %d\n", rabbitBackPNG.wid, rabbitBackPNG.hei);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    rabbitBackPNG.Flip();


    if (YSOK == rabbitLeftPNG.Decode("rabbitLeft.png"))
    {
        printf("Wid %d Hei %d\n", rabbitLeftPNG.wid, rabbitLeftPNG.hei);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    rabbitLeftPNG.Flip();

    if (YSOK == rabbitRightPNG.Decode("rabbitRight.png"))
    {
        printf("Wid %d Hei %d\n", rabbitRightPNG.wid, rabbitRightPNG.hei);
    }
    else
    {
        printf("Failed to open file.\n");
    }
    rabbitRightPNG.Flip();

    for (int i = 0; i < 6400; i++)
    {
        front[i] = rabbitFrontPNG.rgba[i];
        right[i] = rabbitRightPNG.rgba[i];
        left[i] = rabbitLeftPNG.rgba[i];
        back[i] = rabbitBackPNG.rgba[i];
    }


}

int Enemy::GetEnemyRow()
{
    return tileX;
}

int Enemy::GetEnemyCol()
{
    return tileY;
}

void Enemy::SpawnEnemy(int x, int y)
{
    tileX = x;
    tileY = y;
}

void Enemy::CheckFollowing(int playerX, int playerY)
{
    if (following == false)
    {
        if ((abs(playerX - tileX) == 1 || abs(playerX - tileX) == 0) && ((abs(playerY - tileY) == 1 || abs(playerY - tileY) == 0)))
        {
            following = true;
        }

    }
}

void Enemy::Draw() 
{
    gameTime += 1;
    if (HP > 0)
    {
        glRasterPos2i(0 + tileX * 40, pixelY - 1 + tileY * 40);
        if (direction == 0)
        {
            glDrawPixels(pixelX, pixelY, GL_RGBA, GL_UNSIGNED_BYTE, front);
        }
        else if (direction == 1)
        {
            glDrawPixels(pixelX, pixelY, GL_RGBA, GL_UNSIGNED_BYTE, right);
        }
        else if (direction == 2)
        {
            glDrawPixels(pixelX, pixelY, GL_RGBA, GL_UNSIGNED_BYTE, left);
        }
        else if (direction == 3)
        {
            glDrawPixels(pixelX, pixelY, GL_RGBA, GL_UNSIGNED_BYTE, back);
        }
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(tileX * 40, tileY * 40);
        glVertex2f(tileX * 40 + 40 * (HP / 100), tileY * 40);
        glEnd();
    }
}


void Enemy::FollowHeroIfPossible(int playerX, int playerY, Enemy rabbit[],Map map)
{
    if (following == true)
    {
        int currTileX = tileX;
        int currTileY = tileY;
        if (tileX - playerX > 0)
        {
            if (gameTime % speed == 0)
            {
                if (map.IsAccessible(tileX - 1, tileY) == false)
                {
                    return;
                }
                tileX -= 1;
                direction = 1;

                if (playerX == tileX)
                {
                    tileX += 1;
                }
            }

        }
        else if (tileX - playerX < 0)
        {
            if (gameTime % speed == 0)
            {
                if (map.IsAccessible(tileX + 1, tileY) == false)
                {
                    return;
                }
                tileX += 1;
                direction = 2;
                if (playerX == tileX)
                {
                    tileX -= 1;
                }
            }

        }

        if (tileY - playerY > 0)
        {
            if (gameTime % speed == 0)
            {
                if (map.IsAccessible(tileX, tileY - 1) == false)
                {
                    return;
                }
                tileY -= 1;
                direction = 3;
                if (playerY == tileY)
                {
                    tileY += 1;
                }
            }

        }
        else if (tileY - playerY < 0)
        {
            if (gameTime % speed == 0)
            {
                if (map.IsAccessible(tileX, tileY + 1) == false)
                {
                    return;
                }
                tileY += 1;
                direction = 0;
                if (playerY == tileY)
                {
                    tileY -= 1;
                }
            }

        }
        for (int i = 0; i < rabbits; i++)
        {
            if (i == rabbitIdentity)
            {
                continue;
            }
            if (tileX == rabbit[i].tileX && tileY == rabbit[i].tileY)
            {
                tileX = currTileX;
                tileY = currTileY;
                break;
            }
        }

    }
    
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
