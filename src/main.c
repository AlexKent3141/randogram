#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "prng.h"
#include "randogram.h"
#include "assert.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

#define NUM_BITS 8
#define WINDOW_WIDTH (1 << NUM_BITS)
#define WINDOW_HEIGHT (1 << NUM_BITS)

int main(int argc, char** argv)
{
  // Parse args:
  // * First arg must be the PRNG
  //   - `qb` -> `qbasic`
  //   - `qbh` -> `qbasic_high`
  //   - `xs32` -> `xorshift32`
  //   - `msq16` -> `middle_square16`
  struct prng_info* func;
  assert(argc > 1);
  if (strcmp(argv[1], "qb") == 0) func = &qbasic;
  else if (strcmp(argv[1], "qbh") == 0) func = &qbasic_high;
  else if (strcmp(argv[1], "xs32") == 0) func = &xorshift32;
  else if (strcmp(argv[1], "msq16") == 0) func = &middle_square16;
  else if (strcmp(argv[1], "rand") == 0) func = &c_rand;
  else assert(0);

  // Pick the seed (can be overridden via the second argument).
  srand(time(NULL));
  uint32_t seed = (((uint32_t)rand()) << 16) + rand();

  if (argc > 2) {
    seed = atoi(argv[2]);
  }

  printf("Seed is: %u\n", seed);

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
  int* data = (int*)calloc(WINDOW_WIDTH*WINDOW_HEIGHT, sizeof(int));
  int* heatmap = (int*)calloc(8 * 8, sizeof(int));

  get_randogram(*func, data, heatmap, NUM_BITS, seed);

  // Print heatmap with row/column averages.
  int col_sums[NUM_BITS] = {0};
  for (int r = 0; r < NUM_BITS; r++) {
    int row_sum = 0;
    for (int c = 0; c < NUM_BITS; c++) {
      printf("%*d ", 5, heatmap[NUM_BITS * r + c]);
      row_sum += heatmap[NUM_BITS * r + c];
      col_sums[c] += heatmap[NUM_BITS * r + c];
    }

    printf("| %d\n", row_sum / NUM_BITS);
  }

  puts("------------------------------------------------");
  for (int c = 0; c < NUM_BITS; c++) {
    printf("%*d ", 5, col_sums[c] / NUM_BITS);
  }

  puts("");

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
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_q) {
            stop = SDL_TRUE;
          }
          else if (event.key.keysym.sym == SDLK_s) {
            // Create a temp surface for saving.
            SDL_Surface* tmp = SDL_CreateRGBSurface(
              0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0xff0000, 0xff00, 0xff, 0xff000000);
            SDL_RenderReadPixels(
              renderer, NULL, tmp->format->format, tmp->pixels, tmp->pitch);

            // Construct a good name.
            char name[100];
            sprintf(name, "%s-%u.png", argv[1], seed);

            IMG_SavePNG(tmp, name);

            SDL_FreeSurface(tmp);
          }
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

