#include "Map.h"
#include "Hero.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    Map map;
    Hero *hero = nullptr;
    
    // Sound setup
    YsSoundPlayer player;
    player.MakeCurrent();
    player.Start();

    FsChangeToProgramDir();
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Load the map from the file
    if (!map.LoadFromFile("map.txt"))
    {
        return 0; // Exit if map loading fails
    }

    // Find the hero in the map
    for (int row = 0; row < MAP_ROWS; ++row)
    {
        for (int col = 0; col < MAP_COLS; ++col)
        {
            Hero *h = map.GetHero(row, col);
            if (h != nullptr)
            {
                hero = h;
                break;
            }
        }
        if (hero != nullptr)
            break;
    }

    if (hero == nullptr)
    {
        std::cerr << "Error: Hero not found in the map." << std::endl;
        return 0;
    }

    // Main game loop
    FsOpenWindow(0, 0, 800, 800, 1);

    while (true)
    {
        FsPollDevice();
        auto key = FsInkey();

        // Exit if ESC is pressed
        if (key == FSKEY_ESC)
        {
            break;
        }

        // Process player input
        switch (key)
        {
            case FSKEY_UP:
                hero->MoveUp(map, player);
                break;
            case FSKEY_DOWN:
                hero->MoveDown(map, player);
                break;
            case FSKEY_LEFT:
                hero->MoveLeft(map, player);
                break;
            case FSKEY_RIGHT:
                hero->MoveRight(map, player  );
                break;
            case FSKEY_SPACE:
                hero->Attack(map, player);
                break;
            default:
                break;
        }
        
        // Process enemy actions
        if (map.EnemyActions()) {
            std::cout << "Hero died! You lose!" << std::endl;
            break;
        }

        // Clear screen and draw the map
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        map.Draw();
        FsSwapBuffers();

        // Check if the hero has reached the door
        if (map.IsGameOver(hero->GetRow(), hero->GetCol()))
        {
            std::cout << "Hero reached the door! You win!" << std::endl;
            break;
        }

        // Delay to control frame rate
        FsSleep(30);
    }

    return 0;
}
