#include "Kernel.h"

Kernel::Kernel() {
  _texture_manager = nullptr;
  _window = nullptr;
  _renderer = nullptr;
  _texture = nullptr;

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

  // Create renderer
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  if (_renderer == nullptr) {
    std::cerr << "Could not create renderer! SDL_Error: " << SDL_GetError() << std::endl;

    return 0;
  }

  SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  _texture_manager = new TextureManager();
  _texture_manager->init(_renderer);
  _texture = _texture_manager->loadTexture("texture-1", "assets/textures/texture-1.png");

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
    }

    // Clear the screen
    SDL_RenderClear(_renderer);

    // Render texture to the screen
    _texture->render(_renderer, 0, 0);

    // Update screen
    SDL_RenderPresent(_renderer);
  }

  return 1;
}

int Kernel::cleanup() {
  _texture_manager->cleanup();
  _texture_manager = nullptr;

  SDL_DestroyWindow(_window);
  _window = nullptr;

  IMG_Quit();
  SDL_Quit();

  return 1;
}
