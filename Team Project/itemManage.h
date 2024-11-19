#include <string>
#include <iostream>
#include <vector>
#include "yssimplesound.h"
#include "yspng.h"
#include "fssimplewindow.h"

// Enumeration for item states
enum ItemState { ONMAP, ONPLAYER };

// Class representing a moving circle (player)
class MovingCircle {
public:
    int x, y;       // Position of the circle
    int radius;     // Radius of the circle

    MovingCircle(int startX, int startY, int rad);

    void Move(int dx, int dy);
    void Draw() const;
};

// Class representing an item in the game
class Item {
public:
    std::string name;          // Name of the item
    int x, y;                  // Position of the item
    ItemState state;           // Current state of the item
    YsRawPngDecoder png;       // Image decoder for the item
    YsSoundPlayer::SoundData sound; // Sound data for the item
    bool imageLoaded;          // Flag indicating if the image is loaded
    bool soundLoaded;          // Flag indicating if the sound is loaded

    Item(const std::string& name, int x, int y, const char* imageFile, const char* soundFile);

    bool LoadImage(const char* filename);
    bool LoadSound(const char* filename);
    void Draw(const MovingCircle& player);
    void PlaySound(YsSoundPlayer& player);
    void TriggerEffect(YsSoundPlayer& player);
    void Pickup();
    bool IsCollidingWith(const MovingCircle& player) const;
};


