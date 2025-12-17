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

static inline uint32_t __round_up_pow2(uint32_t x) {
    if (x <= 1) return 1;
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

int32_t __update_count(string* s, uint32_t len) {
    uint32_t new_cap = __round_up_pow2(len);
    char* newbuf = realloc(s->str, new_cap+1);
    if (!newbuf) return 2;

    s->str = newbuf;
    s->capacity = new_cap;
    return 0;
}

string* new_string(uint32_t size) {
    string* s = malloc(sizeof *s);
    if (!s) return NULL;
    
    uint32_t cap = __round_up_pow2(size);
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

void string_clear(string* s) {
    memset(s->str, 0, s->capacity);
    s->length = 0;
}

void free_string(string* s) {
    if (!s) return;
    free(s->str);
    free(s);
}

int32_t string_write(string* s, const char* str) {
    if (!s || !str) return 1;

    uint32_t len = strlen(str);

    if (len+1 > s->capacity) {
        if (__update_count(s, len+1)) return 2;
    }

    memcpy(s->str, str, len);
    s->str[len] = '\0';
    s->length = len;
    return 0;
}

int32_t string_append(string* s, const char* str) {
    if (!s || !str) return 1;

    uint32_t len = strlen(str);
    uint32_t total = s->length+len;
    
    if (total > s->capacity) {
        if (__update_count(s, total+1)) return 2;
    }

    memcpy(s->str+s->length, str, len);
    s->length += len;
    s->str[s->length] = '\0';

    return 0;
}
