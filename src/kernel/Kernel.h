#ifndef PC_KERNEL_H
#define PC_KERNEL_H

#include <iostream>
#include <string>

#include <SDL.h>

#include "../graphics/Surface.h"
#include "../graphics/SurfaceManager.h"

// @TODO Move to config file
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class Kernel {
private:
  // SurfaceManager
  SurfaceManager* _surface_manager;

  // Main window
  SDL_Window* _window;

  // Window surface
  SDL_Surface* _surface;

  // Texture surface
  Surface* _texture;

  // Event container
  SDL_Event _e;

  // Temp var
  bool _stop;

  // Temp var
  bool _color;

public:
  Kernel();

  int init();
  int loop();
  int cleanup();
};

#endif
