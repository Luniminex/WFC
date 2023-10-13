//
// Created by luniminex on 10/7/23.
//

#include "Tile.h"

#include <utility>

Tile::Tile() {
    chosen_ = nullptr;
    pos_ = {0,0};
    state_ = State::WAITING;
}

Tile::Tile(std::vector<std::shared_ptr<TextureTile>> textureTiles) {
    tileOptions_ = std::move(textureTiles);
    chosen_ = nullptr;
    pos_ = {0,0};
    state_ = State::WAITING;
}

TextureTile &Tile::GetRules(int idx) {
    return *tileOptions_.at(idx);
}

int Tile::GetEntropy() const {
    return static_cast<int>(tileOptions_.size());
}

void Tile::FillTileOptions(std::vector<TextureTile> &uniqueTiles) {
    for(auto& unique : uniqueTiles){
        tileOptions_.push_back(std::make_shared<TextureTile>(unique));
    }
}

bool Tile::Collapse() {
    if(tileOptions_.empty()){
        std::cout << GetPos().x << ", " << GetPos().y <<": Tried to collapse a tile that has no tile options left" << std::endl;
        return false;
    }
    int chosen = GetRandomFromRange(0, static_cast<int>(tileOptions_.size()) - 1);
    chosen_ = tileOptions_.at(chosen);
    tileOptions_.clear();
    return true;
}

TextureTile &Tile::GetChosen() {
    return *chosen_;
}

void Tile::SetPos(SDL_Point pos) {
    pos_ = pos;
}

SDL_Point Tile::GetPos() const {
    return pos_;
}

void Tile::RemoveOption(int idx) {
    if(idx >= tileOptions_.size()){
        std::cout << "Trying to remove an option from a tile at index that is out of bounds" << std::endl;
        return;
    }
    tileOptions_.erase(tileOptions_.begin() + idx);
}

void Tile::CheckRules(Tile &other, Direction dir) {
    int rulesPerSide;
    if(!tileOptions_.empty()) {
        rulesPerSide = static_cast<int>(GetRules(0).rules.size()) / TILESIDES;
    }
    else if(chosen_ != nullptr){
        rulesPerSide = static_cast<int>(chosen_->rules.size()) / TILESIDES;
    }
    TextureTile otherRules;

    int currentOffset = static_cast<int>(dir);
    int mainOffset = currentOffset * rulesPerSide;
    int otherOffset = ((currentOffset + TILESIDES / 2) % TILESIDES) * rulesPerSide;

    //goes through all tile options
    bool removed;
    for(int i = 0; i < other.GetEntropy(); i++) {
        otherRules = other.GetRules(i);
        removed = false;
        //goes through all rules on side
        //PrintChosenRules(mainOffset, rulesPerSide);
        //other.PrintRules(otherOffset, rulesPerSide, i);
        for (int j = 0; j < rulesPerSide; j++) {
            int mainIndex = mainOffset + j;
            int otherIndex = otherOffset + j;
            if (chosen_->rules.at(mainIndex) != otherRules.rules.at(otherIndex)){
                other.RemoveOption(i);
                //std::cout << "<- removed" << std::endl;
                removed = true;
                break;
            }
        }
        //std::cout << std::endl;
        //erase makes vector smaller, so it needs to check same position
        //that has different element in it
        if(removed){
            i--;
        }
    }
   // std::cout << "checked rules " << std::endl;
}

bool Tile::IsCollapsed() const {
    if(chosen_ == nullptr)
        return false;
    return true;
}

State Tile::GetState() const {
    return state_;
}

void Tile::SetState(State state) {
    state_ = state;
}

int Tile::GetRandomFromRange(int bot, int top) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> uniDist =
            std::uniform_int_distribution<int>(
                    bot, top);
    return uniDist(rng);
}
