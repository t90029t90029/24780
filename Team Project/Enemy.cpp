// Enemy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Enemy.h"


Enemy::Enemy()
{
    pixelX = 40;
    pixelY = 40;
    direction = 0;
    HP = 100;
    attackDamage = 1;
    following = false;
}


void Enemy::IsFollowing(int playertileX, int playertileY)
{
    if (following == false)
    {
        if ((abs(playertileX - tileX) == 1 || abs(playertileX - tileX) == 0) && ((abs(playertileY - tileY) == 1 || abs(playertileY - tileY) == 0)))
        {
            printf("dsljfs");
            following = true;
        }

    }
}

void Enemy::Draw(unsigned char front[], unsigned char right[], unsigned char left[], unsigned char back[]) const
{
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


void Enemy::FollowHero(int playertileX, int playertileY, int playergameTime,Enemy rabbit[])
{
    if (following == true)
    {
        int currTileX = tileX;
        int currTileY = tileY;
        printf("here");
        if (tileX - playertileX > 0)
        {
            if (playergameTime % speed == 0)
            {
                tileX -= 1;
                direction = 1;

                if (playertileX == tileX)
                {
                    tileX += 1;
                }
            }

        }
        else if (tileX - playertileX < 0)
        {
            if (playergameTime % speed == 0)
            {
                tileX += 1;
                direction = 2;
                if (playertileX == tileX)
                {
                    tileX -= 1;
                }
            }

        }

        if (tileY - playertileY > 0)
        {
            if (playergameTime % speed == 0)
            {
                tileY -= 1;
                direction = 3;
                if (playertileY == tileY)
                {
                    tileY += 1;
                }
            }

        }
        else if (tileY - playertileY < 0)
        {
            if (playergameTime % speed == 0)
            {
                tileY += 1;
                direction = 0;
                if (playertileY == tileY)
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
