//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_FILEHANDLER_H
#define WAVEFUNCTIONCOLLAPSE_FILEHANDLER_H

#include <vector>
#include <map>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include "Handle.h"
#include "TextureWrap.h"

class FileHandler {
public:
    static void Initialize();
    static std::vector<std::shared_ptr<TextureWrap>> LoadTextures(const std::string& folderPath);
    static std::map<int, std::map<int, std::vector<int>>> LoadRules(const std::string& folderPath);
private:
    static std::shared_ptr<Handle> handle_;
};


#endif //WAVEFUNCTIONCOLLAPSE_FILEHANDLER_H
