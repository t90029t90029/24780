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

void Map::SpawnPlayer(int x, int y)
{
    tiles[y][x] = Tile(x * TILE_SIZE, y * TILE_SIZE, PLAYER);
}

Item Map::GetItem(int x, int y)
{
    return tiles[y][x].GetItem();
}

//
// This part is if you want to generate a maze randomly and write it to a text file.
//

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "fssimplewindow.h"
//#include "yssimplesound.h"
#include <fstream>

using namespace std;

const int windowWidth = 800;
const int windowHeight = 800;
// Must be odd for maze generation
const int mazeWidth = 19;
const int mazeHeight = 19;
// Set the size so that maze width/height * Size <= window width/height
const int cellSize = 20;

// Maze grid: 0 for spaces, 1 for walls, 2 for current path,  3 for start/end
int maze[mazeHeight][mazeWidth];

// Directions
const int directions[4][2] = {
    {-1, 0},  // Up
    {0, 1},   // Right
    {1, 0},   // Down
    {0, -1}   // Left
};

struct Node {
    int x, y;

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

void GenerateMaze() {
    // Initialize the maze with walls
    for (int i = 0; i < mazeHeight; ++i) {
        for (int j = 0; j < mazeWidth; ++j) {
            maze[i][j] = 1; // Wall
        }
    }

    // Starting position
    int startX = 1;
    int startY = 1;

    // Define the stack for backtracking
    vector<pair<int, int>> cellStack;
    cellStack.push_back({ startX, startY });
    // Mark the starting cell as passage
    maze[startY][startX] = 0;

    while (!cellStack.empty()) {
        int x = cellStack.back().first;
        int y = cellStack.back().second;

        // Find unvisited neighbors
        vector<pair<int, int>> neighbors;

        for (const auto& dir : directions) {
            int nx = x + dir[1] * 2;
            int ny = y + dir[0] * 2;

            if (nx > 0 && nx < mazeWidth - 1 && ny > 0 && ny < mazeHeight - 1) {
                if (maze[ny][nx] == 1) {
                    neighbors.push_back({ nx, ny });
                }
            }
        }

        if (!neighbors.empty()) {
            // Choose a random neighbor
            int randIndex = rand() % neighbors.size();
            auto nextCell = neighbors[randIndex];

            // Remove the wall between current cell and chosen cell
            int wallX = x + (nextCell.first - x) / 2;
            int wallY = y + (nextCell.second - y) / 2;
            maze[wallY][wallX] = 0;
            maze[nextCell.second][nextCell.first] = 0;

            // Push the chosen cell to the stack
            cellStack.push_back(nextCell);
        }
        else {
            // Backtrack
            cellStack.pop_back();
        }
    }
}

// Function to write the maze to a text file
void MazeToFile(const int maze[mazeHeight][mazeWidth], const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < mazeHeight; ++i) {
            for (int j = 0; j < mazeWidth; ++j) {
                file << maze[i][j];
                if (j < mazeWidth - 1) {
                    file << " ";
                }
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Maze saved to " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
    }
}
