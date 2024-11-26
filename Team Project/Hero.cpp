// Hero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Hero.h"
#include "Enemy.h"
#include "Map.h"
#include "itemManage.h"


Hero::Hero()
{
    pixelX = 40;
    pixelY = 40;
    direction = 0;
    HP = 100;
    //tileX = 0;
    //tileY = 0;
    range = 0;
    damage = 0;
    health = 0;
    FsChangeToProgramDir();
    
    YsRawPngDecoder heroFrontPNG;
    YsRawPngDecoder heroBackPNG;
    YsRawPngDecoder heroLeftPNG;
    YsRawPngDecoder heroRightPNG;
    YsRawPngDecoder rabbitFrontPNG;
    YsRawPngDecoder rabbitBackPNG;
    YsRawPngDecoder rabbitLeftPNG;
    YsRawPngDecoder rabbitRightPNG;

    if (YSOK == heroFrontPNG.Decode("heroFront.png"))
    {
        printf("Wid %d Hei %d\n", heroFrontPNG.wid, heroFrontPNG.hei);
    }
    else
    {
        printf("Failed to open hero front image.\n");
    }
    heroFrontPNG.Flip();



    if (YSOK == heroBackPNG.Decode("heroBack.png"))
    {
        printf("Wid %d Hei %d\n", heroBackPNG.wid, heroBackPNG.hei);
    }
    else
    {
        printf("Failed to open hero back image.\n");
    }
    heroBackPNG.Flip();


    if (YSOK == heroLeftPNG.Decode("heroLeft.png"))
    {
        printf("Wid %d Hei %d\n", heroLeftPNG.wid, heroLeftPNG.hei);
    }
    else
    {
        printf("Failed to open hero left image.\n");
    }
    heroLeftPNG.Flip();

    if (YSOK == heroRightPNG.Decode("heroRight.png"))
    {
        printf("Wid %d Hei %d\n", heroRightPNG.wid, heroRightPNG.hei);
    }
    else
    {
        printf("Failed to open hero right image.\n");
    }
    heroRightPNG.Flip();

    for (int i = 0; i < 6400; i++)
    {
        front[i] = heroFrontPNG.rgba[i];
        right[i] = heroRightPNG.rgba[i];
        left[i] = heroLeftPNG.rgba[i];
        back[i] = heroBackPNG.rgba[i];
    }

}


bool Hero::IsDead()
{
    if (HP <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Hero::PickItemIfAny(Map map)
{
    return;
    Item curr = map.GetItem(tileX, tileY);
    range = curr.getRange();
    damage = curr.getDamage();
    health = curr.getHeal();

}




int Hero::GetPlayerRow()
{
    return tileX;
}

int Hero::GetPlayerCol()
{
    return tileY;
}

void Hero::SpawnPlayer(int x, int y)
{
    tileX = x;
    tileY = y;
}

void Hero::Attack(Enemy rabbit[])
{
    if (health > 0)
    {
        if (HP <= 100 - health)
        {
            HP += health;
        }
        return;
    }
    if (direction == 0)
    {
        for (int i = 0; i < rabbits; i++)
        {
            if ((rabbit[i].GetEnemyRow() == tileX) && (rabbit[i].GetEnemyCol() >= tileY - range) && (rabbit[i].GetEnemyCol() < tileY))
            {
                rabbit[i].HP -= damage;
            }
        }
    }
    else if (direction == 1)
    {
        for (int i = 0; i < rabbits; i++)
        {
            if ((rabbit[i].GetEnemyRow() <= tileX + range) && (rabbit[i].GetEnemyRow() > tileX) && (rabbit[i].GetEnemyCol() == tileY))
            {
                rabbit[i].HP -= damage;
            }
        }
    }
    else if (direction == 2)
    {
        for (int i = 0; i < rabbits; i++)
        {
            if ((rabbit[i].GetEnemyRow() >= tileX - range) && (rabbit[i].GetEnemyRow() < tileX) && (rabbit[i].GetEnemyCol() == tileY))
            {
                rabbit[i].HP -= damage;
            }
        }
    }
    else if (direction == 3)
    {
        for (int i = 0; i < rabbits; i++)
        {
            if ((rabbit[i].GetEnemyRow() == tileX) && (rabbit[i].GetEnemyCol() <= tileY + range) && (rabbit[i].GetEnemyCol() > tileY))
            {
                rabbit[i].HP -= damage;
            }
        }
    }
}

void Hero::Draw() const
{
    //gameTime += 1;
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

void Hero::Move(int key, Enemy rabbit[], Map map)
{
    if (key == FSKEY_RIGHT)
    {
        if (map.IsAccessible(tileX + 1, tileY) == false)
        {
            return;
        }
        direction = 1;
        
        if (tileX != 19)
        {
            int currTile = tileX;
            int count = 0;
            for (int i = 0; i < 10; i++)
            {
                if (currTile + 1 == rabbit[i].GetEnemyRow() && tileY == rabbit[i].GetEnemyCol())
                {
                    count += 1;
                }
            }

            if (count == 0)
            {
                tileX += 1;
            }
        }
        
    }
    else if (key == FSKEY_LEFT)
    {
        if (map.IsAccessible(tileX - 1, tileY) == false)
        {
            return;
        }
        direction = 2;
        if (tileX != 0)
        {
            int count = 0;
            int currTile = tileX;
            for (int i = 0; i < 10; i++)
            {
                if (currTile - 1 == rabbit[i].GetEnemyRow() && tileY == rabbit[i].GetEnemyCol())
                {
                    count += 1;
                }
            }
            if (count == 0)
            {
                tileX -= 1;
            }
        }

    }
    else if (key == FSKEY_UP)
    {
        if (map.IsAccessible(tileX, tileY - 1) == false)
        {
            return;
        }
        direction = 3;
        if (tileY != 0)
        {
            int count = 0;
            int currTile = tileY;
            for (int i = 0; i < 10; i++)
            {
                if (tileX == rabbit[i].GetEnemyRow() && currTile - 1 == rabbit[i].GetEnemyCol())
                {
                    count += 1;

                }
            }
            if (count == 0)
            {
                tileY -= 1;
            }

        }
    }
    else if (key == FSKEY_DOWN)
    {
        if (map.IsAccessible(tileX, tileY + 1) == false)
        {
            return;
        }
        direction = 0;
        if (tileY != 19)
        {
            int count = 0;
            int currTile = tileY;
            for (int i = 0; i < 10; i++)
            {
                if (tileX == rabbit[i].GetEnemyRow() && currTile + 1 == rabbit[i].GetEnemyCol())
                {
                    count += 1;
                    tileY -= 1;
                }
            }
            if (count == 0)
            {
                tileY += 1;
            }
        }
    }

    for (int i = 0; i < rabbits; i++)
    {
        if ((rabbit[i].GetEnemyRow() + 1 == tileX || rabbit[i].GetEnemyRow() - 1 == tileX) && (rabbit[i].GetEnemyCol() - 1 == tileY || rabbit[i].GetEnemyCol() + 1 == tileY))
        {
            HP -= 5;
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
