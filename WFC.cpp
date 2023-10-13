//
// Created by luniminex on 10/7/23.
//

#include "WFC.h"

#include <utility>

WFC::WFC(std::shared_ptr<TileGrid> grid) : tileManager_(){
    grid_ = std::move(grid);
    stability_ = 0;
    finished_ = false;
}

void WFC::Start() {
    SDL_Point startPos = GetRandomPosOnGrid();
    Tile& tileRef = grid_->GetTileAt(startPos);
    pendingTiles_.push_back(std::shared_ptr<Tile>(&tileRef, [](Tile*){}));
}

void WFC::Iteration() {
    if(finished_) {
        return;
    }
    std::shared_ptr<Tile> tile;
    int tileIdx;
    if(!SelectTileFromPending(tile, tileIdx)){
        std::cerr << "No tiles left in pending, finished" << std::endl;
        return;
    }

    if(!CollapseTile(*tile, tileIdx)){
        pendingTiles_.erase(pendingTiles_.begin() + tileIdx);
        std::cerr << "Failed to collapse a tile  " << std::endl;
        return;
    }

    std::vector<std::shared_ptr<Tile>> updatedTiles;
    updatedTiles = grid_->UpdateNeighbours(*tile);
    PushUpdatedToPending(updatedTiles);
}

void WFC::PushUpdatedToPending(std::vector<std::shared_ptr<Tile>>& updatedTiles) {
    for(auto& updatedTile : updatedTiles){
        pendingTiles_.push_back(updatedTile);
    }
}

bool WFC::CollapseTile(Tile &tile, int idxInPending) {
    if(!tile.Collapse()){
        return false;
    }
    collapsedTiles_.push_back(pendingTiles_.at(idxInPending));
    pendingTiles_.erase(pendingTiles_.begin() + idxInPending);
    return true;
}

void WFC::LoadTiles(const std::string &folderPath) {
    tileManager_.LoadTiles(folderPath);
    grid_->FillTileGrid(tileManager_);
}

SDL_Point WFC::GetRandomPosOnGrid() {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uniDist =
            std::uniform_int_distribution<int>(
                    0,grid_->GetGridSize().x * grid_->GetGridSize().y - 1
            );
    int random = uniDist(rng);
    int x = random % grid_->GetGridSize().x;
    int y = random / grid_->GetGridSize().y;
    return {x, y};
}

int WFC::GetPendingTileWithLeastEntropy() {
    if(pendingTiles_.empty()) {
        return -1;
    }
    //multiple tiles can have same entropy
    std::vector<int> options;
    int leastEntropy = pendingTiles_.front()->GetEntropy();
    int idx = 0;
    //find the least entropy
    for(auto& tile : pendingTiles_){
        if(leastEntropy > tile->GetEntropy())
            leastEntropy = tile->GetEntropy();
    }

    //find all with that entropy
    for(int i = 0; i < pendingTiles_.size(); i++){
        if(pendingTiles_.at(i)->GetEntropy() <= leastEntropy + stability_){
            options.push_back(i);
        }
    }
    //choose random option
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uniDist =
            std::uniform_int_distribution<int>(
                    0,static_cast<int>(options.size()) - 1 );
    int random = uniDist(rng);
    return options.at(random);
}

bool WFC::SelectTileFromPending(std::shared_ptr<Tile>& tile, int& tileIdx) {
    if(pendingTiles_.empty()){
        std::cerr << "Pending tiles empty, finished" << std::endl;
        finished_ = true;
        return false;
    }

    tileIdx = GetPendingTileWithLeastEntropy();

    if(tileIdx == -1) {
        std::cerr << "There is no pending tile" << std::endl;
        finished_ = true;
        return false;
    }
    tile = pendingTiles_.at(tileIdx);
    return true;
}

void WFC::DrawCollapsedTiles(SDL_Renderer *renderer) {
    int textureId;
    int rotation;
    SDL_Point  pos;
    for(auto& tile : collapsedTiles_){
        textureId = tile->GetChosen().textureID;
        rotation = tile->GetChosen().rotation;
        pos = {static_cast<int>(tile->GetPos().x * grid_->GetCellSize()),
               static_cast<int>(tile->GetPos().y * grid_->GetCellSize())};

        tileManager_.DrawTile(renderer, textureId, rotation, pos,
                              static_cast<int>(grid_->GetCellSize()));
    }
}

bool WFC::IsFinished() const{
    return finished_;
}
