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
        glColor3ub(0, 0, 0); // Black for walls
        break;
    case TILE_DOOR:
        glColor3ub(255, 215, 0); // Gold for doors
        break;
    case TILE_EMPTY:
    case TILE_HERO:
    case TILE_ENEMY:
    case TILE_ITEM:
    default:
        glColor3ub(255, 255, 255); // White for empty tiles
        break;
    }

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + 40, y);
    glVertex2i(x + 40, y + 40);
    glVertex2i(x, y + 40);
    glEnd();

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
}
