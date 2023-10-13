//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_TILE_H
#define WAVEFUNCTIONCOLLAPSE_TILE_H

#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <SDL2/SDL.h>

#define TILESIDES 4

struct TextureTile{
    int textureID;
    int rotation;
    std::vector<int> rules;
};

enum class Direction{
    TOP = 0, RIGHT = 1, BOTTOM = 2, LEFT = 3
};

enum class State {
    WAITING = 0, PENDING
};

class Tile {
public:
    Tile();
    Tile(std::vector<std::shared_ptr<TextureTile>> textureTiles);
    void SetPos(SDL_Point pos);
    void SetState(State state);
    //sets all possible options tile can have
    void FillTileOptions(std::vector<TextureTile>& uniqueTiles);
    [[nodiscard]] TextureTile& GetRules(int idx);
    [[nodiscard]] TextureTile& GetChosen();
    [[nodiscard]] SDL_Point GetPos() const;
    [[nodiscard]] int GetEntropy() const;
    [[nodiscard]] bool IsCollapsed() const;
    [[nodiscard]] State GetState() const;
    //compares rules of other tile and removes those that do not match
    void CheckRules(Tile& other, Direction dir);
    //chooses random tileOption and erases others
    bool Collapse();
private:
    //removes possible state of tile from options
    void RemoveOption(int idx);
    //gets random integer number from range
    int GetRandomFromRange(int bot, int top);
private:
    SDL_Point pos_;
    State state_;
    //may be a better option to switch to list instead of vector
    // because of erase operation that is used frequently
    std::vector<std::shared_ptr<TextureTile>> tileOptions_;
    std::shared_ptr<TextureTile> chosen_;
};

#endif //WAVEFUNCTIONCOLLAPSE_TILE_H
