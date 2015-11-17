#ifndef PC_SURFACE_MANAGER_H
#define PC_SURFACE_MANAGER_H

#include <algorithm>
#include <map>
#include <string>
#include <utility>

#include <SDL.h>

#include "Surface.h"

class SurfaceManager {
private:
  std::map<std::string, Surface*> _surface_by_name;
  SDL_Surface* _window_surface;

public:
  SurfaceManager();
  ~SurfaceManager();

  int init(SDL_Surface* window_surface);
  int cleanup();

  Surface* createSurface(std::string name, std::string path);
  Surface* getSurface(std::string name);
};

#endif
