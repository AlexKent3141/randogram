#include "SDL2/SDL.h"
#include "stdio.h"
#include "stdlib.h"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL_Init error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow(
    "Randogram",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    800,
    600,
    SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf("SDL_CreateWindow error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  bool stop = false;
  SDL_Event event;
  while (!stop)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          stop = true;
          break;
        default:
          break;
      }
    }

    SDL_Delay(100);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}

