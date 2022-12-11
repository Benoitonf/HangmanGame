#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <stdio.h>

#include "sdl_function.h"
#include "window.h"
#include "string.h"

typedef struct Button_t Button;

struct Button_t {
    Point pos;
    int width, height;
    bool enable, mouse_over;
    int key_code;
    char *sprite, *sprite_mouseover;
};

extern Button keys[26];
extern Button menu[3];
extern Button result[2];
extern Button scoreboard[4];

void init_buttons();

void draw_button(Button key);

void Mouse_over_buttons(int mouse_x, int mouse_y);

void Check_Button_Click(int mouse_x, int mouse_y);

void DisableButton(char letter);

void Reset_keyboard_buttons();

#endif