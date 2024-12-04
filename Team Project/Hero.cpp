#include "Hero.h"
#include "Map.h"
#include "Tile.h"
#include "Enemy.h"
#include "Item.h"
#include "fssimplewindow.h"
#include <iostream>

// Constructor
Hero::Hero(int health, int attackRange, int damage)
    : health(health), attackRange(attackRange), damage(damage),
row(0), col(0), facingDirection(DOWN), itemOnHand(nullptr)
{
    // Images will be loaded in SpawnPlayer
}

// Destructor
Hero::~Hero()
{
    if (itemOnHand)
    {
        delete itemOnHand;
    }
}

// Spawning
void Hero::SpawnPlayer(int row, int col)
{
    this->row = row;
    this->col = col;
    facingDirection = DOWN; // Default facing direction

    // Load images for different directions
    if (YSOK == heroUpImage.Decode("heroBack.png"))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < heroUpImage.wid * heroUpImage.hei; ++i)
        {
            unsigned char *pixel = &heroUpImage.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        }
    }
    heroUpImage.Flip();


    if (YSOK == heroDownImage.Decode("heroFront.png"))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < heroDownImage.wid * heroDownImage.hei; ++i)
        {
            unsigned char *pixel = &heroDownImage.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        }
    }
    heroDownImage.Flip();

    if (YSOK == heroLeftImage.Decode("heroLeft.png"))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < heroLeftImage.wid * heroLeftImage.hei; ++i)
        {
            unsigned char *pixel = &heroLeftImage.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        }
    }
    heroLeftImage.Flip();

    if (YSOK == heroRightImage.Decode("heroRight.png"))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < heroRightImage.wid * heroRightImage.hei; ++i)
        {
            unsigned char *pixel = &heroRightImage.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        }
    }
    heroRightImage.Flip();

    std::cout << "Hero spawned at position: (" << row << ", " << col << ")" << std::endl;
}

// Drawing
void Hero::Draw() const
{
    int x = col * 40;
    int y = (row + 1) * 40; // Adjusted y-coordinate to align with items

    const YsRawPngDecoder *currentImage;

    switch (facingDirection)
    {
    case UP:
        currentImage = &heroUpImage;
        break;
    case DOWN:
        currentImage = &heroDownImage;
        break;
    case LEFT:
        currentImage = &heroLeftImage;
        break;
    case RIGHT:
        currentImage = &heroRightImage;
        break;
    default:
        break;
    }

    if (currentImage != nullptr && currentImage->rgba != nullptr)
    {
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
        glPixelZoom(40.0f / currentImage->wid, 40.0f / currentImage->hei); // Positive Y scaling

        // Render the PNG image
        glDrawPixels(currentImage->wid, currentImage->hei, GL_RGBA, GL_UNSIGNED_BYTE, currentImage->rgba);

        // Reset pixel zoom to normal
        glPixelZoom(1.0f, 1.0f);
    }
}

// Movement methods with debug output
void Hero::MoveUp(Map &map, YsSoundPlayer &player)
{
    map.GetTile(row, col)->SetBaseType(TILE_EMPTY);
    facingDirection = UP;
    MoveTo(row - 1, col, map, player);
}

void Hero::MoveDown(Map &map, YsSoundPlayer &player)
{
    map.GetTile(row, col)->SetBaseType(TILE_EMPTY);
    facingDirection = DOWN;
    MoveTo(row + 1, col, map, player);
}

void Hero::MoveLeft(Map &map, YsSoundPlayer &player)
{
    map.GetTile(row, col)->SetBaseType(TILE_EMPTY);
    facingDirection = LEFT;
    MoveTo(row, col - 1, map, player);
}

void Hero::MoveRight(Map &map, YsSoundPlayer &player)
{
    map.GetTile(row, col)->SetBaseType(TILE_EMPTY);
    facingDirection = RIGHT;
    MoveTo(row, col + 1, map, player);
}

