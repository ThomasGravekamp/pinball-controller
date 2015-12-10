#include "TextureManager.h"

TextureManager::TextureManager() {
  _renderer = nullptr;
}

TextureManager::~TextureManager() {
  _renderer = nullptr;
}

int TextureManager::init(SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    return 0;
  }

  _renderer = renderer;

  int image_flags = IMG_Init(IMG_INIT_PNG);

  if (!image_flags & IMG_INIT_PNG) {
    return 0;
  }

  return 1;
}

int TextureManager::cleanup() {
  // Call cleanup on every Surface object
  std::for_each(_texture_by_name.begin(), _texture_by_name.end(), [](std::pair<std::string, Texture*> pair) {
    pair.second->cleanup();
  });

  return 1;
}

Texture* TextureManager::loadTexture(std::string name, std::string path) {
  // @TODO Check if texture is already loaded (map.count)
  // Create and initialize a new texture
  Texture* texture = new Texture();
  texture->init();

  // Try to load the given texture file
  int result = texture->loadTexture(path, _renderer);
  if (!result) {
    texture->cleanup();
    delete texture;

    return nullptr;
  }

  // Add the newly made texture object to the textures map
  _texture_by_name.insert(std::pair<std::string, Texture*>(name, texture));

  return texture;
}

Texture* TextureManager::getTextureByName(std::string name) {
  auto result = _texture_by_name.find(name);

  if (result == _texture_by_name.end()) {
    return nullptr;
  }

  return result->second;
}
