#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tile.h"
#include "Item.h"
#include "Hero.h"
#include "Enemy.h"

const int MAP_ROWS = 20;
const int MAP_COLS = 20;

class Map
{
private:
    Tile tiles[MAP_ROWS][MAP_COLS]; // The grid of tiles
    int doorRow, doorCol;          // Position of the door
    int enemyAttackSwitch;          // To slow down the speed of attacking

public:
    Map();
    ~Map();

    bool LoadFromFile(const std::string &filename);
    void Draw() const;

    bool IsAccessible(int row, int col) const; // Check if the hero can access the tile

    bool IsGameOver(int row, int col) const;

    // Tile-specific operations
    void SetHero(int row, int col, Hero *hero);
    Hero *GetHero(int row, int col) const;

    void SetEnemy(int row, int col, Enemy *enemy);
    Enemy *GetEnemy(int row, int col) const;

    void SetItem(int row, int col, Item *item);
    Item *GetItem(int row, int col) const;

    Tile *GetTile(int row, int col); // Direct access to a tile
    
    bool EnemyActions();    // Make all enemies on the map attack once
};

#endif
