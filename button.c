#include "button.h"

#define KEY_SIZE 50
#define KEY_SPACE 20

Button keys[26];
Button menu[3];
Button result[2];
Button scoreboard[4];

void init_scoreboard_buttons() {
    Button menu = {.enable = true, .width = 190, .height = 66, .pos = {.x = 200, .y = 640},
        .sprite = "assets/Scoreboard/menu.png", .sprite_mouseover = "assets/Scoreboard/menu_over.png"};
    Button exit = {.enable = true, .width = 190, .height = 66, .pos = {.x = 590, .y = 640},
        .sprite = "assets/Scoreboard/exit.png", .sprite_mouseover = "assets/Scoreboard/exit_over.png"};
    Button previous = {.enable = true, .width = 210, .height = 52, .pos = {.x = 86, .y = 555},
        .sprite = "assets/Scoreboard/previous.png", .sprite_mouseover = "assets/Scoreboard/previous.png"};
    Button next = {.enable = true, .width = 210, .height = 52, .pos = {.x = 683, .y = 555},
        .sprite = "assets/Scoreboard/next.png", .sprite_mouseover = "assets/Scoreboard/next.png"};

    scoreboard[0] = menu;
    scoreboard[1] = exit;
    scoreboard[2] = previous;
    scoreboard[3] = next;
}

void init_result_buttons() {
    Button menu = {.enable = true, .width = 190, .height = 66, .pos = {.x = 200, .y = 640},
        .sprite = "assets/Result/menu.png", .sprite_mouseover = "assets/Result/menu_over.png"};
    Button exit = {.enable = true, .width = 190, .height = 66, .pos = {.x = 590, .y = 640},
        .sprite = "assets/Result/exit.png", .sprite_mouseover = "assets/Result/exit_over.png"};

    result[0] = menu;
    result[1] = exit;
}

void init_menu_buttons() {
    Button new_game = {.enable = true, .width = 369, .height = 84, .pos = {.x = 306, .y = 310},
        .sprite = "assets/Menu/newgame.png", .sprite_mouseover = "assets/Menu/newgame_over.png"};
    Button scoreboard = {.enable = true, .width = 369, .height = 84, .pos = {.x = 306, .y = 418},
        .sprite = "assets/Menu/scoreboard.png", .sprite_mouseover = "assets/Menu/scoreboard_over.png"};
    Button exit = {.enable = true, .width = 369, .height = 84, .pos = {.x = 306, .y = 528},
        .sprite = "assets/Menu/exit.png", .sprite_mouseover = "assets/Menu/exit_over.png"};

    menu[0] = new_game;
    menu[1] = scoreboard;
    menu[2] = exit;
}

void init_keyboard_buttons() {
    for(int i = 0; i < 26; i++) {
        Button key = {.height = 50, .width = 50, .key_code = 'a' + i, .mouse_over = false, .enable = true};
        
        int key_x = 150 + (key.width + 20) * (i%10);
        if (i >= 20) {
            key_x += (key.width + 20) * 2;
        }
        key.pos.x = key_x;
        key.pos.y = WINDOW_HIGHT - (key.height + KEY_SPACE) * (3 - (i/10));

        asprintf(&key.sprite, "./assets/Keys/Light/%c-Key.png", key.key_code - 32);
        asprintf(&key.sprite_mouseover, "./assets/Keys/Dark/%c-Key.png", key.key_code - 32);

        keys[i] = key;
    }
}

void init_buttons() {
    init_menu_buttons();
    init_keyboard_buttons();
    init_result_buttons();
    init_scoreboard_buttons();
}

