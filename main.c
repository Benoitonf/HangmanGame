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

string pseudo;

file dico; // File qui contient tous les mots possible à faire deviner
string word; // String qui a le mot actuel à deviner
int  attempt_count; // Compteur du nombre de mauvais lettre
string guessed; // String qui contient les lettres déjà trouvées
int  remaining_letters; // Compteur du nombre de lettre qui reste à trouver dans le mot
string letters_guessed; // string qui contient toutes les lettres déjà utilisées

char hangman_body[6]; // Tableau du corps du pendu

//

/**
 * Mets les lignes de texte du fichier dans la structure file
 * @param path Le chemin du fichier
 * @param file La structure file
*/
void init_file(char *path, file *file) {
    if (Read_File(path, file) != 0) {
        printf("Erreur fichier\n");
        exit(1);
    }
}

/**
 * Enlève le caractère retour à la ligne dans le buffer de getchar
*/
void clean_buffer() {
    int c=0;
    while (c != '\n' && c != EOF) {
        c=getchar();
    }
}

/**
 * Retourne un caractère différent du retour à la ligne et de EOF
*/
char GetLetter() {
    char letter;

    do {
        letter = getchar();
    } while (letter == '\n' || letter == EOF);
    
    clean_buffer();

    return letter;
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
 * Tri le fichier src de manière croissante en fonction du score
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

/**
 * Affiche les SCOREBOARD_LENGTH premiers scores
*/
void printScoreboard() {
    if (access(PATH_SCOREBOARD_FILE, F_OK) != 0) { // Le fichier n'existe pas
        printf("Aucun score enregistré.\n");
        return;
    }

    file scoreboard;
    init_file(PATH_SCOREBOARD_FILE, &scoreboard);
    Sort_by_score(&scoreboard); // Tri le scoreboard

    int pseudo_length = 0;
    int i = 0;
    // Recherche la taille du pseudo qui à le plus de caractère dans les premiers
    while (i < SCOREBOARD_LENGTH && i < scoreboard.length) {
        int len = 0;
        while(scoreboard.array[i].str[len] != '|') {
            len++;
        }
        if (len > pseudo_length) {
            pseudo_length = len;
        }
        i++;
    }

    if (pseudo_length < 8)
        pseudo_length = 8;

    // Créer l'entête du scoreboard à la bonne taille
    printf("+----+-%s-+-------+\n", repeatCharacter('-', pseudo_length));
    printf("|    | Pseudo   %s| Score |\n", repeatCharacter(' ', pseudo_length - 8));
    printf("+----+-%s-+-------+\n", repeatCharacter('-', pseudo_length));

    i = 0;
    // Parcours les premières lignes du scoreboard trié pour les afficher
    while(i < SCOREBOARD_LENGTH && i < scoreboard.length) {
        printf("| %2d | ", i + 1); // Affiche la place
        int j = 0;
        while(scoreboard.array[i].str[j] != '|') { // Affiche le pseudo
            printf("%c", scoreboard.array[i].str[j]);
            j++;
        }
        printf("%s", repeatCharacter(' ', pseudo_length - j)); // Rempli d'espace si le pseudo est trop petit
        j++; //skip pipe char

        printf(" |   %c   |\n", scoreboard.array[i].str[j]); // Affiche le score
        i++;
    }
    printf("+----+-%s-+-------+\n", repeatCharacter('-', pseudo_length)); // Ferme le scoreboard

    printf("[%d/%d]\n", i, scoreboard.length); // Affiche le nombre de ligne afficher et le nombre de résultat en tout
}

// End fonction scoreboard

// Fonction Joueur

/**
 * Demande le nom du joueur
*/
void setPseudo() {
    do {
        system("clear");
        dump(&pseudo); // Vide la variable si on refait une partie
        printf("Quel est votre pseudo ? (3 lettres min)\n");

        char letter;
        while ((letter = getchar()) != '\n') {
            if (letter != '|') // Ignore le caractère '|' car il sert de séparateur pour le score dans le fichier
                append(&pseudo, letter);
        }
    } while (pseudo.char_length < 3); // Redemande un pseudo s'il y a moins de 3 lettres
}

// Fin Fonction Joueur

// Fonction Mot à chercher

/**
 * Initialise le mot à trouver aléatoirement parmis les mots qui sont dans le fichier
*/
void init_word() {
    int random_line = rand() % dico.length;

    copy(&dico.array[random_line], &word);

    remaining_letters = word.char_length;
}

/**
 * Affiche le word à trouver
*/
void printWord() {
    printf("Le mot à trouver était : %s (Nombre de lettre %d)\n", word.str, word.char_length);
}

// End Fonction Mot à chercher

// Fonction Hangman

/**
 * Affiche le pendu en fonction du nombre de tentative
*/
void printHangman() {
    system("clear");
    if (attempt_count >= 2) {
        printf("    ____       \n");
        printf("   |    |      \n");
        printf("   |    %c     \n", hangman_body[0]);
        printf("   |   %c%c%c  \n", hangman_body[1], hangman_body[2], hangman_body[3]);
        printf("   |    %c     \n", hangman_body[2]);
        printf("   |   %c %c   \n", hangman_body[4], hangman_body[5]);
        printf("  _|_          \n");
    }
    if (attempt_count >= 1) {
        if (attempt_count == 1)
            printf("  ___          \n");
        printf(" |   |_______    \n");
        printf(" |           |   \n");
        printf(" |___________|   \n");
        printf("                 \n");
    }
}

/**
 * Initialise le tableau du corps du pendu
*/
void init_body() {
    for(int i = 0; i < 6; i++)
        hangman_body[i] = ' ';
}

/**
 * Ajoute une tentative et en fonction du nombre de tentative ajoute une partie du corps au pendu
*/
void add_attempt() {
    attempt_count++;

    switch(attempt_count) {
        case 3:
            hangman_body[0] = 'o';
            break;
        case 4:
            hangman_body[1] = '/';
            break;
        case 5:
            hangman_body[2] = '|';
            break;
        case 6:
            hangman_body[3] = '\\';
            break;
        case 7:
            hangman_body[4] = '/';
            break;
        case 8:
            hangman_body[5] = '\\';
            break;
    }
}

// End Fonction Hangman

// Guessing Fonction

/**
 * Initialise le mot avec les lettres trouvées
*/
void init_guessed() {
    for(int i = 0; i < word.char_length; i++) {
        append(&guessed, '_');
    }
}

/**
 * Affiche le mot avec les lettres trouvées
*/
void printGuessed() {
    printf("Lettre trouvée : %s (Nombre de lettre %d)\n", guessed.str, guessed.char_length);
}

/**
 * Affiche les lettres utilisées dans la partie
*/
void printLetters() {
    printf("Lettres utilisées : ");

    for(int i = 0; i < letters_guessed.char_length; i++) {
        printf("%c, ",letters_guessed.str[i]);
    }

    printf("\n");
}

/**
 * Regarde si la lettre est dans le mot à trouver et retourne 1 si c'est dedans
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
}

/**
 * Retourne 1 si la lettre est déjà utilisée
 * @param c caractère à tester
*/
int already_Guessed(char c) {
    int i = 0;
    int found = 0;

    while (i < letters_guessed.char_length && found != 1) {
        if (c == letters_guessed.str[i])
            found = 1;
        i++;
    }

    return found;
}

/**
 * Demande une lettre entre a et z et qui n'est pas déjà utilisée
*/
void guess_Letter() {
    char letter;
    printf("Proposition de lettre : ");

    do {
        letter = GetLetter();
    } while ((letter < 'a' || letter > 'z') || already_Guessed(letter));

    add_guessed_letter(letter);
}

// End guesing Fonction

/**
 * Initialise les différentes variables du jeu, demande le pseudo et choisi le mot à deviner
*/
void initialise_game() {
    // Initialise les chaines de caractère
    init_string(&pseudo);
    init_string(&guessed);
    init_string(&word);
    init_string(&letters_guessed);
    
    // Demande le pseudo
    setPseudo();

    init_word(); // Choisi un mot aléatoirement
    init_body(); // Initialise le corps du pendu
    init_guessed(); // Initialise le mot trouvé avec des underscores

    attempt_count = 0; // Initialise le nombre d'essai actuel à 0
}

/**
 * Boucle du jeu
*/
void game_hangman() {
    initialise_game();

    // Tant qu'on a pas perdu ou gagné
    while(attempt_count < TRIES_MAX && remaining_letters != 0) {
        printHangman();

        printWord();
        printLetters();
        printGuessed();

        guess_Letter();
    }

    if (remaining_letters == 0) { // Victoire
        printf("Félicitation, %s tu as trouvé '%s' en %d lettres\n", pseudo.str, word.str, letters_guessed.char_length);
    }
    else { // Défaite
        printHangman();
        printf("Perdu, %s le mot était '%s'\n", pseudo.str, word.str);
    }

    add_scoreboard(pseudo.str, attempt_count); // Ajoute le résultat dans le scoreboard
    printf("\nAppuyer sur Entrée pour continuer ...");
    getchar();
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char *path = PATH_WORDS_FILE;

    // Si on veut donner un autre fichier
    if (argc > 1) {
        if (access(argv[1], F_OK) == 0) { // Si le fichier existe
            path = argv[1]; // On change le nom du fichier qui contient les mots
        }
    }

    init_file(path, &dico); // Initialise le fichier

    char choice;
    do {
        system("clear");
        printf("Quelle action faire ?\n");
        printf("\t- 1 : Jeu du pendu\n");
        printf("\t- 2 : Voir le TOP %d\n", SCOREBOARD_LENGTH);
        printf("\t- 0 : Exit\n");

        choice = GetLetter();

        switch(choice) {
            case '1':
                game_hangman();
                break;
            case '2':
                system("clear");
                printScoreboard();
                printf("\nAppuyer sur Entrée pour continuer ...");
                getchar();
                break;
        }
    } while(choice != '0');

    free_string(&pseudo);
    free_string(&guessed);
    free_string(&word);
    free_string(&letters_guessed);
    free_file(&dico);
}