#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "file.h"
#include "string.h"
#include "window.h"

#define TRIES_MAX 8                             // Nombre d'essai max
#define PATH_WORDS_FILE "words.txt"             // Chemin du fichier qui contient les mots
#define PATH_SCOREBOARD_FILE "scoreboard.txt"   // Chemin du fichier qui contient les résultats
#define PSEUDO_LENGTH_MAX 14                    // Taille max du pseudo

typedef enum {
    MENU_SELECT,
    ASK_PSEUDO,
    GAME,
    RESULT,
    SCOREBOARD
} Game_Status_t;

typedef enum {
    NONE,
    WIN,
    LOSE
} Result_t;

typedef struct {
    string place_num, nameScore;
}scoreboard_t;

extern Game_Status_t game_status;
extern Result_t game_result;

extern string pseudo;

extern file dico;
extern string word;
extern int attempt_count; 
extern string guessed;
extern int remaining_letters;
extern string letters_guessed;

extern char *hangman_sprite;
extern file scoreboard_file;
extern int scoreboard_page;

void init_file(char *path, file *file);

int add_scoreboard(char *pseudo, int score);

char* getPseudo(char *line);

int getScore(char *line);

void Sort_by_score(file *src);

void init_word();

void add_attempt();

void init_guessed();

int is_letter_in_word(char c);

void add_guessed_letter(char c);

void initialise_game();

void SetResultGame(Result_t result);

#endif