//
// Created by luniminex on 10/7/23.
//

#include "TileManager.h"

void TileManager::LoadTiles(const std::string &folderPath) {
    textures_ = FileHandler::LoadTextures(folderPath);
    std::map<int, std::map<int, std::vector<int>>> rules = FileHandler::LoadRules(folderPath);
    CreateTiles(rules);
}

void TileManager::CreateTiles(std::map<int, std::map<int, std::vector<int>>>& rules) {
    for(const auto& textureIdx : rules){
        for(const auto& rotationIdx : textureIdx.second){
            TextureTile tx = {textureIdx.first, rotationIdx.first, rotationIdx.second};
            uniqueTextureTiles_.emplace_back(tx);
        }
    }
}

std::vector<TextureTile> &TileManager::GetTextureTiles() {
    return uniqueTextureTiles_;
}

void TileManager::DrawTile(SDL_Renderer* renderer, int textureIdx, int rotation, SDL_Point pos, int size) {
    textures_.at(textureIdx)->RenderTextureAt(pos.x, pos.y,
                                              size, size,
                                              renderer, nullptr,
                                              static_cast<double>(rotation) * 90.f,
                                              nullptr,
                                              SDL_FLIP_NONE);
}

