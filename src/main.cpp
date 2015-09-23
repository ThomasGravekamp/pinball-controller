#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[]) {

  // Main window
  SDL_Window* window = NULL;

  // Window surface
  SDL_Surface* screen_surface = NULL;

  // Event container
  SDL_Event e;

  bool stop = false;

  bool color = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "SDL could not initialize video! SDL_Error: " << SDL_GetError() << endl;

    return 0;
  }

  // Create window
  window = SDL_CreateWindow("Pinball Controller",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (window == NULL) {
    cerr << "Could not create window! SDL_Error: " << SDL_GetError() << endl;

    return 0;
  }

  // Get the window surface
  screen_surface = SDL_GetWindowSurface(window);

  // Fill the surface
  SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

  // Update the surface
  SDL_UpdateWindowSurface(window);

  while (!stop) {

    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        stop = true;
      }

      if (e.type == SDL_KEYDOWN) {
        if (color) {
          SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));

          color = !color;
        } else {
          SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

          color = !color;
        }

        SDL_UpdateWindowSurface(window);
      }
    }

  }

  SDL_Quit();

  return 0;
}
