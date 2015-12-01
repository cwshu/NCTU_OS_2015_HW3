#include <stdio.h>

#include "shared_library_test_lib.h"

int main(int argc, char *argv[]){
    int num;

    printf("shared library memory:\n");
    lib_show_code_data();
    printf("input any number to continue\n");
    scanf("%d", &num);

    printf("write to shared library data segment\n");
    lib_modify_data('1');
    printf("shared library memory:\n");
    lib_show_code_data();
    printf("input any number to finish program\n");
    scanf("%d", &num);

    return 0;
}
