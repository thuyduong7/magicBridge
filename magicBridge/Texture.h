#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Texture
{
    public:
        Texture();
        ~Texture();
        static SDL_Texture* loadFromFile(string path);
        static void render(SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0, SDL_Point* center = NULL);
        SDL_Texture* getTexture();
        void free();

    //private:
        SDL_Texture* texture;
        int width, height;
};

#endif // TEXTURE_H

