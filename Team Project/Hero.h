#ifndef HERO_H
#define HERO_H

#include "yspng.h"
#include "yssimplesound.h"

class Item;

enum Direction
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

class Map;

class Hero
{
private:
    int health;
    int attackRange;
    int damage;
    int row, col;
    Direction facingDirection;
    Item* itemOnHand;

    // Images for different directions
    YsRawPngDecoder heroUpImage;
    YsRawPngDecoder heroDownImage;
    YsRawPngDecoder heroLeftImage;
    YsRawPngDecoder heroRightImage;

public:
    Hero(int health = 100, int attackRange = 1, int damage = 10);

    // Destructor
    ~Hero();

    // Getters and setters
    int GetHealth() const;
    void SetHealth(int health);

    int GetAttackRange() const;
    void SetAttackRange(int range);

    int GetDamage() const;
    void SetDamage(int damage);

    int GetRow() const;
    int GetCol() const;

    void SetPosition(int row, int col);
    
    Item* GetItemOnHand() const;
    void SetItemOnHand(Item* item);

    // Combat
    void TakeDamage(int amount);
    bool IsAlive() const;

    // Rendering
    void Draw() const;

    // Movement
    void MoveUp(Map &map, YsSoundPlayer &player);
    void MoveDown(Map &map, YsSoundPlayer &player);
    void MoveLeft(Map &map, YsSoundPlayer &player);
    void MoveRight(Map &map, YsSoundPlayer &player);
    void MoveTo(int newRow, int newCol, Map &map, YsSoundPlayer &player);

    // Spawning
    void SpawnPlayer(int row, int col);

    // Attacking
    void Attack(Map &map, YsSoundPlayer &player);
};

#endif
