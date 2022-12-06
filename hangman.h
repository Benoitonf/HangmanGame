#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "file.h"
#include "string.h"

#define TRIES_MAX 8 // Nombre d'essai max
#define PATH_WORDS_FILE "words.txt" // Chemin du fichier qui contient les mots
#define PATH_SCOREBOARD_FILE "scoreboard.txt" // Chemin du fichier qui contient les résultats
#define SCOREBOARD_LENGTH 10 // Nombre de ligne à afficher dans le tableau des scores

extern string pseudo;

extern file dico;
extern string word;
extern int  attempt_count; 
extern string guessed;
extern int  remaining_letters;
extern string letters_guessed;

extern char *hangman_sprite;

void init_file(char *path, file *file);

int add_scoreboard(char *pseudo, int score);

int getScore(char *line);

void Sort_by_score(file *src);

void printScoreboard();

void setPseudo();

void init_word();

void add_attempt();

void init_guessed();

int is_letter_in_word(char c);

void add_guessed_letter(char c);

void initialise_game();

void game_hangman();

#endif