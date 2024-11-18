//  GameManager.cpp
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "common.h"
//#include "character.h"
//#include "item.h"
//#include "map.h"

using namespace std;

const int windowWidth = 800;
const int windowHeight = 800;

int main(void)
{
    // Initailization
    YsSoundPlayer::SoundData playerSound;
    YsSoundPlayer::SoundData enemySound;
    YsSoundPlayer::SoundData itemSound;
    YsRawPngDecoder playerPng;
    YsRawPngDecoder enemyPng;
    YsRawPngDecoder itemPng;
//    Player player = NULL;
//    Enemy[] enemies = NULL;
//    Item[] items = NULL;
//    Map map = NULL;
    
    FsChangeToProgramDir();
    // Load wav files
    if (!loadWav(playerSound, enemySound, itemSound)) {
        return 0;
    }
    
    // Load png files
    if (!loadPng(playerPng, enemyPng, itemPng)) {
        return 0;
    }
    
    // Initiate instances
//    while (!player || !enemies || !items) {
//        // Early stop if pressing ESC key
//        auto key=FsInkey();
//        if(FSKEY_ESC==key)
//        {
//            break;
//        }
//        // Loop until the instances are created at the valid coordinates
//        player = spawnPlayer(playerPng, playerSound);
//        enemies = spawnEnemies(enemyPng, enemySound);
//        items = spawnItems(itemPng, itemSound);
//    }
//
//    map = createMap(player, enemies, items);
//    if (!map) {
//        printf("Error! Did not create the map successfully.\n");
//        return 0;
//    }
    
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
            case FSKEY_DOWN:
            case FSKEY_LEFT:
            case FSKEY_RIGHT:
//                player.updatePlayerPosition(key);
                break;
            // Handle attack
            case FSKEY_SPACE:
//                player.attackTheDirection();
                break;
        }
        
        // Pick an item if any after updaing the position
//        player.pickItemIfAny();
        
        // Update the map rendering after the changes in this iteration
//        map.updateMap();
        
        // Check if the game is over (at the goal tile or the player died)
//        if (player.isGameOver()) {
//            printf("You died!\n");
//            break;
//        }
//        if (map.isGameOver()) {
//            printf("You win the game!\n");
//            break;
//        }

        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        FsSwapBuffers();

        FsSleep(1);
    }
    
    return 0;
}
