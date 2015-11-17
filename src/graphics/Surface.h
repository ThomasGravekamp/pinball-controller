#ifndef PC_SURFACE_H
#define PC_SURFACE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Surface {
private:
  SDL_Surface* _surface;

public:
  Surface();
  ~Surface();

  int init();
  int cleanup();

  int loadTexture(std::string path, SDL_PixelFormat* format);
  SDL_Surface* getSurface();
};

#endif
