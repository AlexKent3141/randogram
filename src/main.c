#include "SDL2/SDL.h"
#include "prng.h"
#include "randogram.h"
#include "stdio.h"
#include "stdlib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf("SDL_CreateWindow error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Texture* texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STATIC,
    WINDOW_WIDTH,
    WINDOW_HEIGHT);
  if (texture == NULL)
  {
    printf("SDL_CreateTexture error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Calculate the randogram that we want to plot.
  float* data = (float*)malloc(WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(float));
  get_randogram(qbasic, data, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Set the pixels on the texture.
  uint32_t* pixels = (uint32_t*)malloc(WINDOW_WIDTH*WINDOW_HEIGHT*sizeof(float));
  SDL_PixelFormat* fmt = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  for (int i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT; i++)
  {
    uint32_t colour = SDL_MapRGB(fmt, 255*data[i], 255*data[i], 255*data[i]);
    pixels[i] = colour;
  }

  SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH*sizeof(uint32_t));

  free(data);
  free(pixels);

  SDL_bool stop = SDL_FALSE;
  SDL_Event event;
  while (!stop)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          stop = SDL_TRUE;
          break;
        default:
          break;
      }
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(100);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}

