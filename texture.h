//
// Created by Francesco Laurita on 4/30/16.
//

#ifndef SDL_SNAKE_TEXTURE_H
#define SDL_SNAKE_TEXTURE_H

#include <string>
namespace snake {
    class Texture {
    public:
        Texture(SDL_Renderer *renderer, TTF_Font *font);
        ~Texture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render(int x,
                    int y,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE
        );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;
        SDL_Renderer* mRenderer;
        TTF_Font* mFont;
        //Image dimensions
        int mWidth;
        int mHeight;
    };
}


#endif //SDL_SNAKE_TEXTURE_H
