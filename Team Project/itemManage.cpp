#ifndef ITEM_MANAGE_H
#define ITEM_MANAGE_H
#endif 
//move this to the header file
/*
#include <stdio.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <math.h>
#include "Tile.h"
*/

#include "itemManage.h"
class Item {
public:
    std::string name;            // Item's name
    int attackRange;             // Attack range of the item
    int damage;                  // Attack damage of the item
    int heal;                    // Healing effect of the item
    YsRawPngDecoder png;         // Image data
    YsSoundPlayer::SoundData sound; // Sound data
    bool imageLoaded = false;    // Flag for image load success
    bool soundLoaded = false;    // Flag for sound load success

    // Constructor
    Item(const std::string& name, int attackRange, int damage, int heal, const char* imageFile, const char* soundFile)
        : name(name), state(ONMAP), attackRange(attackRange), damage(damage), heal(heal) {
        LoadImage(imageFile);
        LoadSound(soundFile);
    }


    int getRange() const { return this->attackRange; }
    int getHeal() const { return this->heal; }
    int getDamage() const { return this->damage; }

    // Load image file
    bool LoadImage(const char* filename) {
        if (YSOK == png.Decode(filename)) {
            //png.Flip();  // Flip vertically for OpenGL compatibility
            imageLoaded = true;
            return true;
        }
        std::cerr << "Failed to load image for " << this->name << ": " << filename << std::endl;
        return false;
    }

    // Load sound file
    bool LoadSound(const char* filename) {
        if (YSOK == sound.LoadWav(filename)) {
            soundLoaded = true;
            return true;
        }
        std::cerr << "Failed to load sound for " << this->name << ": " << filename << std::endl;
        return false;
    }

    // Draw item at the specified position
    void Draw(int tileX, int tileY) {
        if (!imageLoaded) return;

        int drawX = tileX * TILE_SIZE;
        int drawY = (tileY) * TILE_SIZE; // Adjusted to anchor from the top-left

        // Update the raster position to the bottom-left of the desired top-left anchor point
        glRasterPos2i(drawX, drawY);

        float scaleX = static_cast<float>(TILE_SIZE) / png.wid;
        float scaleY = -static_cast<float>(TILE_SIZE) / png.hei; // Negative scale to flip the image vertically

        glPixelZoom(scaleX, scaleY);
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        glPixelZoom(1.0f, 1.0f);
    }


    // Trigger the sound effect
    void TriggerEffect(YsSoundPlayer& player) {
        if (this -> soundLoaded) {
            player.PlayOneShot(sound);
            std::cout << "Playing sound for: " << this->name << std::endl;
        }
        else {
            std::cout << "No sound available for: " << this->name << std::endl;
        }
    }
};





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

    // Create Item objects //instead of default constructor, spawn item 
    Item gun("Gun", 3, 50, 0, "gun.png", "gun.wav");
    Item sword("Sword", 1, 25, 0, "sword.png", "sword.wav");
    Item healthPotion("Health Potion", 0, 0, 25, "hp.png", "hp.wav");

    // Hero's currently held item (just for testing)
    Item& itemHold = gun; 
    //hero item

    bool terminate = false;

    while (!terminate) {
        FsPollDevice();
        int key = FsInkey();

        if (key == FSKEY_ESC) {
            terminate = true;
        }

        if (key == FSKEY_SPACE) {
            itemHold.TriggerEffect(player);
            std::cout << "Range: " << itemHold.getRange() << std::endl;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the items at specific positions
        gun.Draw(0, 0);
        healthPotion.Draw(1, 0);
        sword.Draw(1, 1);


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

// use this.item.triggereffect  this.name

//int TriggerEffect(this.name, YsSoundPlayer& player) {\


//this.item.getRange()

//this.item is Item gun("Gun", 3, 50, 0, "gun.png", "gun.wav");