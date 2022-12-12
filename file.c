#include "file.h"

/**
 * Initialise la structure file
 * @param file Pointeur de la structure
*/
void init_struct_file(file *file) {
    file->length = 0;
    file->array = NULL;
}

/**
 * Libère la mémoire allouée dans chaque string dans le fichier
 * @param s Pointeur d'une structure file
*/
void free_file(file *file) {
    if (file == NULL) {
        return;
    }

    // libère la mémoire de toutes les lignes
    for(int i = 0; i < file->length; i++) {
        free_string(&file->array[i]);
    }
    file->length = 0;
    free(file->array);
    file->array = NULL;
}

/**
 * Ajoute une ligne qui contient la chaine de caractère str dans file
 * @param file Pointeur du fichier qui va contenir les lignes de texte
 * @param str  La chaine de caractère à inscrire dans file
*/
void add_line(file *file, struct string_t str) {
    if (file == NULL) {
        return;
    }
    // Ajoute la case mémoire pour la nouvelle ligne
    file->length++;
    file->array = realloc(file->array, sizeof(string) * file->length);

    init_string(&file->array[file->length - 1]);
    copy(&str, &file->array[file->length - 1]);
}

/**
 * Lit le fichier et met tous les caractères dans le tableau dans la structure file
 * @param path Chemin du fichier à lire
 * @param file Pointeur d'une struct file_t
*/
int Read_File(char* path, file *file) {
    FILE *fptr = fopen(path, "r");

    if (fptr == NULL) {
        printf("Erreur pour lire le fichier : %s\n", path);
        return -1;
    }

    // Initialise la variable file
    init_struct_file(file);
    char c;

    // Variable temporaire qui va contenir les caractères de la ligne qu'on lit
    string tmp;
    init_string(&tmp);

    do {
        c = getc(fptr);
        if (c != '\n' && c != EOF) {
            append(&tmp, c); // Ajoute le caractère c dans la variable temporaire
        }
        else {
            // Ajoute une nouvelle ligne dans file avec comme chaine de caractère la variable tmp
            if (tmp.char_length != 0) {
                add_line(file, tmp);
            }

            dump(&tmp); // Vide la variable temporaire
        }
    } while (c != EOF);
    free_string(&tmp); // Libère la mémoire de la chaine temporaire
    fclose(fptr);

    return 0;
}

/**
 * Ecrit une chaîne de caractère à la suite dans le fichier
 * @param path Chemin du fichier à créer
 * @param str La chaine de caractère à écrire dans le fichier
*/
int Write_in_File(char *path, char *str) {
    FILE *fptr = fopen(path, "a");

    if (fptr == NULL) {
        printf("Erreur pour écrire le fichier : %s\n", path);
        return -1;
    }

    fprintf(fptr, "%s", str);

    fclose(fptr);

    return 0;
}

/**
 * Créer un nouveau fichier et écrit dedans
 * @param path Chemin du fichier à créer
 * @param str La chaine de caractère à écrire dans le fichier
*/
int Write_new_File(char *path, char *str) {
    FILE *fptr = fopen(path, "w");

    if (fptr == NULL) {
        printf("Erreur pour écrire le fichier : %s\n", path);
        return -1;
    }

    fprintf(fptr, "%s", str);

    fclose(fptr);

    return 0;
}