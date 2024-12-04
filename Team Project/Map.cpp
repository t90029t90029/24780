#include "Map.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

Map::Map() : doorRow(-1), doorCol(-1), enemyAttackSwitch(0)
{
    // Initialize random seed if needed
}

Map::~Map()
{
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            if (tiles[row][col].GetItem() != nullptr)
            {
                delete tiles[row][col].GetItem();
                tiles[row][col].SetItem(nullptr);
            }
            if (tiles[row][col].GetEnemy() != nullptr)
            {
                delete tiles[row][col].GetEnemy();
                tiles[row][col].SetEnemy(nullptr);
            }
            if (tiles[row][col].GetHero() != nullptr)
            {
                delete tiles[row][col].GetHero();
                tiles[row][col].SetHero(nullptr);
            }
        }
    }
}


bool Map::LoadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            int tileTypeInt = -1;
            if (!(file >> tileTypeInt))
            {
                std::cerr << "Error: Failed to read map data at row " << row << ", col " << col << std::endl;
                return false;
            }

            TileType tileType = static_cast<TileType>(tileTypeInt);
            tiles[row][col] = Tile(col * 40, row * 40, tileType);

            switch (tileType)
            {
                case TILE_DOOR:
                    doorRow = row;
                    doorCol = col;
                    break;

                case TILE_HERO:
                {
                    // Initialize the hero
                    Hero *newHero = new Hero();
                    tiles[row][col].SetHero(newHero);
                    newHero->SpawnPlayer(row, col);
                    break;
                }

                case TILE_ENEMY:
                {
                    // Initialize an enemy
                    Enemy *newEnemy = new Enemy();
                    tiles[row][col].SetEnemy(newEnemy);
                    newEnemy->SpawnEnemy(row, col);
                    break;
                }

                case TILE_ITEM:
                {
                    // Randomly select an item type
                    int randomType = std::rand() % 3; // Assuming 3 types of items
                    Item *newItem = nullptr;

                    switch (randomType)
                    {
                        case 0:
                            newItem = new Item("Gun", 3, 50, 0, "gun.png", "gun.wav");
                            break;
                        case 1:
                            newItem = new Item("Sword", 1, 25, 0, "sword.png", "sword.wav");
                            break;
                        case 2:
                            newItem = new Item("Health Potion", 0, 0, 25, "hp.png", "hp.wav");
                            break;
                        default:
                            break;
                    }

                    if (newItem != nullptr)
                    {
                        tiles[row][col].SetItem(newItem);
                        newItem->SetPosition(row, col);
                        std::cout << "Item spawned at position: (" << row << ", " << col << "), Type: " << newItem->GetName() << std::endl;
                    }
                    break;
                }

                default:
                    break;
            }
        }
    }

    return true;
}

void Map::Draw() const
{
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            tiles[row][col].Draw();
        }
    }
}

bool Map::IsAccessible(int row, int col) const
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return false; // Out of bounds
    }

    TileType baseType = tiles[row][col].GetBaseType();
    if (baseType == TILE_WALL)
        return false; // Can't walk into walls

    // Allow moving into tiles with items
    // Can't move into tiles with enemies (handled in Hero's MoveTo)
    return baseType == TILE_EMPTY || baseType == TILE_DOOR || baseType == TILE_ITEM;
}

bool Map::IsGameOver(int row, int col) const
{
    return row == doorRow && col == doorCol;
}

Item* Map::GetItem(int row, int col) const
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return nullptr; // Out of bounds
    }

    return tiles[row][col].GetItem();
}

void Map::SetItem(int row, int col, Item* item)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return; // Out of bounds, do nothing
    }

    tiles[row][col].SetItem(item);
}

void Map::SetHero(int row, int col, Hero* hero)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return; // Out of bounds, do nothing
    }

    tiles[row][col].SetHero(hero);
}

Hero* Map::GetHero(int row, int col) const
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return nullptr; // Out of bounds
    }

    return tiles[row][col].GetHero();
}

void Map::SetEnemy(int row, int col, Enemy* enemy)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return; // Out of bounds, do nothing
    }

    tiles[row][col].SetEnemy(enemy);
}

Enemy* Map::GetEnemy(int row, int col) const
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return nullptr; // Out of bounds
    }

    return tiles[row][col].GetEnemy();
}

Tile* Map::GetTile(int row, int col)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return nullptr; // Return nullptr for out-of-bounds access
    }
    return &tiles[row][col];
}

bool Map::EnemyActions(Hero &hero)
{
    ++enemyAttackSwitch;
    
    if (enemyAttackSwitch % 5  == 0) {
        for (int row = 0; row < MAP_ROWS; ++row)
        {
            for (int col = 0; col < MAP_COLS; ++col)
            {
                Enemy* enemy = tiles[row][col].GetEnemy();
                if (enemy != nullptr)
                {
                    if (!enemy->Attack(*this)) // Attack if the hero is adjacent
                    {
                        enemy->FollowHero(hero, *this); // Otherwise, follow the hero
                    } else {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

