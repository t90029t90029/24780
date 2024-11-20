#include "Tile.h"

// Tile Implementation
Tile::Tile(int x, int y, TileType type) : x(x), y(y), type(type) {}

void Tile::SetType(TileType newType)
{
    type = newType;
}

TileType Tile::GetType() const
{
    return type;
}

void Tile::Draw() const
{
    switch (type)
    {
        // TODO: Some of the cases may be removed and replaced as a png file in the future
        case WALL:
            glColor3ub(0, 0, 0); // Black for walls
            break;
        case PLAYER:
            glColor3ub(0, 255, 0); // Green for player
            break;
        case ENEMY:
            glColor3ub(255, 0, 0); // Red for enemy
            break;
        case ITEM:
            glColor3ub(0, 0, 255); // Blue for item
            break;
        case DOOR:
            glColor3ub(255, 215, 0); // Gold for door
            break;
        default:
            glColor3ub(255, 255, 255); // White for empty tiles
            break;
    }

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
}
