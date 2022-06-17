#include "SDL.h"

#include <time.h>
#include <math.h>
#include <vector>

#define SIZE 25
#define PIXEL 20
#define WINDOW SIZE * PIXEL
#define FPS_CAP 10 // afeta a velocidade do jogo

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct
{
    int x;
    int y;
} Position;

int total = 0;
int direction = Direction::RIGHT;
int yv = 0;     // velocidade y
int xv = PIXEL; // velocidade x

// Position trail[SIZE * SIZE];
std::vector<Position> trail;
Position head = {20, 20};
Position food;


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

    for (Position tail : trail)
    {
        if (tail.x == food.x && tail.y == food.y)
            createFood();
    }
}

void reset()
{
    head = {20, 20};
    direction = Direction::RIGHT;

    total = 0;
    xv = PIXEL;
    yv = 0;

    createFood();
    trail.clear();
}

void update()
{
    if (trail.size() > 0)
    {
        trail.pop_back();
    }

    for (Position tail : trail)
    {
        if (tail.x == head.x && tail.y == head.y)
            reset();
    }

    trail.insert(trail.begin(), head);

    head.x += xv;
    head.y += yv;

    if (head.x > WINDOW || head.y > WINDOW ||
        head.x < 0 || head.y < 0)
        reset();
}

void gameLoop(SDL_Renderer *renderer)
{
    update();

    // render food
    drawPixel(renderer, food.x, food.y, {0xF4, 0x35, 0x7F, 0xFF});

    // render player
    drawPixel(renderer, head.x, head.y, {0xDB, 0xDB, 0xDB, 0xFF});

    // render tail
    for (int i = 0; i < trail.size(); i++)
    {
        Position tail = trail[i];
        drawPixel(renderer, tail.x, tail.y, {0xFF, 0xFF, 0xFF, 0xFF});
    }

    if (head.x == food.x && head.y == food.y)
    {
        createFood();
        trail.push_back(head);
        total++;
    }
}

int SDL_main(int argc, char *argv[])
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
        delta = a - b;

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP && direction != Direction::DOWN)
            {
                direction = Direction::UP;
                xv = 0;
                yv = -PIXEL;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && direction != Direction::RIGHT)
            {
                direction = Direction::LEFT;
                xv = -PIXEL;
                yv = 0;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && direction != Direction::UP)
            {
                direction = Direction::DOWN;
                xv = 0;
                yv = PIXEL;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && direction != Direction::LEFT)
            {
                direction = Direction::RIGHT;
                xv = PIXEL;
                yv = 0;
            }
        }

        if (delta > 1000 / FPS_CAP)
        {
            b = a;
            gameLoop(renderer);
            SDL_RenderPresent(renderer);
        }

        SDL_SetRenderDrawColor(renderer, 0x38, 0x38, 0x38, 0xFF);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
