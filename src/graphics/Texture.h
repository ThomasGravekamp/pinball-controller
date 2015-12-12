#ifndef PC_TEXTURE_H
#define PC_TEXTURE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture {
private:
  SDL_Texture* _texture;
  SDL_Rect* _renderRectangle;

  int _width;
  int _height;

public:
  Texture();
  ~Texture();

  int init();
  int cleanup();

  void render(SDL_Renderer* renderer, int x, int y);

  int loadTexture(std::string path, SDL_Renderer* renderer);
  int loadTexture(SDL_Surface* surface, SDL_Renderer* renderer);
  int loadTextureFromFont(TTF_Font* font, std::string text, SDL_Color* color, SDL_Renderer* renderer);
  SDL_Texture* getTexture();
};

#endif
