#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <math.h>

// Item class: Represents an item in the game
class Item {
public:
    // Enum for item states
    enum ItemState { ONMAP, ONPLAYER };

    std::string name;            // Item's name
    ItemState state;             // Current state of the item
    int effectCode;              // Numeric code representing the item's effect
    YsRawPngDecoder png;         // Image data
    YsSoundPlayer::SoundData sound; // Sound data
    bool imageLoaded = false;    // Flag for image load success
    bool soundLoaded = false;    // Flag for sound load success

    // Constructor
    Item(const std::string& name, int effectCode, const char* imageFile, const char* soundFile);

    // Loads an image for the item
    bool LoadImage(const char* filename);

    // Loads a sound for the item
    bool LoadSound(const char* filename);

    // Draws the item at a specified position
    void Draw(int drawX, int drawY);
};

// Function to trigger the effect and return the corresponding effect code
int TriggerEffect(Item* heroHoldItem, YsSoundPlayer& player);

#endif // ITEM_MANAGER_H
