#ifndef PC_TEXTURE_H
#define PC_TEXTURE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Texture {
private:
  SDL_Texture* _texture;

public:
  Texture();
  ~Texture();

  int init();
  int cleanup();

  void render(SDL_Renderer* renderer);

  int loadTexture(std::string path, SDL_Renderer* renderer);
  int loadTexture(SDL_Surface* surface, SDL_Renderer* renderer);
  SDL_Texture* getTexture();
};

#endif
