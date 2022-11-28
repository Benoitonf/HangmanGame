#include "window.h"

void init_window() {
    init(WINDOW_WIDTH, WINDOW_HIGHT);

    // for(int i = 'a'; i <= 'z'; i++) {
    //     //Button key = {.}
    // }

}

void drawGame() {
    clear();

    for(int i = 0; i < 26; i++) {
        draw_button(keys[i]);
    }

    actualize();
}

void gameloop() {

}