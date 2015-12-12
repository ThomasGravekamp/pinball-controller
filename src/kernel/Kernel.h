#ifndef PC_KERNEL_H
#define PC_KERNEL_H

#include <iostream>
#include <string>

#include <SDL.h>

#include "../graphics/Texture.h"
#include "../graphics/TextureManager.h"

// @TODO Move to config file
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class Kernel {
private:
  // TextureManager
  TextureManager* _texture_manager;

  // Main window
  SDL_Window* _window;

  // Renderer
  SDL_Renderer* _renderer;

  // Main texture
  Texture* _texture;

  // Text texture
  Texture* _textTexture;

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
