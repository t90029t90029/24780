#ifndef ITEM_H
#define ITEM_H

#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include <string>

class Item
{
private:
    std::string name;                // Name of the item
    int attackRange;                 // Attack range provided by the item
    int damage;                      // Damage provided by the item
    int heal;                        // Healing provided by the item
    YsRawPngDecoder png;             // Image data
    YsSoundPlayer::SoundData sound;  // Sound data
    int row, col;                    // Position of the item on the map (row and column)

public:
    Item(const std::string &name = "Unknown", int attackRange = 0, int damage = 0, int heal = 0,
         const char *imageFile = "default.png", const char *soundFile = "default.wav");

    // Getters
    std::string GetName() const;
    int GetRange() const;
    int GetHeal() const;
    int GetDamage() const;
    YsSoundPlayer::SoundData &GetSound();

    int GetRow() const;
    int GetCol() const;
    void SetPosition(int row, int col);

    // Resource loading
    bool LoadImage(const char *filename);
    bool LoadSound(const char *filename);

    // Rendering
    void Draw() const;
};

#endif
