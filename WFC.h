//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_WFC_H
#define WAVEFUNCTIONCOLLAPSE_WFC_H

#include "TileGrid.h"

class WFC {
public:
    WFC(std::shared_ptr<TileGrid> grid);
    //chooses random tile on grid and pushes it to pending tiles
    void Start();
    void Iteration();
    void LoadTiles(const std::string& folderPath);
    void DrawCollapsedTiles(SDL_Renderer* renderer);
    [[nodiscard]] bool IsFinished() const;
private:
    SDL_Point GetRandomPosOnGrid();
    int GetPendingTileWithLeastEntropy();
    void PushUpdatedToPending(std::vector<std::shared_ptr<Tile>>& updatedTiles);
    [[nodiscard]] bool CollapseTile(Tile& tile, int idxInPending);
    [[nodiscard]] bool SelectTileFromPending(std::shared_ptr<Tile>& tile, int& tileIdx);
private:
    TileManager tileManager_;
    std::shared_ptr<TileGrid> grid_;
    std::vector<std::shared_ptr<Tile>> collapsedTiles_;
    std::vector<std::shared_ptr<Tile>> pendingTiles_;
    int stability_;
    bool finished_;
};

#endif //WAVEFUNCTIONCOLLAPSE_WFC_H
