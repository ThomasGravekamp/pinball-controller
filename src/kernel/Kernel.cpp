#include "Kernel.h"

Kernel::Kernel() {
  _stop = false;
  _color = true;
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

  // Update the surface
  SDL_UpdateWindowSurface(_window);

  std::string filename = SDL_GetBasePath();
  filename.append("assets/textures/texture-1.bmp");

  // Load the texture
  _texture = SDL_LoadBMP(filename.c_str());

  if (_texture == NULL) {
    std::cerr << SDL_GetError() << std::endl;
    return 0;
  }

  _texture = SDL_ConvertSurface(_texture, _surface->format, 0);

  if (_texture == NULL) {
    std::cerr << SDL_GetError() << std::endl;
    return 0;
  }

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

        SDL_BlitSurface(_texture, NULL, _surface, NULL);

        SDL_UpdateWindowSurface(_window);
      }
    }

  }

  return 1;
}

int Kernel::cleanup() {
  SDL_FreeSurface(_texture);
  _texture = NULL;

  SDL_DestroyWindow(_window);
  _window = NULL;

  SDL_Quit();

  return 1;
}
