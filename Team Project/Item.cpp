#include "Item.h"
#include <iostream>

// Constructor
Item::Item(const std::string &name, int attackRange, int damage, int heal, const char *imageFile, const char *soundFile)
    : name(name), attackRange(attackRange), damage(damage), heal(heal), row(0), col(0)
{
    if (!LoadImage(imageFile))
    {
        std::cerr << "Failed to load image for item: " << name << std::endl;
    }

    if (!LoadSound(soundFile))
    {
        std::cerr << "Failed to load sound for item: " << name << std::endl;
    }
}

// Getters
std::string Item::GetName() const
{
    return name;
}

int Item::GetRange() const
{
    return attackRange;
}

int Item::GetHeal() const
{
    return heal;
}

int Item::GetDamage() const
{
    return damage;
}

YsSoundPlayer::SoundData &Item::GetSound()
{
    return sound;
}

int Item::GetRow() const
{
    return row;
}

int Item::GetCol() const
{
    return col;
}

void Item::SetPosition(int row, int col)
{
    this->row = row;
    this->col = col;
}

bool Item::LoadImage(const char *filename)
{
    if (YSOK == png.Decode(filename))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < png.wid * png.hei; ++i)
        {
            unsigned char *pixel = &png.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        png.Flip();
        }
        return true;
    }
    std::cerr << "Failed to load image: " << filename << std::endl;
    return false;
}

// Load a sound for the item
bool Item::LoadSound(const char *filename)
{
    return sound.LoadWav(filename) == YSOK;
}

void Item::Draw() const
{
    if (png.rgba != nullptr) // Check if the image is loaded
    {
        int x = col * 40;
        int y = (row + 1) * 40;

        // Set raster position at the top-left corner of the tile
        glRasterPos2i(x, y);

        // Check if raster position is valid
        int rasterPosValid;
        glGetIntegerv(GL_CURRENT_RASTER_POSITION_VALID, &rasterPosValid);
        if (!rasterPosValid)
        {
            std::cerr << "Invalid raster position at (" << x << ", " << y << ")" << std::endl;
            return;
        }

        // Scale the image to fit the block size (40x40 pixels)
        glPixelZoom(40.0f / png.wid, 40.0f / png.hei); // Positive Y scaling

        // Render the PNG image
        glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);

        // Reset pixel zoom to normal
        glPixelZoom(1.0f, 1.0f);
    }
}
