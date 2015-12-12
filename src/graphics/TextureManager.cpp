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

  if (TTF_Init() == -1) {
    return 0;
  }

  // Build the path to the font
  std::string fullpath = SDL_GetBasePath();
  fullpath.append("assets/fonts/UbuntuMono-R.ttf");

  _font = TTF_OpenFont(fullpath.c_str(), 28);

  if (_font == nullptr) {
    std::cerr << TTF_GetError() << std::endl;

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

Texture* TextureManager::loadTextureFromFont(std::string name, std::string text) {
  Texture* texture = new Texture();
  texture->init();

  SDL_Color color = { 0, 0, 0, 0 };
  int result = texture->loadTextureFromFont(_font, text, &color, _renderer);
  if (!result) {
    texture->cleanup();
    delete texture;

    return nullptr;
  }

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
