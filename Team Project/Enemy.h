#ifndef ENEMY_H
#define ENEMY_H

#include "fssimplewindow.h"
#include "yspng.h"

class Map;

class Enemy
{
private:
    int health;       // Enemy's health
    int damage;       // Damage dealt by the enemy
    int row, col;     // Current position of the enemy on the map (row and column)
    YsRawPngDecoder enemyDownImage;

public:
    Enemy(int health = 50, int damage = 10);

    // Getters and setters
    int GetHealth() const;
    void SetHealth(int health);

    int GetDamage() const;
    void SetDamage(int damage);

    int GetRow() const;
    int GetCol() const;

    void SetPosition(int row, int col);

    // Combat
    bool Attack(Map &map);
    void TakeDamage(int amount);
    bool IsAlive() const;

    // Rendering
    void Draw() const;

    // Spawning
    void SpawnEnemy(int row, int col);
};

#endif
