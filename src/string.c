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

int32_t string_grow(string* s, uint32_t need) {
    if (need <= s->capacity) return 0;
    uint32_t new_cap = __round_up_pow2(need);
    char* newbuf = realloc(s->str, new_cap+1);
    if (!newbuf) return 2;

    s->str = newbuf;
    s->capacity = new_cap;
    return 0;
}

string* new_string(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);

    string* s = malloc(sizeof *s);
    if (!s) return NULL;

    uint32_t cap = __round_up_pow2(len+1);
    if (cap < STRING_MIN_CAP) cap = STRING_MIN_CAP;

    s->capacity = cap;

    s->str = malloc(s->capacity+1);
    if (!s->str) {
        free(s);
        return NULL;
    }
    memcpy(s->str, str, len);
    s->str[len] = '\0';
    s->length = len;
    return s;
}

string* new_string_with_size(uint32_t size) {
    string* s = malloc(sizeof *s);
    if (!s) return NULL;
    
    uint32_t cap = __round_up_pow2(size);
    if (cap < STRING_MIN_CAP) cap = STRING_MIN_CAP;

    s->capacity = cap;
    s->length = 0;

    s->str = malloc(s->capacity);
    if (!s->str) {
        free(s);
        return NULL;
    }
    s->str[0] = '\0';
    return s;
}

char* string_to_cstr(string* s) {
    if (!s) return NULL;
    char* buf = malloc(s->length+1);
    if (!buf) return NULL;
    memcpy(buf, s->str, s->length);
    buf[s->length] = '\0';
    return buf;
}

int32_t string_clear(string* s) {
    if (!s) return 1;
    s->str = '\0';
    s->length = 0;
    return 0;
}

void free_string(string* s) {
    if (!s) return;
    free(s->str);
    free(s);
}

int32_t string_write(string* s, const char* str) {
    if (!s || !str) return 1;

    size_t len = strlen(str);

    if (len > s->capacity) {
        if (string_grow(s, len)) return 2;
    }

    memcpy(s->str, str, len);
    s->str[len] = '\0';
    s->length = len;
    return 0;
}

int32_t string_append(string* s, const char* str) {
    if (!s || !str) return 1;

    size_t len = strlen(str);
    size_t total = s->length+len;
    
    if (total > s->capacity) {
        if (string_grow(s, total)) return 2;
    }

    memcpy(s->str+s->length, str, len);
    s->length = total;
    s->str[s->length] = '\0';
    return 0;
}

int32_t string_insert(string* s, uint32_t index, const char* str) {
    if (!s || !str) return 1;
    if (index > s->length) return 3;

    if (index == s->length) return string_append(s, str);

    size_t len = strlen(str);
    size_t total = s->length+len;

    if (total > s->capacity) {
        if (string_grow(s, total)) return 2;
    }

    memmove(
        s->str+index+len,
        s->str+index,
        (s->length-index)+1
    );

    memcpy(s->str+index, str, len);

    s->length = total;
    return 0;
}

int32_t string_replace(string* s, uint32_t index, const char* str) {
    if (!s || !str) return 1;
    return 0;
}

void string_find() {}
