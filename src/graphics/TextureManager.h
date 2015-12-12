#ifndef PC_TEXTURE_MANAGER_H
#define PC_TEXTURE_MANAGER_H

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <utility>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"

class TextureManager {
private:
  std::map<std::string, Texture*> _texture_by_name;
  SDL_Renderer* _renderer;
  TTF_Font* _font;

public:
  TextureManager();
  ~TextureManager();

  int init(SDL_Renderer* renderer);
  int cleanup();

  Texture* loadTexture(std::string name, std::string path);
  Texture* loadTextureFromFont(std::string name, std::string text);
  Texture* getTextureByName(std::string name);
};

#endif