void Hero::MoveTo(int newRow, int newCol, Map &map, YsSoundPlayer &player)
{
    if (!map.IsAccessible(newRow, newCol))
        return;

    map.SetHero(row, col, nullptr);
    map.GetTile(row, col)->SetBaseType(TILE_EMPTY);

    row = newRow;
    col = newCol;

    map.SetHero(row, col, this);
    map.GetTile(row, col)->SetBaseType(TILE_HERO);

    // Check for item
    Item *item = map.GetItem(row, col);
    if (item != nullptr)
    {
        std::cout << "Picked up item: " << item->GetName() << std::endl;

        if (item->GetDamage() > 0) // If the item is a weapon
        {
            if (itemOnHand)
            {
                std::cout << "Dropping current item: " << itemOnHand->GetName() << std::endl;
                delete itemOnHand; // Clean up the currently held item
            }
            itemOnHand = item; // Equip the new item
            std::cout << "Equipped item: " << itemOnHand->GetName() << std::endl;
        }
        else if (item->GetHeal() > 0) // If the item is consumable
        {
            player.PlayOneShot(item->GetSound());
            
            health += item->GetHeal();
            if (health > 100)
                health = 100;
            std::cout << "New HP: " << health << std::endl;
            delete item; // Remove the consumable item
        }

        map.SetItem(row, col, nullptr);
    }
}

// Combat
void Hero::Attack(Map &map, YsSoundPlayer &player)
{
    if (itemOnHand)
    {
        player.Stop(itemOnHand->GetSound());  // Stop the sound if it is already playing
        player.PlayOneShot(itemOnHand->GetSound());
    }
    
    int rangeToUse = itemOnHand ? itemOnHand->GetRange() : attackRange; // Use weapon's range or hero's default
    int damageToUse = itemOnHand ? itemOnHand->GetDamage() : damage;   // Use weapon's damage or hero's default

    for (int range = 1; range <= rangeToUse; ++range)
    {
        int targetRow = row;
        int targetCol = col;

        // Determine the target tile based on facing direction and range
        switch (facingDirection)
        {
        case UP:
            targetRow -= range;
            break;
        case DOWN:
            targetRow += range;
            break;
        case LEFT:
            targetCol -= range;
            break;
        case RIGHT:
            targetCol += range;
            break;
        default:
            break;
        }

        // Ensure target coordinates are within map bounds
        if (targetRow < 0 || targetRow >= MAP_ROWS || targetCol < 0 || targetCol >= MAP_COLS)
        {
            std::cout << "Attack went out of bounds." << std::endl;
            break; // Stop checking further tiles if out of bounds
        }

        // Attempt to attack the enemy on the target tile
        Enemy *enemy = map.GetEnemy(targetRow, targetCol);
        if (enemy != nullptr)
        {
            enemy->TakeDamage(damageToUse);
            std::cout << "Attacked enemy at (" << targetRow << ", " << targetCol << "). Enemy health: " << enemy->GetHealth() << std::endl;

            if (!enemy->IsAlive())
            {
                std::cout << "Enemy defeated!" << std::endl;
                map.SetEnemy(targetRow, targetCol, nullptr); // Remove the enemy from the map
                delete enemy; // Clean up
                map.GetTile(targetRow, targetCol)->SetBaseType(TILE_EMPTY); // Allow hero to walk through
            }
            return; // Stop attacking after hitting an enemy
        }
    }

    std::cout << "No enemy in range to attack." << std::endl;
}



// Getters and Setters
int Hero::GetHealth() const
{
    return health;
}

void Hero::SetHealth(int health)
{
    this->health = health;
}

int Hero::GetAttackRange() const
{
    return attackRange;
}

void Hero::SetAttackRange(int range)
{
    attackRange = range;
}

int Hero::GetDamage() const
{
    return damage;
}

void Hero::SetDamage(int damage)
{
    this->damage = damage;
}

int Hero::GetRow() const
{
    return row;
}

int Hero::GetCol() const
{
    return col;
}

Item* Hero::GetItemOnHand() const
{
    return itemOnHand;
}

void Hero::SetItemOnHand(Item* item)
{
    itemOnHand = item;
}

void Hero::SetPosition(int row, int col)
{
    this->row = row;
    this->col = col;
}

// Health status
void Hero::TakeDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
    }
}

bool Hero::IsAlive() const
{
    return health > 0;
}
