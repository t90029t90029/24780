#include "Tile.h"
#include "itemManage.h"

// Tile Implementation
Tile::Tile(int x, int y, TileType type) : x(x), y(y), type(type) {}
//Tile::Tile(int x, int y, TileType type, Item item) : x(x), y(y), type(type), item(item) {}

void Tile::SetType(TileType newType)
{
    type = newType;
}

TileType Tile::GetType() const
{
    return type;
}

Item Tile::GetItem(void)
{
    switch(type)
    {
    case GUN:
        return gun;
    case HP:
        return healthPotion;
    case SWORD:
        return sword;
    default:
        return;
    }
}

void Tile::Draw() const
{
    switch (type)
    {
        // TODO: Some of the cases may be removed and replaced as a png file in the future
        case WALL:
        {
            // Don't remove braces here - needed for png decode execution in switch/case statement
            YsRawPngDecoder png;
            png.Decode("WALL.png");
            glRasterPos2i(x, y);
            glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
            break;
        }
        case PLAYER:
            hero.Draw();
            break;
        case ENEMY:
            rabbit.Draw();
            break;
        case GUN:
            gun.Draw(x, y);
            break;
        case HP:
            healthPotion.Draw(x, y);
            break;
        case SWORD:
            sword.Draw(x, y);
            break;
        case DOOR:
        {
            // Don't remove the braces here - needed for png decode execution in switch/case statement
            YsRawPngDecoder png;
            png.Decode("DOOR.png");
            png.Flip();
            glRasterPos2i(x, y);
            glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
            /*glColor3ub(255, 215, 0);*/ // Gold for door
            break;
        }
        default:
            glColor3ub(255, 255, 255); // White for empty tiles
            glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x + TILE_SIZE, y);
            glVertex2i(x + TILE_SIZE, y + TILE_SIZE);
            glVertex2i(x, y + TILE_SIZE);
            glEnd();

            glColor3ub(200, 200, 200);
            glBegin(GL_LINE_LOOP); // Draw border
            glVertex2i(x + 1, y + 1);
            glVertex2i(x + TILE_SIZE - 1, y + 1);
            glVertex2i(x + TILE_SIZE - 1, y + TILE_SIZE - 1);
            glVertex2i(x + 1, y + TILE_SIZE - 1);
            glEnd();
            break;
    }
}
