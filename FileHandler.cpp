//
// Created by luniminex on 10/7/23.
//

#include "FileHandler.h"

std::shared_ptr<Handle> FileHandler::handle_;

void FileHandler::Initialize() {
    handle_ = Handle::GetInstance();
}

std::vector<std::shared_ptr<TextureWrap>> FileHandler::LoadTextures(const std::string &folderPath) {
    std::vector<std::shared_ptr<TextureWrap>> textures;
    std::vector<std::string> filenames;
    //Iterates through directory and saves stem names of tiles
    for(const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if(entry.path().extension() == ".png") {
            filenames.push_back(entry.path().filename().stem().string());
        }
    }
    //sorts filenames in ascending order
    std::sort(filenames.begin(), filenames.end(), [](const std::string& a, const std::string& b) {
        return std::stoi(a) < std::stoi(b);
    });

    //reconstructs folderPath and loads textures
    for(const auto& filename : filenames) {
        std::string filepath = folderPath + "/" + filename + ".png";
        textures.push_back(std::make_shared<TextureWrap>(filepath, handle_->GetRenderer()));
        std::cout << "Loaded texture" << filepath << std::endl;
    }
    return textures;
}

std::map<int, std::map<int, std::vector<int>>> FileHandler::LoadRules(const std::string &folderPath) {
    std::fstream file(folderPath + "/rules");
    if(!file.is_open()) {
        std::cout << "ERROR::WFC::LOADRULES()::File not found" << std::endl;
    }
    std::map<int, std::map<int, std::vector<int>>> rules;
    std::string line;
    std::string num;
    int idx = 0;
    while(getline(file, line)){
        std::stringstream stream(line);
        std::vector<int> rulesHolder;
        while(stream >> num) { //saves rules into vector
            rulesHolder.push_back(std::stoi(num));
        }
        int rulesPerSide = rulesHolder.size() / 4;
        //rotates rules
        for(int j = 0; j < 4; j++){
            //saves rules
            for(const auto& rule : rulesHolder){
                rules[idx][j].push_back(rule);
            }

            //offsets rules by one
            for(int l = 0; l < rulesPerSide; l++) {
                int temp = rulesHolder.back();
                for (int k = static_cast<int>(rulesHolder.size()) - 2; k >= 0; k--) {
                    rulesHolder.at(k + 1) = rulesHolder.at(k);
                }
                rulesHolder.at(0) = temp;
            }
        }
        idx++;
    }
    file.close();
    std::cout << "Loaded rules for " << idx-- << " tiles " << std::endl;
    return rules;
}
