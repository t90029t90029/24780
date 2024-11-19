#include <stdio.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"

enum ItemState { ONMAP, ONPLAYER }; // States for an item

class MovingCircle {
public:
    int x, y; // Position of the circle
    int radius; // Radius of the circle

    MovingCircle(int startX, int startY, int rad) : x(startX), y(startY), radius(rad) {}

    void Move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void Draw() const {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2i(x, y); // Center of the circle
        for (int i = 0; i <= 360; ++i) {
            double angle = i * 3.14159 / 180.0;
            int cx = x + radius * cos(angle);
            int cy = y + radius * sin(angle);
            glVertex2i(cx, cy);
        }
        glEnd();
    }
};

class Item {
public:
    std::string name;
    int x, y; // Position of the item
    ItemState state; // Current state of the item
    YsRawPngDecoder png;
    YsSoundPlayer::SoundData sound;
    bool imageLoaded = false;
    bool soundLoaded = false;

    Item(const std::string& name, int x, int y, const char* imageFile, const char* soundFile)
        : name(name), x(x), y(y), state(ONMAP) {
        LoadImage(imageFile);
        LoadSound(soundFile);
    }

    bool LoadImage(const char* filename) {
        if (YSOK == png.Decode(filename)) {
            png.Flip();
            imageLoaded = true;
            return true;
        }
        std::cerr << "Failed to load image for " << name << ": " << filename << std::endl;
        return false;
    }

    bool LoadSound(const char* filename) {
        if (YSOK == sound.LoadWav(filename)) {
            soundLoaded = true;
            return true;
        }
        std::cerr << "Failed to load sound for " << name << ": " << filename << std::endl;
        return false;
    }

    void Draw(const MovingCircle& player) {
        if (state == ONPLAYER) {
            x = player.x;
            y = player.y;
        }
        if (!imageLoaded) return;

        float scaleX = 40.0f / png.wid; // Horizontal scaling factor
        float scaleY = 40.0f / png.hei; // Vertical scaling factor
        glRasterPos2i(x, y);            // Set position
        glPixelZoom(scaleX, scaleY);    // Scale to 40x40 pixels
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
        glPixelZoom(1.0f, 1.0f);        // Reset scaling to normal
    }

    void PlaySound(YsSoundPlayer& player) {
        if (soundLoaded) {
            player.PlayOneShot(sound);
        }
    }

    void TriggerEffect(YsSoundPlayer& player) {
        PlaySound(player);
        std::cout << "Effect triggered for: " << name << std::endl;
    }

    void Pickup() {
        state = ONPLAYER;
    }

    bool IsCollidingWith(const MovingCircle& player) const {
        int dx = x - player.x;
        int dy = y - player.y;
        return (dx * dx + dy * dy) <= (player.radius * player.radius);
    }
};

int main() {
    FsChangeToProgramDir();

    // Initialize the sound player
    YsSoundPlayer player;
    player.MakeCurrent();
    player.Start();

    // Create items
    Item gun("Gun", 100, 500, "gun.png", "gun.wav");
    Item healthPotion("Health Potion", 300, 500, "hp.png", "hp.wav");
    Item sword("Sword", 600, 600, "sword.png", "sword.wav");

    FsOpenWindow(0, 0, 800, 800, 1, "Multiple Items with Sound Effects");
    glEnable(GL_BLEND);  // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Set the blend function
    bool terminate = false;

    MovingCircle circle(400, 400, 20);

    while (!terminate) {
        FsPollDevice();
        int key = FsInkey();

        // Handle input
        switch (key) {
        case FSKEY_ESC:
            terminate = true;
            break;
        case FSKEY_UP:
            circle.Move(0, -10); // Move up
            break;
        case FSKEY_DOWN:
            circle.Move(0, 10); // Move down
            break;
        case FSKEY_LEFT:
            circle.Move(-10, 0); // Move left
            break;
        case FSKEY_RIGHT:
            circle.Move(10, 0); // Move right
            break;
        case FSKEY_1:
            gun.TriggerEffect(player);
            break;
        case FSKEY_2:
            healthPotion.TriggerEffect(player);
            break;
        case FSKEY_3:
            sword.TriggerEffect(player);
            break;
        }

        // Check for item pickup
        if (gun.state == ONMAP && gun.IsCollidingWith(circle)) {
            gun.Pickup();
            std::cout << "Picked up: Gun" << std::endl;
        }
        if (healthPotion.state == ONMAP && healthPotion.IsCollidingWith(circle)) {
            healthPotion.Pickup();
            std::cout << "Picked up: Health Potion" << std::endl;
        }
        if (sword.state == ONMAP && sword.IsCollidingWith(circle)) {
            sword.Pickup();
            std::cout << "Picked up: Sword" << std::endl;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the circle and items
        glColor3ub(255, 0, 0); // Set circle color to red
        circle.Draw();

        gun.Draw(circle);
        healthPotion.Draw(circle);
        sword.Draw(circle);

        FsSwapBuffers();
        FsSleep(10);
        player.KeepPlaying();
    }

    player.End();
    return 0;
}
