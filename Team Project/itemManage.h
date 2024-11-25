#ifndef ITEM_MANAGE_H
#define ITEM_MANAGE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <math.h>
#include "Tile.h"

// const int TILE_SIZE = 40;

// FOR EXAMPLE USE REFER TO MAIN LOOP IN ITEMMANAGE.CPP
class Item {
public:
    std::string name;            // Item's name
    int attackRange;             // Attack range of the item
    int damage;                  // Attack damage of the item
    int heal;                    // Healing effect of the item
    YsRawPngDecoder png;         // Image data
    YsSoundPlayer::SoundData sound; // Sound data
    bool imageLoaded;    // Flag for image load success
    bool soundLoaded;    // Flag for sound load success

    // Constructor
    Item(const std::string& name, int attackRange, int damage, int heal, const char* imageFile, const char* soundFile); 

    int getRange() const;
    int getHeal() const;
    int getDamage() const;

    bool LoadImage(const char* filename); 
    bool LoadSound(const char* filename);

    void Draw(int tileX, int tileY); //this is to draw the item based on the tile
    void TriggerEffect(YsSoundPlayer& player); //this is to trigger sound effect
};

Item SpawnItem(const std::string& name); //use this to initialize item such as Item gun = SpawnItem("Gun");

#endif // ITEM_MANAGE_H