void draw_button(Button key) {
    if (key.mouse_over || !key.enable) {
        sprite(key.pos.x, key.pos.y, key.sprite_mouseover);
    }
    else {
        sprite(key.pos.x, key.pos.y, key.sprite);
    }
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
    int i = 0;
    bool key_find = false;
    switch(game_status) {
        case MENU_SELECT:
            while(!key_find && i < 3) {
                if (menu[i].enable) {
                    menu[i].mouse_over = Check_Intersection(menu[i].pos.x, menu[i].pos.y, menu[i].width, menu[i].height, mouse_x, mouse_y);
                    key_find = menu[i].mouse_over;
                }
                i++;
            }
            break;
        case GAME:
            while(!key_find && i < 26) {
                if (keys[i].enable) {
                    keys[i].mouse_over = Check_Intersection(keys[i].pos.x, keys[i].pos.y, keys[i].width, keys[i].height, mouse_x, mouse_y);
                    key_find = keys[i].mouse_over;
                }
                i++;
            }
            break;
        case RESULT:
            while(!key_find && i < 2) {
                if (result[i].enable) {
                    result[i].mouse_over = Check_Intersection(result[i].pos.x, result[i].pos.y, result[i].width, result[i].height, mouse_x, mouse_y);
                    key_find = result[i].mouse_over;
                }
                i++;
            }
            break;
        case SCOREBOARD:
            while(!key_find && i < 4) {
                if (scoreboard[i].enable) {
                    scoreboard[i].mouse_over = Check_Intersection(scoreboard[i].pos.x, scoreboard[i].pos.y, scoreboard[i].width, scoreboard[i].height, mouse_x, mouse_y);
                    key_find = scoreboard[i].mouse_over;
                }
                i++;
            }
            break;
    }
}

void Click_Keyboard_Button(Button* btn) {
    if (!btn->enable)
        return;
    
    add_guessed_letter(btn->key_code);

    btn->enable = false;
    btn->mouse_over = false;
}

void Check_Button_Click(int mouse_x, int mouse_y) {
    switch(game_status) {
        case MENU_SELECT:
            if (menu[0].mouse_over) {
                game_status = ASK_PSEUDO;
                menu[0].mouse_over = false;

                Reset_keyboard_buttons();
                initialise_game();
            }
            else if (menu[1].mouse_over) {
                scoreboard_page = 1;
                scoreboard_lock = false;
                game_status = SCOREBOARD;
                menu[1].mouse_over = false;

                if (access(PATH_SCOREBOARD_FILE, F_OK) != 0) { // Le fichier n'existe pas
                    return;
                }

                init_file(PATH_SCOREBOARD_FILE, &scoreboard_file);
                Sort_by_score(&scoreboard_file); // Tri le scoreboard
            }
            else if (menu[2].mouse_over) {
                freeAndTerminate();
            }

            break;
        case GAME:
            for(int i = 0; i < 26; i++) {
                if (keys[i].enable && keys[i].mouse_over) {
                    Click_Keyboard_Button(&keys[i]);
                }
            }
            break;
        case RESULT:
            if (result[0].mouse_over) {
                game_result = NONE;
                game_status = MENU_SELECT;
                result[0].mouse_over = false;
            }
            else if (result[1].mouse_over) {
                freeAndTerminate();
            }
            break;
        case SCOREBOARD:
            if (scoreboard[0].mouse_over) {
                game_status = MENU_SELECT;
                result[0].mouse_over = false;
            } else if (scoreboard[1].mouse_over) {
                freeAndTerminate();
            } else if (scoreboard[2].mouse_over) {
                if (scoreboard_page > 1) {
                    scoreboard_page--;
                    scoreboard_lock = false;
                }
            } else if (scoreboard[3].mouse_over) {
                if (scoreboard_page < ((scoreboard_file.length / 10))) {
                    scoreboard_page++;
                    scoreboard_lock = false;
                }
            }
            break;
    }
    
}

void DisableButton(char letter) {
    if (letter < 'a' || letter > 'z') {
        return;
    }

    Click_Keyboard_Button(&keys[letter - 'a']);
}

void Reset_keyboard_buttons() {
    for(int i = 0; i < 26; i++) {
        keys[i].enable = true;
        keys[i].mouse_over = false;
    }
}