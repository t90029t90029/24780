#include "Enemy.h"
#include "Hero.h"
#include "Map.h"
#include <iostream>
#include <cmath>

// Constructor
Enemy::Enemy(int health, int damage)
    : health(health), damage(damage), row(0), col(0)
{
    // Images will be loaded in SpawnEnemy
}

// Getters and setters
int Enemy::GetHealth() const
{
    return health;
}

void Enemy::SetHealth(int health)
{
    this->health = health;
}

int Enemy::GetDamage() const
{
    return damage;
}

void Enemy::SetDamage(int damage)
{
    this->damage = damage;
}

int Enemy::GetRow() const
{
    return row;
}

int Enemy::GetCol() const
{
    return col;
}

void Enemy::SetPosition(int row, int col)
{
    this->row = row;
    this->col = col;
}

// Combat
bool Enemy::Attack(Map &map)
{
    const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // UP, DOWN, LEFT, RIGHT

    for (int d = 0; d < 4; ++d)
    {
        int targetRow = row + directions[d][0];
        int targetCol = col + directions[d][1];

        // Ensure target coordinates are within map bounds
        if (targetRow < 0 || targetRow >= MAP_ROWS || targetCol < 0 || targetCol >= MAP_COLS)
        {
            continue; // Skip out-of-bounds tiles
        }

        // Check if there is a hero on the target tile
        Hero *hero = map.GetHero(targetRow, targetCol);
        if (hero != nullptr)
        {
            hero->TakeDamage(damage);
            std::cout << "Enemy at (" << row << ", " << col << ") attacked hero at (" << targetRow << ", " << targetCol << "). Hero health: " << hero->GetHealth() << std::endl;

            if (!hero->IsAlive())
            {
                std::cout << "Hero defeated!" << std::endl;
                map.SetHero(targetRow, targetCol, nullptr); // Remove the hero from the map
                delete hero; // Clean up the hero
                return true;
            }

            // Stop attacking further since each enemy can only attack one tile per action
            return false;
        }
    }

    return false;
}

void Enemy::TakeDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
    }
}

bool Enemy::IsAlive() const
{
    return health > 0;
}

// Rendering
void Enemy::Draw() const
{
    if (enemyDownImage.rgba != nullptr) // Check if the image is loaded
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
        glPixelZoom(40.0f / enemyDownImage.wid, 40.0f / enemyDownImage.hei); // Positive Y scaling

        // Render the PNG image
        glDrawPixels(enemyDownImage.wid, enemyDownImage.hei, GL_RGBA, GL_UNSIGNED_BYTE, enemyDownImage.rgba);

        // Reset pixel zoom to normal
        glPixelZoom(1.0f, 1.0f);
    }
}

// Spawning
void Enemy::SpawnEnemy(int row, int col)
{
    this->row = row;
    this->col = col;
    if (YSOK == enemyDownImage.Decode("rabbitBack.png"))
    {
        // Replace transparent pixels with white
        for (int i = 0; i < enemyDownImage.wid * enemyDownImage.hei; ++i)
        {
            unsigned char *pixel = &enemyDownImage.rgba[i * 4];
            if (pixel[3] == 0) // Fully transparent pixel (alpha = 0)
            {
                pixel[0] = 255; // Red
                pixel[1] = 255; // Green
                pixel[2] = 255; // Blue
                pixel[3] = 255; // Make it opaque
            }
        }
    }
    enemyDownImage.Flip();
    std::cout << "Enemy spawned at position: (" << row << ", " << col << ")" << std::endl;
}

void Enemy::FollowHero(const Hero &hero, Map &map)
{
    int heroRow = hero.GetRow();
    int heroCol = hero.GetCol();

    // Calculate Manhattan distance to the hero
    int distance = abs(heroRow - row) + abs(heroCol - col);

    if (distance <= 8 && distance > 1) // Example: Follow if within 5 tiles
    {
        // Determine the direction to move closer to the hero
        int moveRow = 0;
        int moveCol = 0;

        if (heroRow < row) moveRow = -1;
        else if (heroRow > row) moveRow = 1;

        if (heroCol < col) moveCol = -1;
        else if (heroCol > col) moveCol = 1;

        int newRow = row + moveRow;
        int newCol = col + moveCol;

        // Ensure the target position is accessible
        if (map.IsAccessible(newRow, newCol) && !map.GetEnemy(newRow, newCol))
        {
            map.SetEnemy(row, col, nullptr);  // Clear current position
            map.GetTile(row, col)->SetBaseType(TILE_EMPTY);
            row = newRow;
            col = newCol;
            map.SetEnemy(row, col, this);    // Set new position
            map.GetTile(row, col)->SetBaseType(TILE_ENEMY);
        }
    }
}
