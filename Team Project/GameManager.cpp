//  GameManager.cpp
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "common.h"
#include "Map.h"

using namespace std;

const int windowWidth = 800;
const int windowHeight = 800;

int main(void)
{
    // Initailization
    Map map;
    
    FsChangeToProgramDir();
    // Load the map
    if (!map.LoadFromFile("map.txt"))
    {
        return 0;
    }
    
    FsOpenWindow(0, 0, windowWidth, windowHeight, 1);
    for (;;) {
        FsPollDevice();

        auto key = FsInkey();
        // Early stop if pressing ESC key
        if(FSKEY_ESC == key)
        {
            break;
        }

        switch(key) {
            // Handle movement
            case FSKEY_UP:
                map.UpdatePlayerPosition(map.GetPlayerRow() - 1, map.GetPlayerCol());
                break;
            case FSKEY_DOWN:
                map.UpdatePlayerPosition(map.GetPlayerRow() + 1, map.GetPlayerCol());
                break;
            case FSKEY_LEFT:
                map.UpdatePlayerPosition(map.GetPlayerRow(), map.GetPlayerCol() - 1);
                break;
            case FSKEY_RIGHT:
                map.UpdatePlayerPosition(map.GetPlayerRow(), map.GetPlayerCol() + 1);
                break;
            // Handle attack
            case FSKEY_SPACE:
                break;
        }

        // Clear the screen before drawing
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        // Draw the map
        map.Draw();

        // Check if the player is at the goal tile of the current map
        if (map.IsGameOver()) {
            printf("You win the game!\n");
            break;
        }

        FsSwapBuffers();
        FsSleep(10);
    }
    
    return 0;
}
