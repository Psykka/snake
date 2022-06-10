#include "SDL.h"
#include "stdio.h"
#include <tuple>

#define SIZE 25

int game[SIZE][SIZE];

enum Objects
{
    WALL = 1,
    HEAD,
    BODY,
    FOOD
};

void drawGame(SDL_Renderer *renderer)
{
    // for (int i = 0; i < 25; i++)
    // {
    // }
    
    SDL_Rect rect;

    rect.h = 20;
    rect.w = 20;
    rect.x = 0;
    rect.y = 20;

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Event event;

    bool inputThisFrame = false;

    for (int i = 0; i < SIZE; i++)
    {
        game[0][i] = Objects::WALL;
        game[SIZE - 1][i] = Objects::WALL;
        game[i][0] = Objects::WALL;
        game[i][SIZE - 1] = Objects::WALL;
    }

    // for (int i = 0; i < SIZE; i++)
    // {
    //     for (int j = 0; j < SIZE; j++)
    //     {
    //         printf("%i ", game[i][j]);
    //     }
    //     printf("\n");
    // }

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(520, 500, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    drawGame(renderer);

    while (true)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            break;
        }


        // if (event.type == SDL_KEYDOWN && inputThisFrame == false)
        // {
        // }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
