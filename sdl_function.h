#ifndef SDL_FUNCTION
#define SDL_FUNCTION

#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct Point {
    double x;
    double y;
} Point;

void init(int windowWidth, int windowHeight);

void freeWindow();

void freeRenderer();

void freeTexture(SDL_Texture *texture);

void freeAndTerminate();

void actualize();

void clear();

void changeColor(int r, int g, int b);

void drawSquare(int posX, int posY, int longueur);

#endif