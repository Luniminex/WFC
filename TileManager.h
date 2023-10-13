//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_TILEMANAGER_H
#define WAVEFUNCTIONCOLLAPSE_TILEMANAGER_H

#include "FileHandler.h"
#include "Tile.h"

class TileManager {
public:
    //loads tiles from a folder
    void LoadTiles(const std::string& folderPath);
    //returns reference to unique tiles options
    [[nodiscard]] std::vector<TextureTile>& GetTextureTiles();
    void DrawTile(SDL_Renderer* renderer, int textureIdx, int rotation, SDL_Point pos, int size);
private:
    void CreateTiles(std::map<int, std::map<int, std::vector<int>>>& rules);
private:
    //vector of all possible tiles
    std::vector<TextureTile> uniqueTextureTiles_;
    std::vector<std::shared_ptr<TextureWrap>> textures_;
};


#endif //WAVEFUNCTIONCOLLAPSE_TILEMANAGER_H
