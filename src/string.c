#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define STRING_MIN_CAP 16

typedef struct STRING {
    char* str;
    uint32_t length;
    uint32_t capacity;
} string;

static inline uint32_t round_up_pow2(uint32_t x) {
    if (x <= 1) return 1;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

string* new_string(uint32_t size) {
    string* s = malloc(sizeof *s);
    if (!s) return NULL;
    
    uint32_t cap = round_up_pow2(size);
    if (cap < STRING_MIN_CAP) cap = STRING_MIN_CAP;

    s->capacity = cap;
    s->length = 0;

    s->str = malloc(s->capacity+1);
    if (!s->str) {
        free(s);
        return NULL;
    }
    s->str[0] = '\0';
    return s;
}

int32_t string_write(string* s, const char* str) {
    if (!s || !str) return 1;

    uint32_t len = strlen(str);

    if (len+1 > s->capacity) {
        uint32_t new_cap = round_up_pow2(len+1);
        char* newbuf = realloc(s->str, new_cap+1);
        if (!newbuf) return 2;

        s->str = newbuf;
        s->capacity = new_cap;
    }
    
    memcpy(s->str, str, len);
    s->str[len] = '\0';
    s->length = len;
    return 0;
}

void string_append() {}

void free_string(string* s) {
    if (!s) return;
    free(s->str);
    free(s);
}
