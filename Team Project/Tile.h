#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "fssimplewindow.h"
#include "Hero.h"
#include "Enemy.h"
#include "Item.h"

enum TileType
{
    TILE_EMPTY = 0,  // Empty tile
    TILE_WALL = 1,   // Wall
    TILE_DOOR = 2,   // Door
    TILE_HERO = 3,   // Hero start position
    TILE_ENEMY = 4,  // Enemy position
    TILE_ITEM = 5    // Item position
};

class Tile
{
private:
    int x, y;           // Position of the tile on the map
    TileType baseType;  // Base type of the tile
    Hero* hero;         // Pointer to the hero on this tile (if any)
    Enemy* enemy;       // Pointer to the enemy on this tile (if any)
    Item* item;         // Pointer to the item on this tile (if any)

public:
    Tile(int x = 0, int y = 0, TileType baseType = TILE_EMPTY);

    void SetBaseType(TileType type);
    TileType GetBaseType() const;

    void SetHero(Hero* hero);
    Hero* GetHero() const;

    void SetEnemy(Enemy* enemy);
    Enemy* GetEnemy() const;

    void SetItem(Item* item);
    Item* GetItem() const;

    bool IsOccupied() const;
    void Draw() const;
};

#endif
