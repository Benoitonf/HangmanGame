#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

#include "sdl_function.h"
#include "window.h"

typedef struct Button_t Button;

struct Button_t {
    Point pos;
    int width, height;
    bool enable, mouse_over;
    int key_code;
};

extern Button keys[26];

void init_buttons();

void draw_button(Button key);

void Mouse_over_buttons(int mouse_x, int mouse_y);

void Click_Button(int mouse_x, int mouse_y);

#endif