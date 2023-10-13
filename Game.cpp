//
// Created by luniminex on 10/7/23.
//

#include <fstream>
#include "Game.h"

Game::Game() :
        grid_(16, 16, 50),
        wfc_(std::make_shared<TileGrid>(grid_))
    {
    handle_ = Handle::GetInstance();
    running_ = true;
    want_quit_ = false;
    keys_['x'] = false; //exit
    keys_['w'] = false; //iteration
}

void Game::Start() {
    handle_->Init();
    FileHandler::Initialize();

    CreateWindow();
    handle_->CreateRenderer(SDL_RENDERER_ACCELERATED);

    LoadTiles();
    wfc_.Start();
    Play();
}

void Game::Play() {
    const float fps = 60.f;
    const float delay = 1000.f / fps;
    Uint64 lastUpdate = SDL_GetTicks64();


    while(running_){
        Uint64 current = SDL_GetTicks64();

        HandleEvents();

        float dt = static_cast<float>((current - lastUpdate)) / 1000.f;

        //update
        if(keys_.at('w')){
            wfc_.Iteration();
            keys_.at('w') = false;
        }
        wfc_.Iteration();

        //UpdateEntities(dt);

        //draw
        SDL_SetRenderTarget(handle_->GetRenderer(), nullptr);
        SDL_SetRenderDrawColor(handle_->GetRenderer(), 128, 128, 128, 255);
        SDL_RenderClear(handle_->GetRenderer());
        Draw();

        SDL_RenderPresent(handle_->GetRenderer());

        Uint64 frameTime = SDL_GetTicks64() - current;
        if(static_cast<float>(frameTime) < delay){
           SDL_Delay(static_cast<Uint32>(delay - static_cast<float>(frameTime)));
        }
        CheckQuit();
    }
    Quit();
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            std::cout<<"Wants to end"<<std::endl;
            want_quit_ = true;
        }
        else if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
                case SDLK_e:
                    keys_['e'] = true;
                    want_quit_ = true;
                    break;
                case SDLK_w:
                    keys_['w'] = true;
                    break;
            }
        }
    }
}

void Game::CheckQuit() {
    if(want_quit_){
        running_ = false;
    }
}

void Game::Quit() {
    SDL_Quit();
}

void Game::DrawGrid() {
    SDL_SetRenderDrawColor(handle_->GetRenderer(), 0, 0, 0, 255);
    int width = handle_->GetWindowInfo().width;
    int height = handle_->GetWindowInfo().height;
    int cellSize = static_cast<int>(grid_.GetCellSize());

    for(int i = 1; i < grid_.GetGridSize().x; i++){
        SDL_RenderDrawLine(handle_->GetRenderer(),0, i*cellSize,width,i*cellSize);
    }
    for(int i = 1; i < grid_.GetGridSize().y; i++){
        SDL_RenderDrawLine(handle_->GetRenderer(),i*cellSize, 0,i*cellSize,height);
    }
}

void Game::CreateWindow() {
    int width = static_cast<int>(grid_.GetGridSize().x * grid_.GetCellSize());
    int height = static_cast<int>(grid_.GetGridSize().y * grid_.GetCellSize());
    handle_->CreateWindow("WaveFunctionCollapse", width, height, SDL_WINDOW_SHOWN);
}

void Game::LoadTiles() {
    wfc_.LoadTiles("../tilesets/circuit");
}

void Game::Draw() {
    DrawGrid();
    //if(wfc_.IsFinished())
        wfc_.DrawCollapsedTiles(handle_->GetRenderer());
}
