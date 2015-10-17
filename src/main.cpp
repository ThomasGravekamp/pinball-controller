#include <iostream>

#include "kernel/Kernel.h"

Kernel* kernel;
int result;


int main(int argc, char* args[]) {

  kernel = new Kernel();

  result = kernel->init();

  if (result) {
    std::cerr << "Something went wrong while initializing the Kernel class" << std::endl;

    return 0;
  }

  result = kernel->loop();

  if (result) {
    std::cerr << "Something went wrong while the game loop was running" << std::endl;

    return 0;
  }

  result = kernel->cleanup();

  if (result) {
    std::cerr << "Something went wrong while cleaning up the Kernel class" << std::endl;
  }

  return 0;
}
