#include "Tile.h"

Tile::Tile(int x, int y, TileType baseType)
    : x(x), y(y), baseType(baseType), hero(nullptr), enemy(nullptr), item(nullptr) {}

void Tile::SetBaseType(TileType type)
{
    baseType = type;
}

TileType Tile::GetBaseType() const
{
    return baseType;
}

void Tile::SetHero(Hero* heroPtr)
{
    hero = heroPtr;
}

Hero* Tile::GetHero() const
{
    return hero;
}

void Tile::SetEnemy(Enemy* enemyPtr)
{
    enemy = enemyPtr;
}

Enemy* Tile::GetEnemy() const
{
    return enemy;
}

void Tile::SetItem(Item* itemPtr)
{
    item = itemPtr;
}

Item* Tile::GetItem() const
{
    return item;
}

bool Tile::IsOccupied() const
{
    return hero != nullptr || enemy != nullptr || item != nullptr;
}

void Tile::Draw() const
{
    // Draw base tile
    switch (baseType)
    {
    case TILE_WALL:
    {
        YsRawPngDecoder png;
        if (YSOK == png.Decode("WALL.png"))
        {
            png.Flip();
        }
        

        // This is to band-aid fix a rendering bug where these values are shifted
        int posx = x; int posy = y;
        if (x >= 440)
        {
            posx -= 1;
        }
        if (y > 360)
        {
            posy -= 1;
        }

        glRasterPos2i(posx, posy + 40 - 1);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        goto LOOPOUT;
    }
        break;
    case TILE_DOOR:
        //glColor3ub(255, 215, 0); // Gold for doors
        {
            YsRawPngDecoder png;
            if (YSOK == png.Decode("DOOR.png"))
            {
                png.Flip();
            }
            if (x >= 440)
            glRasterPos2i(x - 1, y + 40 - 1);
            glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
            goto LOOPOUT;
        }
        break;
    case TILE_EMPTY:
    case TILE_HERO:
    case TILE_ENEMY:
    case TILE_ITEM:
    default:
        glColor3ub(255, 255, 255); // White for empty tiles
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + 40, y);
        glVertex2i(x + 40, y + 40);
        glVertex2i(x, y + 40);
        glEnd();
        break;
    }

    //glBegin(GL_QUADS);
    //glVertex2i(x, y);
    //glVertex2i(x + 40, y);
    //glVertex2i(x + 40, y + 40);
    //glVertex2i(x, y + 40);
    //glEnd();

    // Draw entities on top
    if (item)
    {
        item->Draw();
    }
    if (enemy)
    {
        enemy->Draw();
    }
    if (hero)
    {
        hero->Draw();
    }   
LOOPOUT:
    glEnd();
}

