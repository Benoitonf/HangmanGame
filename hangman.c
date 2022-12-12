#include "hangman.h"

Game_Status_t game_status;
Result_t game_result;

string pseudo;

file dico;                  // File qui contient tous les mots possible à faire deviner
string word;                // String qui a le mot actuel à deviner
int  attempt_count;         // Compteur du nombre de mauvaise lettre
string guessed;             // String qui contient les lettres déjà trouvées
int  remaining_letters;     // Compteur du nombre de lettre qui reste à trouver dans le mot
string letters_guessed;     // String qui contient toutes les lettres déjà utilisées

char *hangman_sprite;       // Chaîne de caractère qui contient le chemin du sprite du pendu
file scoreboard_file;       // File qui contient le scoreboard
int scoreboard_page = 1;    // Numéro de la page du scoreboard à afficher

/**
 * Mets les lignes du fichier dans la structure file
 * @param path Le chemin du fichier
 * @param file La structure file
*/
void init_file(char *path, file *file) {
    if (Read_File(path, file) != 0) {
        printf("Erreur fichier\n");
        exit(1);
    }
}

// Fonction scoreboard

/**
 * Ajoute le pseudo et son score dans le fichier scoreboard
 * @param pseudo Pointeur vers char
 * @param score Le score du joueur
*/
int add_scoreboard(char *pseudo, int score) {
    // Variable temporaire
    string tmp;
    init_string(&tmp);

    // Ajoute du pseudo et du score avec le format "Pseudo|Score\n"
    append_string(&tmp, pseudo);
    append(&tmp, '|');
    append(&tmp, (char)(score + '0'));
    append(&tmp, '\n');

    // Ecrit la ligne dans le fichier scoreboard
    if (Write_in_File(PATH_SCOREBOARD_FILE, tmp.str) != 0) {
        printf("Impossible d'écrire\n");
        return -1;
    }
    free_string(&tmp);
}

/**
 * Retourne le pseudo depuis une ligne du fichier scoreboard
 * @param line une ligne du fichier scoreboard
*/
char* getPseudo(char *line) {
    string pseudo;
    init_string(&pseudo);

    int i = 0;
    while(line[i] != '|') {
        append(&pseudo, line[i]);
        i++;
    }

    return pseudo.str;
}

/**
 * Retourne le score depuis une ligne du fichier scoreboard
 * @param line une ligne du fichier scoreboard
*/
int getScore(char *line) {
    int j = 0;
    while(line[j] != '|') {
        j++;
    }
    //skip tab char
    j++;
    return line[j] - '0';
}

/**
 * Tri par séléction le fichier src de manière croissante en fonction du score
 * @param src Fichier qui contient les scores
*/
void Sort_by_score(file *src) {
    int i = 0;
    while(i < src->length-1) {
        // Recherche le plus petit score dans tout src, récupère le score et son index
        int score_min = __INT_MAX__, index_min = 0;
        for(int j = i; j < src->length; j++) {
            int current_score = getScore(src->array[j].str);
            if (current_score < score_min) {
                score_min = current_score;
                index_min = j;
            }
        }
        
        // Interverti le string actuel avec le plus petit élément
        swap(&src->array[i], &src->array[index_min]);

        i++;
    }
}

// End fonction scoreboard

/**
 * Initialise le mot à trouver aléatoirement parmis les mots qui sont dans le fichier
*/
void init_word() {
    int random_line = rand() % dico.length;

    copy(&dico.array[random_line], &word);

    remaining_letters = word.char_length;
}

/**
 * Ajoute une tentative et en fonction du nombre de tentative change le sprite du pendu
*/
void add_attempt() {
    if (attempt_count >= TRIES_MAX)
        return;
    attempt_count++;

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
            SetResultGame(LOSE);
            break;
    }
}

// Guessing Fonction

/**
 * Initialise le mot trouvé par le joueur avec des tirets
*/
void init_guessed() {
    for(int i = 0; i < word.char_length; i++) {
        append(&guessed, '-');
    }
}

/**
 * Regarde si la lettre est dans le mot à trouver et retourne 1 si elle est dedans
 * @param c caractère à tester
*/
int is_letter_in_word(char c) {
    int correct_letter = 0;
    
    for(int i = 0; i < word.char_length; i++) {
        if (word.str[i] == c) {
            correct_letter = 1;
            guessed.str[i] = c;
            remaining_letters--;
        }
    }

    return correct_letter;
}

/**
 * Ajoute la lettre dans le tableau des lettres utilisées
 * @param c caractère utilisé
*/
void add_guessed_letter(char c) {
    append(&letters_guessed, c);

    // Si la lettre n'est pas dans le mot alors on ajoute un essai
    if (is_letter_in_word(c) == 0) {
        add_attempt();
    }

    // S'il n'y a plus de lettre à deviner alors c'est gagné
    if (remaining_letters == 0) {
        SetResultGame(WIN);
    }
}

// End guesing Fonction

/**
 * Initialise les différentes variables du jeu et choisi le mot à deviner
*/
void initialise_game() {
    // Initialise les chaines de caractère
    init_string(&pseudo);
    init_string(&guessed);
    init_string(&word);
    init_string(&letters_guessed);

    init_word();            // Choisi un mot aléatoirement
    init_guessed();         // Initialise le mot trouvé avec des underscores

    attempt_count = 0;      // Initialise le nombre d'essai actuel à 0

    game_result = NONE;     // Initialise le résultat de la partie à NONE
}

/**
 * Change la variable du résultat de la partie & ajoute le score au fichier
 * @param result 
*/
void SetResultGame(Result_t result) {
    if (result == NONE)
        return;
    
    game_result = result;
    add_scoreboard(pseudo.str, attempt_count);
    scoreboard_lock = false;
    game_status = RESULT;
}