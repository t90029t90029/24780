#ifndef TILE_H
#define TILE_H

#include "fssimplewindow.h"

// Constants for tile size
const int TILE_SIZE = 40;

// Enumeration for different tile types
enum TileType
{
    EMPTY,  // 0: Empty tile
    WALL,   // 1: Wall
    PLAYER, // 2: Player
    ENEMY,  // 3: Enemy
    ITEM,   // 4: Item
    DOOR    // 5: Door
};

// Tile class represents a single tile on the map
class Tile
{
private:
    int x, y;         // Top-left corner position of the tile
    TileType type;    // Type of the tile (e.g., WALL, PLAYER)

public:
    // Constructor
    Tile(int x = 0, int y = 0, TileType type = EMPTY);

    // Setter and getter for tile type
    void SetType(TileType newType);
    TileType GetType() const;

    // Render the tile
    void Draw() const;
};

#endif
