#include "Surface.h"

Surface::Surface() {
  _surface = nullptr;
}

Surface::~Surface() {}

int Surface::init() {
  return 1;
}

int Surface::cleanup() {
  if (_surface != nullptr) {
    SDL_FreeSurface(_surface);
    _surface = nullptr;
  }

  return 1;
}

int Surface::loadTexture(std::string path, SDL_PixelFormat* format) {
  // Build the path to the texture
  std::string fullpath = SDL_GetBasePath();
  fullpath.append(path);

  // Load the texture
  SDL_Surface* new_surface = nullptr;
  new_surface = IMG_Load(fullpath.c_str());

  if (new_surface == NULL) {
    return 0;
  }

  // Optimize the texture for the display in use
  SDL_Surface* optimized_surface = nullptr;
  optimized_surface = SDL_ConvertSurface(new_surface, format, 0);

  if (optimized_surface == NULL) {
    SDL_FreeSurface(new_surface);

    return 0;
  }

  _surface = optimized_surface;
  return 1;
}

SDL_Surface* Surface::getSurface() {
  return _surface;
}
