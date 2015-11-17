#include "Kernel.h"

Kernel::Kernel() {
  _surface_manager = nullptr;

  this->_stop = false;
  this->_color = true;
}

int Kernel::init() {
  // Initialize SDL video
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize video! SDL_Error: " << SDL_GetError() << std::endl;

    return 0;
  }

  // Create window
  _window = SDL_CreateWindow("Pinball Controller",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (_window == NULL) {
    std::cerr << "Could not create window! SDL_Error: " << SDL_GetError() << std::endl;

    return 0;
  }

  // Get the window surface
  _surface = SDL_GetWindowSurface(_window);

  // Fill the surface
  SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 0xFF, 0xFF, 0xFF));

  _surface_manager = new SurfaceManager();
  _surface_manager->init(_surface);
  _texture = _surface_manager->createSurface("texture-1", "assets/textures/texture-1.png");

  if (_texture == nullptr) {
    std::cerr << "Something went wrong while creating the surface" << std::endl;
    return 0;
  }

  // Update the surface
  SDL_UpdateWindowSurface(_window);

  return 1;
}

int Kernel::loop() {
  while (!_stop) {

    while (SDL_PollEvent(&_e) != 0) {
      if (_e.type == SDL_QUIT) {
        _stop = true;
      }

      if (_e.type == SDL_KEYDOWN) {
        if (_color) {
          SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 0x00, 0x00, 0x00));

          _color = !_color;
        } else {
          SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 0xFF, 0xFF, 0xFF));

          _color = !_color;
        }

        SDL_BlitSurface(_texture->getSurface(), NULL, _surface, NULL);

        SDL_UpdateWindowSurface(_window);
      }
    }

  }

  return 1;
}

int Kernel::cleanup() {
  _surface_manager->cleanup();
  _surface_manager = nullptr;

  SDL_DestroyWindow(_window);
  _window = nullptr;

  SDL_Quit();

  return 1;
}
