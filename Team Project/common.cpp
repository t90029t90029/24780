//  common.cpp
#include "yssimplesound.h"
#include "yspng.h"

bool loadWav(YsSoundPlayer::SoundData & playerSound, YsSoundPlayer::SoundData & enemySound, YsSoundPlayer::SoundData & itemSound) {
    if (YSOK != playerSound.LoadWav("player.wav")) {
        printf("Error! Cannot load player.wav\n");
        return false;
    }
    if (YSOK != enemySound.LoadWav("enemy.wav")) {
        printf("Error! Cannot load enemy.wav\n");
        return false;
    }
    if (YSOK != itemSound.LoadWav("item.wav")) {
        printf("Error! Cannot load item.wav\n");
        return false;
    }
    return true;
}

bool loadPng(YsRawPngDecoder & playerPng, YsRawPngDecoder & enemyPng, YsRawPngDecoder & itemPng) {
    if (YSOK != playerPng.Decode("player.png"))
    {
        printf("Error! Cannot load player.png\n");
        return false;
    }
    if (YSOK != enemyPng.Decode("enemy.png"))
    {
        printf("Error! Cannot load enemy.png\n");
        return false;
    }
    if (YSOK != itemPng.Decode("item.png"))
    {
        printf("Error! Cannot load item.png\n");
        return false;
    }
    return true;
}
