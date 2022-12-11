#include "window.h"

bool scoreboard_lock = false;
scoreboard_t sorted[10];
int max_line;

void init_window() {
    init(WINDOW_WIDTH, WINDOW_HIGHT);

    game_status = MENU_SELECT;
}

void draw_Menu() {
    sprite(0,0, "assets/Menu/menu.png");

    for(int i = 0; i < 3; i++) {
        draw_button(menu[i]);
    }
}

void draw_AskPseudo() {
    sprite(0, 0, "assets/Ask_Pseudo.png");

    if (pseudo.char_length > 0)
        write_text(WINDOW_WIDTH/2, 467, pseudo.str, 44, SDL_TRUE);
}

void draw_Game() {
    sprite(0,0, "assets/Game.png");

    if (attempt_count != 0)
        sprite(388, 140, hangman_sprite);

    for(int i = 0; i < 26; i++) {
        draw_button(keys[i]);
    }

    write_text(20, 10, pseudo.str, 44, SDL_FALSE);
    write_text(20, 100, word.str, 44, SDL_FALSE);

    write_text(490, 407, guessed.str, 44, SDL_TRUE);
}

void draw_Result() {
    sprite(0, 0, "assets/Result/Result.png");
    if (game_result == WIN) {
        sprite(64, 120, "assets/Result/win.png");
    }
    else {
        sprite(64, 120, "assets/Result/lose.png");
    }

    char score[2];
    sprintf(score, "%d", attempt_count);

    write_text(500, 310, pseudo.str, 40, SDL_FALSE);
    write_text(500, 391, score, 40, SDL_FALSE);

    write_text(500, 470, word.str, 40, SDL_FALSE);
    write_text(500, 550, guessed.str, 40, SDL_FALSE);

    for(int i = 0; i < 2; i++) {
        draw_button(result[i]);
    }
}

void scoreboard_parsing() {
    string num_place, name_score;
    init_string(&num_place);
    init_string(&name_score);

    int i = (scoreboard_page - 1) * 10;
    while(i < (scoreboard_page * 10) && i < scoreboard_file.length) {
        string current_line = scoreboard_file.array[i];

        if (i < 9) {
            append(&num_place, i + '1');
        }
        else {
            if (i % 10 == 9)
                append(&num_place, i/10 + '1');
            else
                append(&num_place, i/10 + '0');
            append(&num_place, (i+1)%10 + '0');
        }

        append_string(&name_score, getPseudo(current_line.str));
        append_string(&name_score, " (");
        append(&name_score, getScore(current_line.str) + '0');
        append(&name_score, ')');

        scoreboard_t tmp;
        init_string(&tmp.nameScore);
        init_string(&tmp.place_num);
        copy(&num_place, &tmp.place_num);
        copy(&name_score, &tmp.nameScore);
        sorted[i % 10] = tmp;

        dump(&num_place);
        dump(&name_score);
        i++;
    }
    max_line = i;

    free_string(&num_place);
    free_string(&name_score);
}

void draw_Scoreboard() {
    sprite(0, 0, "assets/Scoreboard/scoreboard.png");

    for(int i = 0; i < 4; i++) {
        draw_button(scoreboard[i]);
    }

    if (scoreboard_file.length == 0) {
        return;
    }

    if (!scoreboard_lock) {
        scoreboard_lock = true;
        scoreboard_parsing();
    }

    for(int i = (scoreboard_page - 1) * 10; i < max_line; i++) {
        int x_place = 108, x_nameScore = 163;
        int y = 139 + (84*(i % 5));
        
        if (i % 10 > 4) { //Deuxième colonne
            x_nameScore = 598;
            if (i < 9) {
                x_place = 545;
            }
            else {
                x_place = 536;
            }
        } 
        else {
            if (i > 9) {
                x_place = 99;
            }
        }

        scoreboard_t tmp = sorted[i % 10];
        
        write_text(x_place, y, tmp.place_num.str, 30, SDL_FALSE);
        write_text(x_nameScore, y, tmp.nameScore.str, 30, SDL_FALSE);
    }


    string num_page;
    init_string(&num_page);
    append(&num_page, scoreboard_page + '0');
    append(&num_page, '/');
    append(&num_page, scoreboard_file.length / 10 + (scoreboard_file.length % 10 == 0 ? '0' : '1'));
    write_text(490, 555, num_page.str, 30, SDL_TRUE);

    free_string(&num_page);
}

void drawGame() {
    clear();

    switch(game_status) {
        case MENU_SELECT:
            draw_Menu();
            break;
        case ASK_PSEUDO:
            draw_AskPseudo();
            break;
        case GAME:
            draw_Game();
            break;
        case RESULT:
            draw_Result();
            break;
        case SCOREBOARD:
            draw_Scoreboard();
            break;
    }

    actualize();
}