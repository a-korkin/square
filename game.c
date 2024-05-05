#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "./game.h"
#include "./square.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool running = false;
Square square = { 
    .size = STEP,
    .position = { .x = 0, .y = 0 }, 
    .direction = { .x = 1, .y = 1 },
    .color = { .r = 0xFF, .g = 0x00, .b = 0x00, .a = 0xFF },
};
size_t last_frame_time = 0;

void init(void) {
    running = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error init SDL: %s", SDL_GetError());
        running = false;
    }

    window = SDL_CreateWindow(
            "Square", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            SCREEN_WIDTH, 
            SCREEN_HEIGTH, 
            SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Error creating window: %s", SDL_GetError());
        running = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Error creating renderer: %s", SDL_GetError());
        running = false;
    }
    srand(time(NULL));
}

void handle_event(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        printf("quit\n");
        running = false;
    }
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: square.position.y -= STEP; break;
            case SDLK_RIGHT: square.position.x += STEP; break;
            case SDLK_DOWN: square.position.y += STEP; break;
            case SDLK_LEFT: square.position.x -= STEP; break;
        }
    }
}

void change_color_square(void) {
    square.color.r = rand() % 255;
    square.color.g = rand() % 255;
    square.color.b = rand() % 255;
}

void update(void) {
    size_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    
    square.position.x += square.direction.x * SPEED * delta_time;
    square.position.y += square.direction.y * SPEED * delta_time;

    if (square.position.x + square.size >= SCREEN_WIDTH) {
        square.direction.x = -1;
        change_color_square();
    }
    if (square.position.x <= 0) {
        square.direction.x = 1;
        change_color_square();
    }
    if (square.position.y + square.size >= SCREEN_HEIGTH) {
        square.direction.y = -1;
        change_color_square();
    }
    if (square.position.y <= 0) {
        square.direction.y = 1;
        change_color_square();
    }
}

void draw_square(void) {
    SDL_SetRenderDrawColor(
            renderer, 
            square.color.r, square.color.g, square.color.b, square.color.a);
    SDL_Rect rect = { 
        .x = square.position.x, 
        .y = square.position.y, 
        .w = square.size,
        .h = square.size,
    };
    SDL_RenderFillRect(renderer, &rect);
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    draw_square();

    SDL_RenderPresent(renderer);
}

void loop(void) {
    while (running) {
        handle_event();
        update();
        render();
    }
}

void quit(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    init();
    loop();
    quit();
    return 0;
}

