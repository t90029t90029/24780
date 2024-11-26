#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include "Tile.h"
#include "itemManage.h"
#include "Hero.h"
#include "Enemy.h"

// Constants for map dimensions
const int MAP_ROWS = 20;
const int MAP_COLS = 20;

// Map class manages the overall grid of tiles
class Map
{
private:
    Tile tiles[MAP_ROWS][MAP_COLS]; // 2D array of tiles
    // TODO: (This will be removed when integrating with player class)
    int playerRow, playerCol;       // Player's position
    int doorRow, doorCol;           // Door's position (the target of the map)

public:
    // Constructor
    Map();

    // Load map layout from a text file
    bool LoadFromFile(const std::string &filename);

    // Render the entire map
    void Draw() const;

    // TODO: Update player's position (this will be the duty of player class and will be removed)
    void UpdatePlayerPosition(int newRow, int newCol);

    // Check if the tile is accessible or not
    bool IsAccessible(int row, int col) const;

    // Check if the player has reached the door
    bool IsGameOver() const;

    // TODO: (This will be removed when integrating with player class)
    // Get the player's current position
    int GetPlayerRow() const;
    int GetPlayerCol() const;

    // Spawn the Player at Tile (x, y)
    void SpawnPlayer(int x, int y);

    // Return the Item at Tile (x, y)
    Item GetItem(int x, int y);
};

#endif
