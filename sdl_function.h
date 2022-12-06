#ifndef SDL_FUNCTION
#define SDL_FUNCTION

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

void sprite(int posX, int posY, char *imgBMPSrc);

void write_text(int posX, int posY, char *text);

#endif