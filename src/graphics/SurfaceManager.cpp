#include "SurfaceManager.h"

SurfaceManager::SurfaceManager() {
  _window_surface = nullptr;
}

SurfaceManager::~SurfaceManager() {
  _window_surface = nullptr;
}

int SurfaceManager::init(SDL_Surface* window_surface) {
  if (window_surface == nullptr) {
    return 0;
  }

  _window_surface = window_surface;

  int image_flags = IMG_Init(IMG_INIT_PNG);

  if (!image_flags & IMG_INIT_PNG) {
    return 0;
  }

  return 1;
}

int SurfaceManager::cleanup() {
  // Call cleanup on every Surface object
  std::for_each(_surface_by_name.begin(), _surface_by_name.end(), [](std::pair<std::string, Surface*> pair) {
    pair.second->cleanup();
  });

  return 1;
}

Surface* SurfaceManager::createSurface(std::string name, std::string path) {
  // @TODO Check if texture is already loaded (map.count)
  // Create and initialize a new surface
  Surface* surface = new Surface();
  surface->init();

  // Try to load the given texture file
  int result = surface->loadTexture(path, _window_surface->format);
  if (!result) {
    surface->cleanup();
    delete surface;

    return nullptr;
  }

  // Add the newly made surface object to the surfaces map
  _surface_by_name.insert(std::pair<std::string, Surface*>(name, surface));

  return surface;
}

Surface* SurfaceManager::getSurface(std::string name) {
  auto result = _surface_by_name.find(name);

  if (result == _surface_by_name.end()) {
    return nullptr;
  }

  return result->second;
}
