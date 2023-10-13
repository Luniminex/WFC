//
// Created by luniminex on 10/8/23.
//

#include "TileGrid.h"

TileGrid::TileGrid(int gridWidth, int gridHeight, double cellSize) {
    gridSize_ = {gridWidth, gridHeight};
    cellSize_ = cellSize;
}

void TileGrid::FillTileGrid(TileManager &tileMan) {
    tiles_.resize(gridSize_.y, std::vector<Tile>(gridSize_.x));
    SDL_Point pos = {0, 0};
    for (auto &row: tiles_) {
        for (auto &tile: row) {
            tile.FillTileOptions(tileMan.GetTextureTiles());
            tile.SetPos(pos);
            pos.x++;
        }
        pos.x = 0;
        pos.y++;
    }
}

SDL_Point TileGrid::GetGridSize() const {
    return gridSize_;
}

double TileGrid::GetCellSize() const {
    return cellSize_;
}

Tile &TileGrid::GetTileAt(SDL_Point pos) {
    return tiles_.at(pos.y).at(pos.x);
}

std::vector<std::shared_ptr<Tile>> TileGrid::UpdateNeighbours(Tile &main) {
    SDL_Point pos = main.GetPos();
    std::vector<std::shared_ptr<Tile>> updatedTiles;
    //check right side
    if (pos.x < gridSize_.x - 1) {
        UpdateNeighbourAtDir(pos, Direction::RIGHT, updatedTiles);
    }
    //check left side
    if (pos.x > 0) {
        UpdateNeighbourAtDir(pos, Direction::LEFT, updatedTiles);
    }
    //check top side
    if (pos.y > 0) {
        UpdateNeighbourAtDir(pos, Direction::TOP, updatedTiles);
    }
    //check bottom
    if (pos.y < gridSize_.y - 1) {
        UpdateNeighbourAtDir(pos, Direction::BOTTOM, updatedTiles);
    }
    return updatedTiles;
}

SDL_Point TileGrid::GetDirectionFromPosition(SDL_Point pos, Direction dir) const{
    SDL_Point p = pos;
    switch (dir) {
        case Direction::TOP:
            p.y--;
            break;
        case Direction::BOTTOM:
            p.y++;
            break;
        case Direction::LEFT:
            p.x--;
            break;
        case Direction::RIGHT:
            p.x++;
            break;
        default:
            break;
    }
    return p;
}

void TileGrid::UpdateNeighbourAtDir(SDL_Point pos, Direction dir, std::vector<std::shared_ptr<Tile>> &updatedTiles) {
    Tile &main = GetTileAt(pos);
    SDL_Point otherPos =  GetDirectionFromPosition(pos, dir);
    if (!GetTileAt(otherPos).IsCollapsed()) {
        main.CheckRules(GetTileAt(otherPos), dir);
        Tile &tileRef = GetTileAt(otherPos);
        if (tileRef.GetState() != State::PENDING) {
            tileRef.SetState(State::PENDING);
            updatedTiles.push_back(std::shared_ptr<Tile>(&tileRef, [](Tile *) {}));
        }
    }
}


