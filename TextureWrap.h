//
// Created by luniminex on 10/7/23.
//

#ifndef WAVEFUNCTIONCOLLAPSE_TEXTUREWRAP_H
#define WAVEFUNCTIONCOLLAPSE_TEXTUREWRAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

// in future prob make a static reference to a renderer...
class TextureWrap{
public:
    TextureWrap();
    //loads from a supplied fiile
    TextureWrap(const std::string &path, SDL_Renderer* renderer);
    //loads texture from file, return false if failed
    bool LoadFromFile(const std::string &path, SDL_Renderer* renderer);
    //creates blank texture of width and height
    bool CreateBlankTexture(int width, int height, SDL_Renderer* renderer, SDL_TextureAccess textureAccess);
    //sets current texture as render target
    void SetAsRenderTarget(SDL_Renderer* renderer);
    //sets blend mode
    void SetBlendMode(SDL_BlendMode blendMode);
    //renders texture as it is at x, y
    void RenderTextureAt(int x, int y, int w, int h, SDL_Renderer* renderer);
    /*renders texture at x, y
     *  clip sets the destination size of texture, nullptr for default - scaling
     *  angle in degrees at which it will be rotated in clockwise rotation
     *  center is the point it will be rotated around, nullptr for center
     *  flip if you want the image flipped
     */
    void RenderTextureAt(int x, int y, int w, int h, SDL_Renderer* renderer, SDL_Rect* clip = nullptr, double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~TextureWrap();
private:
    SDL_Texture* texture_;
    //width of texture
    int width_;
    //height of texture
    int height_;
};

#endif //WAVEFUNCTIONCOLLAPSE_TEXTUREWRAP_H
