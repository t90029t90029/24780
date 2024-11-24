#ifndef ITEM_MANAGE_H
#define ITEM_MANAGE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <math.h>

#endif // ITEM_MANAGE_H


class Item {
public:
    enum ItemState { ONMAP, ONPLAYER }; // States for an item

    std::string name;            // Item's name
    ItemState state;             // Current state of the item
    int effectCode;              // Numeric code representing the item's effect
    YsRawPngDecoder png;         // Image data
    YsSoundPlayer::SoundData sound; // Sound data
    bool imageLoaded = false;    // Flag for image load success
    bool soundLoaded = false;    // Flag for sound load success

    // Constructor
    Item(const std::string& name, int effectCode, const char* imageFile, const char* soundFile)
        : name(name), state(ONMAP), effectCode(effectCode) {
        LoadImage(imageFile);
        LoadSound(soundFile);
    }

    // Load image file
    bool LoadImage(const char* filename) {
        if (YSOK == png.Decode(filename)) {
            png.Flip();  // Flip vertically for OpenGL compatibility
            imageLoaded = true;
            return true;
        }
        std::cerr << "Failed to load image for " << name << ": " << filename << std::endl;
        return false;
    }

    // Load sound file
    bool LoadSound(const char* filename) {
        if (YSOK == sound.LoadWav(filename)) {
            soundLoaded = true;
            return true;
        }
        std::cerr << "Failed to load sound for " << name << ": " << filename << std::endl;
        return false;
    }

    // Draw item at the specified position
    void Draw(int drawX, int drawY) {
        if (!imageLoaded) return;

        float scaleX = 40.0f / png.wid; 
        float scaleY = 40.0f / png.hei; 
        glRasterPos2i(drawX, drawY);    
        glPixelZoom(scaleX, scaleY);   
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        glPixelZoom(1.0f, 1.0f);       
    }

};

int TriggerEffect(Item* heroHoldItem, YsSoundPlayer& player) {
    if (heroHoldItem == nullptr) {
        std::cout << "Hero is not holding any item!" << std::endl;
        return 0; // Return 0 to indicate no effect triggered
    }

    // Play the sound associated with the item
    if (heroHoldItem->soundLoaded) {
        player.PlayOneShot(heroHoldItem->sound);
        std::cout << "Playing sound for: " << heroHoldItem->name << std::endl;
    }
    else {
        std::cout << "No sound available for: " << heroHoldItem->name << std::endl;
    }

    // Perform item-specific actions and return the effect code
    if (heroHoldItem->name == "Gun") {
        std::cout << "Gun effect triggered" << std::endl;
        return 1; // Gun effect code
    }
    else if (heroHoldItem->name == "Health Potion") {
        std::cout << "Health Potion effect triggered" << std::endl;
        return 2; // Health potion effect code
    }
    else if (heroHoldItem->name == "Sword") {
        std::cout << "Sword effect triggered" << std::endl;
        return 3; // Sword effect code
    }
    else {
        std::cout << "Currently No Item " << heroHoldItem->name << std::endl;
        return 0; // Unknown effect code
    }
}




//main function just for testing
int main() {
    FsOpenWindow(0, 0, 800, 600, 1, "Item Drawing Example");

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize sound player
    YsSoundPlayer player;
    player.MakeCurrent();
    player.Start();

    // Create Item objects
    Item gun("Gun", 1, "gun.png", "gun.wav");
    Item healthPotion("Health Potion", 2, "hp.png", "hp.wav");
    Item sword("Sword", 3, "sword.png", "sword.wav");

    // Hero's currently held item (just for testing)
    Item* heroHoldItem = &gun;

    bool terminate = false;

    while (!terminate) {
        FsPollDevice();
        int key = FsInkey();

        if (key == FSKEY_ESC) {
            terminate = true;
        }

        if (key == FSKEY_SPACE) {
            // Trigger the effect and get the effect code
            int effectCode = TriggerEffect(heroHoldItem, player);
            std::cout << "Effect code returned: " << effectCode << std::endl;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the items at specific positions
        gun.Draw(100, 200);         // Draw gun at (100, 200)
        healthPotion.Draw(300, 500); // Draw health potion at (300, 500)
        sword.Draw(600, 400);       // Draw sword at (600, 400)

        FsSwapBuffers();
        FsSleep(10);
    }

    player.End();
    return 0;
}

/*
void Pickup() {
    state = ONPLAYER;
}

bool IsCollidingWith(const MovingCircle& player) const {
    int dx = x - player.x;
    int dy = y - player.y;
    return (dx * dx + dy * dy) <= (player.radius * player.radius);
}
*/