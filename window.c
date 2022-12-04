#include "window.h"

int state = 0;

void init_window() {
    init(WINDOW_WIDTH, WINDOW_HIGHT);

    // for(int i = 'a'; i <= 'z'; i++) {
    //     //Button key = {.}
    // }

}

void drawGame() {
    clear();

    char *hangman_sprite;
    switch(state) {
        case 0:
            hangman_sprite = "./assets/Hangman/0.png";
            break;
        case 1:
            hangman_sprite = "./assets/Hangman/1.png";
            break;
        case 2:
            hangman_sprite = "./assets/Hangman/2.png";
            break;
        case 3:
            hangman_sprite = "./assets/Hangman/3.png";
            break;
        case 4:
            hangman_sprite = "./assets/Hangman/4.png";
            break;
        case 5:
            hangman_sprite = "./assets/Hangman/5.png";
            break;
        case 6:
            hangman_sprite = "./assets/Hangman/6.png";
            break;
        case 7:
            hangman_sprite = "./assets/Hangman/7.png";
            break;
    }

    sprite(WINDOW_WIDTH / 2 - 208 / 2, 50, hangman_sprite);

    for(int i = 0; i < 26; i++) {
        draw_button(keys[i]);
    }

    actualize();
}

void gameloop() {

}