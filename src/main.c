#include <stdio.h>
#include "string.c"

int main(void) {
    int32_t result = 0;
    string* test = new_string(12);
    if(!test) return 1;

    result = string_write(test, "hello world");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    result = string_write(test, "hello world! my name is Moryn.");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    free_string(test);
    return 0;
}
