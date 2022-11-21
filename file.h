#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "string.h"

typedef struct file_t   file;

struct file_t {
    int length;
    struct string_t *array;
};

void init_struct_file(file *file);

void free_file(file *file);

void add_line(file *file, struct string_t str);

int Read_File(char* path, file *file);

int Write_in_File(char *path, char *str);

int Write_new_File(char *path, char *str);

#endif