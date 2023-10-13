//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_GAME_H
#define WAVEFUNCTIONCOLLAPSE_GAME_H

#include "WFC.h"

class Game {
public:
    Game();
    void Start();
private:
    //the game loop
    void Play();
    void CheckQuit();
    void HandleEvents();
    void Quit();
private:
    void CreateWindow();
    void LoadTiles();
    void Draw();
    void DrawGrid();
private:
    std::shared_ptr<Handle> handle_;
    TileGrid grid_;
    WFC wfc_;
    bool running_;
    bool want_quit_;
    std::map<char, bool> keys_;
};
#endif //WAVEFUNCTIONCOLLAPSE_GAME_H
