#include "window.h"

void init_window() {
    init(WINDOW_WIDTH, WINDOW_HIGHT);

    // for(int i = 'a'; i <= 'z'; i++) {
    //     //Button key = {.}
    // }

}

void drawGame() {
    clear();

    char *hangman_sprite;
    switch(attempt_count) {
        case 1:
            hangman_sprite = "./assets/Hangman/0.png";
            break;
        case 2:
            hangman_sprite = "./assets/Hangman/1.png";
            break;
        case 3:
            hangman_sprite = "./assets/Hangman/2.png";
            break;
        case 4:
            hangman_sprite = "./assets/Hangman/3.png";
            break;
        case 5:
            hangman_sprite = "./assets/Hangman/4.png";
            break;
        case 6:
            hangman_sprite = "./assets/Hangman/5.png";
            break;
        case 7:
            hangman_sprite = "./assets/Hangman/6.png";
            break;
        case 8:
            hangman_sprite = "./assets/Hangman/7.png";
            break;
    }

    if (attempt_count != 0)
        sprite(WINDOW_WIDTH / 2 - 208 / 2, 50, hangman_sprite);

    for(int i = 0; i < 26; i++) {
        draw_button(keys[i]);
    }

    write_text(20, 20, "Pseudo:");
    write_text(20, 60, word.str);

    int pos_x_guess = WINDOW_WIDTH/2 - (30 * guessed.char_length)/2;
    int pos_y_guess = WINDOW_HIGHT/2;

    write_text(pos_x_guess, pos_y_guess, guessed.str);

    actualize();
}

void gameloop() {

}