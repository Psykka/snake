#include "SDL.h"
#include "stdio.h"
#include <time.h>
#include <math.h>

#define SIZE 25
#define PIXEL 20
#define WINDOW SIZE * PIXEL
#define FPS_CAP 120 // afeta a velocidade do jogo

typedef struct
{
    int x;
    int y;
} Position;

int tailSize = 0;

int yv = 0;     // velocidade y
int xv = PIXEL; // velocidade x

Position tail[SIZE * SIZE];
Position head = {20, 20};
Position food;

int constrain(int x, int low, int high)
{
    if (x < low)
    {
        return low;
    }
    else if (high < x)
    {
        return high;
    }
    else
        return x;
}

void drawPixel(SDL_Renderer *renderer, int x, int y, SDL_Color rgb)
{
    SDL_Rect rect;

    rect.h = PIXEL;
    rect.w = PIXEL;
    rect.x = x;
    rect.y = y;

    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderFillRect(renderer, &rect);
}

void createFood()
{
    srand(time(0));
    food.x = floor(rand() % WINDOW);
    food.y = floor(rand() % WINDOW);
}

void updateSpeed()
{
    head.x += xv;
    head.y += yv;

    head.x = constrain(head.x, 0, WINDOW - PIXEL);
    head.y = constrain(head.y, 0, WINDOW - PIXEL);
}

void gameLoop(SDL_Renderer *renderer)
{
    updateSpeed();

    // render food
    drawPixel(renderer, food.x, food.y, {0xF4, 0x35, 0x7F, 0xFF});

    // render player
    drawPixel(renderer, head.x, head.y, {0xFF, 0xFF, 0xFF, 0xFF});

    if (head.x == food.x && head.y == food.y)
    {
        tailSize++;
        createFood();
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW, WINDOW, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;

    createFood();

    while (true)
    {
        a = SDL_GetTicks();
        delta += a - b;

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)
            {
                xv = 0;
                yv = -PIXEL;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
            {
                xv = -PIXEL;
                yv = 0;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
            {
                xv = 0;
                yv = PIXEL;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            {
                xv = PIXEL;
                yv = 0;
            }
        }

        if (delta > 1000 / FPS_CAP)
        {
            gameLoop(renderer);
            delta = 0;
        }

        b = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0x38, 0x38, 0x38, 0xFF);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
