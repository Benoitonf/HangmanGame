#ifndef STRING_H
#define STRING_H

#include "file.h"

typedef struct string_t string;

struct string_t {
    int char_length;
    char *str;
};

void init_string(string *s);

void free_string(string *s);

void dump(string *s);

void append(string *s, char c);

void append_string(string *s, char *string);

void insert(string *s, int index, char c);

void copy(string *src, string *dst);

char* repeatCharacter(char c, int count);

char* repeatString(char *str, int count);

void swap(string *s1, string *s2);

#endif