#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>


// Define screen dimensions
#define SCREEN_WIDTH   650
#define SCREEN_HEIGHT   800


void Lgen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x88, 0xFF);

    int xPos[4] = {x, x, x, x + 40};
    int yPos[4] = {y, y+40, y+80, y+80};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = xPos[i];
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }

}

void LRgen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0x88, 0x00, 0x88, 0xFF);

    int xPos[4] = {x, x, x, x - 40};
    int yPos[4] = {y, y+40, y+80, y+80};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = xPos[i];
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }

}

void Igen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0x00, 0xDD, 0xDD, 0xFF);

    int yPos[4] = {y, y+40, y+80, y+120};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = x;
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }

}

void Sgen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0xDD, 0xDD, 0x00, 0xFF);

    int xPos[4] = {x, x+40, x, x + 40};
    int yPos[4] = {y, y, y+40, y+40};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = xPos[i];
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }
}

void Zgen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0x88, 0x00, 0x00, 0xFF);

    int xPos[4] = {x, x+40, x+40, x + 80};
    int yPos[4] = {y, y, y+40, y+40};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = xPos[i];
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }
}

void ZRgen(SDL_Renderer *renderer, int x, int y) {
    // Declare rect of square
    SDL_Rect rectList[4];

    SDL_SetRenderDrawColor(renderer, 0xAA, 0x22, 0x22, 0xFF);

    int xPos[4] = {x, x+40, x+40, x + 80};
    int yPos[4] = {y+40, y+40, y, y};

    for (int i = 0; i < 4; i++) {
        rectList[i].x = xPos[i];
        rectList[i].y = yPos[i];
        rectList[i].w = 40;
        rectList[i].h = 40;
        SDL_RenderFillRect(renderer, &rectList[i]);
    }
}

int gen(){
    int piece[6] = {1, 2, 3, 4, 5, 6};
/*
 *  1 square
 *  2 L
 *  3 LR
 *  4 Z
 *  5 ZR
 *  6 I
 */

    int p = rand() % 6;
    int gen = piece[p];

    return gen;
}


int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    // iniciar semilla de numeros pseudoaleatorios
    srand(time(NULL));

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    int FPS = 60;

    const int DELAY_TIME = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // Create window
    SDL_Window *window = SDL_CreateWindow("Tetris",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            printf("Renderer could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Declare rect of square
            SDL_Rect squareRect;

            // Square dimensions
            squareRect.w = 250;
            squareRect.h = 800;

            // Square position
            squareRect.x = 400;
            squareRect.y = 0;

            bool generated = false;
            int piece = 1;
            int pos = 0;
            int step = 0;

            bool up = false;
            bool down = false;
            bool left = false;
            bool right = true;

            // Event loop exit flag
            bool quit = false;

            SDL_bool a_pressed = SDL_FALSE;
            SDL_bool s_pressed = SDL_FALSE;
            SDL_bool d_pressed = SDL_FALSE;
            SDL_bool w_pressed = SDL_FALSE;

            SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
            SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
            SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
            SDL_EventState(SDL_MOUSEWHEEL, SDL_IGNORE);

            // Event loop
            while(!quit) {
                frameStart = SDL_GetTicks();
                SDL_Event e;

                while (SDL_PollEvent(&e)) {

                    // User requests quit
                    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                        quit = true;
                    }
                }


                // 0x declares hex number   FF= 255
                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
                // Clear screen
                SDL_RenderClear(renderer);


                SDL_SetRenderDrawColor(renderer, 0x99, 0x99, 0x99, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(renderer, &squareRect);

                step = SDL_GetTicks64() / 1000;
                step *= 40;

                if (!generated) {
                    piece = gen();
                    generated = true;
                }

                if (generated) {
                        switch (piece) {
                            case 1: {
                                Sgen(renderer, 200, step);
                                break;
                            }
                            case 2: {
                                Lgen(renderer, 200, step);
                                break;
                            }
                            case 3: {
                                LRgen(renderer, 200, step);
                                break;
                            }
                            case 4: {
                                Zgen(renderer, 180, step);
                                break;
                            }
                            case 5: {
                                ZRgen(renderer, 180, step);
                                break;
                            }
                            case 6: {
                                Igen(renderer, 200, step);
                                break;
                            }
                            default: {
                                printf("Piece could not be created!\n");
                            }
                        }
                }

                if (step == 800) {
                    generated = false;
                }

                // Update screen
                SDL_RenderPresent(renderer);


                frameTime = SDL_GetTicks64() - frameStart;

                // Esperar el tiempo restante hasta alcanzar el frame rate deseado
                if (frameTime < DELAY_TIME) {
                    SDL_Delay(DELAY_TIME - frameTime);
                }
            }

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    SDL_Quit();


    return 0;
}