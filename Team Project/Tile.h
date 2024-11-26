#ifndef TILE_H
#define TILE_H

#include "fssimplewindow.h"
#include "itemManage.h"
#include "Enemy.h"
#include "Hero.h"
#include "yspng.h"

// Loading items for GetItem function
Item gun("Gun", 1, "gun.png", "gun.wav");
Item healthPotion("Health Potion", 2, "hp.png", "hp.wav");
Item sword("Sword", 3, "sword.png", "sword.wav");
Hero hero();
Enemy rabbit();

// Constants for tile size
const int TILE_SIZE = 40;

// Enumeration for different tile types
enum TileType
{
    EMPTY,  // 0: Empty tile
    WALL,   // 1: Wall
    PLAYER, // 2: Player
    ENEMY,  // 3: Enemy
    GUN,    // 4: Gun
    HP,     // 5: Health Potion
    SWORD,  // 6: Sword
    DOOR    // 7: Door
};

// Tile class represents a single tile on the map
class Tile
{
private:
    int x, y;         // Top-left corner position of the tile
    TileType type;    // Type of the tile (e.g., WALL, PLAYER)

public:
    // Constructor
    Tile(int x = 0, int y = 0, TileType type = EMPTY);; //std::optional<Item> item = std::nullopt);
    // Constructor with Item
    /*Tile(int x = 0, int y = 0, TileType type = EMPTY, Item item);*/

    // Setter and getter for tile type
    void SetType(TileType newType);
    TileType GetType() const;
    Item GetItem(void);

    // Render the tile
    void Draw() const;
};

#endif
