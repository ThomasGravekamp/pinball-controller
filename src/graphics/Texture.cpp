#include "Texture.h"

Texture::Texture() {
  _texture = nullptr;
}

Texture::~Texture() {

}

int Texture::init() {
  return 1;
}

int Texture::cleanup() {
  if (_texture != nullptr) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }

  return 1;
}

int Texture::loadTexture(std::string path, SDL_Renderer* renderer) {
  // Build the path to the texture
  std::string fullpath = SDL_GetBasePath();
  fullpath.append(path);

  // Load the texture
  SDL_Surface* new_surface = nullptr;
  new_surface = IMG_Load(fullpath.c_str());

  if (new_surface == NULL) {
    return 0;
  }

  _texture = SDL_CreateTextureFromSurface(renderer, new_surface);

  if (_texture == nullptr) {
    return 0;
  }

  SDL_FreeSurface(new_surface);

  return 1;
}

int Texture::loadTexture(SDL_Surface* surface, SDL_Renderer* renderer) {
  _texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (_texture == nullptr) {
    return 0;
  }

  return 1;
}

SDL_Texture* Texture::getTexture() {
  return _texture;
}
