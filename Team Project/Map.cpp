#include "Map.h"

// Map Implementation
Map::Map() : playerRow(-1), playerCol(-1), doorRow(-1), doorCol(-1) {}

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
            int tileType;
            if (!(file >> tileType) || tileType < 0 || tileType > 5)
            {
                std::cerr << "Error: Invalid map data at row " << row << ", col " << col << std::endl;
                return false;
            }

            tiles[row][col] = Tile(col * TILE_SIZE, row * TILE_SIZE, static_cast<TileType>(tileType));

            if (tileType == PLAYER)
            {
                playerRow = row;
                playerCol = col;
            }
            else if (tileType == DOOR)
            {
                doorRow = row;
                doorCol = col;
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

void Map::UpdatePlayerPosition(int newRow, int newCol)
{
    // Check for boundaries
    if (newRow < 0 || newRow >= MAP_ROWS || newCol < 0 || newCol >= MAP_COLS)
    {
        // Out of boundary; keep the player in the same position
        return;
    }

    // Check for collision with a wall
    if (tiles[newRow][newCol].GetType() == WALL)
    {
        // Player hit a wall; keep the player in the same position
        return;
    }

    // Update tile type of old position to empty
    tiles[playerRow][playerCol].SetType(EMPTY);

    // Update tile type of new position to player
    playerRow = newRow;
    playerCol = newCol;
    tiles[playerRow][playerCol].SetType(PLAYER);
}

bool Map::IsAccessible(int row, int col) const
{
    return (tiles[row][col].GetType() != WALL && tiles[row][col].GetType() != ENEMY);
}

bool Map::IsGameOver() const
{
    return (playerRow == doorRow && playerCol == doorCol);
}

int Map::GetPlayerRow() const
{
    return playerRow;
}

int Map::GetPlayerCol() const
{
    return playerCol;
}
