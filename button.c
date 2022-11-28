#include "button.h"

#define KEY_SIZE 50

Button keys[26];

void init_buttons() {
    //space 130 left/right
    //width 50
    //space between key 20
    for(int i = 0; i < 26; i++) {
        Button key = {.height = 50, .width = 50, .key_code = 'a' + i, .mouse_over = false, .enable = true};
        
        key.pos.x = 130 + (key.width + 20) * (i%10);
        if (i < 10) {
            key.pos.y = WINDOW_HIGHT - (key.height + 30) * 3;
        }
        else if (i < 20) {
            key.pos.y = WINDOW_HIGHT - (key.height + 30) * 2;
        }
        else {
            key.pos.y = WINDOW_HIGHT - (key.height + 30);
        }

        keys[i] = key;
    }
}

void draw_button(Button key) {
    if (key.enable) {
        if (key.mouse_over) {
            changeColor(50,90,140);
        } else {
            changeColor(100,50,40);
        }
    }
    else {
        changeColor(80,80,80);
    }
    
    drawSquare(key.pos.x, key.pos.y, key.height);

    //printf("%c - x : %3f | y : %3f\n", key.key_code, key.pos.x, key.pos.y);
}

/**
 * Check that the two objects intersect
 * @param x1
 * @param y1
 * @param w1
 * @param h1
 * @param x2
 * @param y2
 * @param w2
 * @param h2
*/
bool Check_Intersection(double x1, double y1, int w1, int h1, double x2, double y2) {
    if (x1 <= x2 && (x1 + w1 >= x2) && y1 <= y2 && (y1 + h1 >= y2)) {
        return true;
    }
    return false;
}

void Mouse_over_buttons(int mouse_x, int mouse_y) {
    for(int i = 0; i < 26; i++) {
        if (keys[i].enable) {
            keys[i].mouse_over = Check_Intersection(keys[i].pos.x, keys[i].pos.y, keys[i].width, keys[i].height, mouse_x, mouse_y);
        }
    }
}

void Click_Button(int mouse_x, int mouse_y) {
    for(int i = 0; i < 26; i++) {
        if (keys[i].enable && keys[i].mouse_over) {
            //printf("Click on %c key\n", keys[i].key_code);
            keys[i].enable = false;
            keys[i].mouse_over = false;
        }
    }
}