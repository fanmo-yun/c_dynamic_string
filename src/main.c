#include <stdio.h>
#include <pthread.h>
#include "string.c"

int main(void) {
    int32_t result = 0;

    string* test1 = new_string("hello everybody!");
    if(!test1) return 1;
    printf("str -> %s, length -> %d, cap -> %d\n", test1->str, test1->length, test1->capacity);
    free_string(test1);

    string* test = new_string_with_size(12);
    if(!test) return 1;

    result = string_write(test, "hello world");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    string_clear(test);
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    result = string_write(test, "hello world! my name is Moryn.");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    result = string_append(test, " and my age is 20 years-old");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    result = string_insert(test, 12, " wow this is amazing!");
    if (result == 2) {
        free_string(test);
        return result;
    }
    printf("str -> %s, length -> %d, cap -> %d\n", test->str, test->length, test->capacity);

    char* test_cstr = string_to_cstr(test);
    printf("str -> %s\n", test_cstr);
    free(test_cstr);
    
    free_string(test);
    test = NULL;
    return 0;
}
