//
// Created by luniminex on 10/8/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_TILEGRID_H
#define WAVEFUNCTIONCOLLAPSE_TILEGRID_H

#include "TileManager.h"
#include <SDL2/SDL.h>

class TileGrid {
public:
    TileGrid(int gridWidth, int gridHeight, double cellSize);
    void FillTileGrid(TileManager& tileMan);
    [[nodiscard]] SDL_Point GetGridSize() const;
    [[nodiscard]] double GetCellSize() const;
    [[nodiscard]] Tile& GetTileAt(SDL_Point pos);
    [[nodiscard]] SDL_Point GetDirectionFromPosition(SDL_Point pos, Direction dir) const;
    std::vector<std::shared_ptr<Tile>> UpdateNeighbours(Tile& main);
    void UpdateNeighbourAtDir(SDL_Point pos, Direction dir, std::vector<std::shared_ptr<Tile>>& updatedTiles);
private:
    SDL_Point gridSize_;
    double cellSize_;
    std::vector<std::vector<Tile>> tiles_;
};


#endif //WAVEFUNCTIONCOLLAPSE_TILEGRID_H
