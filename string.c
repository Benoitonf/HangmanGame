#include "string.h"

/**
 * Initialise la structure string, alloue la mémoire pour str, met char_length = 0 & met un '\0' dans str
 * @param s Pointeur d'une structure string
*/
void init_string(string *s) {
    if (s == NULL) {
        s = malloc(sizeof(string));
    }
    s->char_length = 0;
    s->str = malloc(sizeof(char));
    s->str[0] = '\0';
}

/**
 * Ajoute la place d'un caractère dans la mémoire de str
 * @param s Pointeur d'une structure string
*/
void add_size(string *s) {
    if (s->str == NULL) {
        return;
    }
    
    s->char_length++;
    s->str = realloc(s->str, sizeof(char) * (s->char_length + 1));
}

/**
 * Vide la structure string, libère la mémoire de str et réinitialise string
 * @param s Pointeur d'une structure string
*/
void dump(string *s) {
    if (s != NULL) {
        free_string(s);
        init_string(s);
    }
}

/**
 * Libère la mémoire de str dans la string
 * @param s Pointeur d'une structure string
*/
void free_string(string *s) {
    if (s != NULL) {
        free(s->str);
        s->str = NULL;
        s->char_length = 0;
    }
}

/**
 * Ajoute un caractère dans str de la string
 * @param s Pointeur d'une structure string
*/
void append(string *s, char c) {
    if (s == NULL) {
        return;
    }
    
    insert(s, s->char_length, c);
}

/**
 * Ajoute la chaine de caractère dans str de la string
 * @param s Pointeur d'une structure string
 * @param string La chaine de caractère à ajouter
*/
void append_string(string *s, char *string) {
    if (s == NULL) {
        return;
    }

    int i = 0;
    while (string[i] != '\0') {
        append(s, string[i]);
        i++;
    }
}

/**
 * Insert le caractère à l'index demandé dans la string
 * @param s Pointeur d'une structure string
 * @param index Index où le caractère va être inséré
 * @param c Le caractère à insérer
*/
void insert(string *s, int index, char c) {
    if (index > s->char_length) {
        return;
    }

    add_size(s);

    for(int i = s->char_length ; i > index; i--) {
        s->str[i] = s->str[i - 1];
    }

    s->str[index] = c;
}

/**
 * Copie la chaine de caractère de src vers dst
 * @param src Pointeur du string source
 * @param dst Pointeur du string destination
*/
void copy(string *src, string *dst) {
    if (src == NULL) {
        return;
    }

    // Initialise ou vide la variable destination
    if (dst == NULL) {
        init_string(dst);
    }
    else {
        dump(dst);
    }

    // Ajoute caractère par caractère la chaine de src dans dst
    append_string(dst, src->str);
}

/**
 * Retourne n fois la chaine de caractère
 * @param str la chaine de caractère
 * @param count le nombre de fois
*/
char* repeatString(char *str, int count) {
    if (count == 0)
        return "";

    // Compteur pour connaitre la taille de str
    int length = 0;
    while(str[length] != '\0') {
        length++;
    }

    // Créer une variable temporaire à la bonne taille
    char* tmp = malloc(sizeof(char) * (length*count + 1));

    // Boucle pour le nombre de fois à répéter
    for(int i = 0; i < count; i++) {
        // Boucle pour recopier les caractères de str dans la variable temporaire
        for(int j = 0; j < length; j++) {
            tmp[j + (i * length)] = str[j];
        }
    }
    tmp[(length*count + 1)] = '\0'; // Caractère de fin de chaine à la fin
    return tmp;
}

/**
 * Retourne n fois le caractère
 * @param c le caractère
 * @param count le nombre de fois
*/
char* repeatCharacter(char c, int count) {
    if (count <= 0)
        return "";

    // Créer une variable temporaire
    char* str = malloc(sizeof(char) * (count + 1));

    // Boucle pour mettre n fois le caractère
    for(int i = 0; i < count; i++)
        str[i] = c;
    str[count] = '\0'; // Caractère de fin de chaine à la fin
    return str;
}

/**
 * Echange les deux strings
 * @param s1 Chaine de caractère
 * @param s2 Chaine de caractère
*/
void swap(string *s1, string *s2) {
    string tmp;

    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}