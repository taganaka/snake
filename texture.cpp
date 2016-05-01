//
// Created by Francesco Laurita on 4/30/16.
//

#include "headers.h"
#include <iostream>

namespace snake {
    Texture::Texture(SDL_Renderer *renderer, TTF_Font *font) {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
        mRenderer = renderer;
        mFont = font;
    }

    Texture::~Texture() {
        free();
    }

    void Texture::free() {
        if (mTexture != nullptr) {
            SDL_DestroyTexture(mTexture);
        }
        mTexture = nullptr;
        mWidth = 0;
        mWidth = 0;

    }

    bool Texture::loadFromFile(std::string path) {
        free();
        return false;
    }

    bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
        free();
        SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), textColor);
        if (textSurface == nullptr){
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return false;
        }

        mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
        if (mTexture == nullptr){
            std::cerr << "Unable to create a texture! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }
        mWidth = textSurface->w;
        mHeight = textSurface->h;
        SDL_FreeSurface(textSurface);
        return mTexture != nullptr;
    }

    void Texture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {

        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != nullptr ) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip );

    }


    int Texture::getWidth() {
        return mWidth;
    }

    int Texture::getHeight() {
        return mHeight;
    }

    // To be implemented
    void Texture::setBlendMode(SDL_BlendMode blending) {

    }

    void Texture::setAlpha(Uint8 alpha) {

    }

    void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {

    }



}







