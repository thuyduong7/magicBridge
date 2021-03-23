#include "Texture.h"
#include "Core.h"

using namespace std;

Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

SDL_Texture* Texture::loadFromFile(string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL){
        //SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0xff, 0xff, 0xff));
        newTexture = SDL_CreateTextureFromSurface(Core::renderer, loadSurface);
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}

void Texture::render(SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect,  SDL_RendererFlip flip, double angle, SDL_Point* center)
{
    SDL_RenderCopyEx(Core::renderer, _texture, &scrRect, &dstRect, angle, center, flip);
}

SDL_Texture* Texture::getTexture()
{
    return texture;
}

void Texture::free()
{
    SDL_DestroyTexture(texture);
    texture = NULL;
    height = 0;
    width = 0;
}

