#ifndef WINDOW_H
#define WINDOW_H

#include "button.h"
#include "sdl_function.h"
#include "hangman.h"

#define WINDOW_WIDTH 980
#define WINDOW_HIGHT 720

extern bool scoreboard_lock;

void init_window();

void draw_window();

void gameloop();

#endif