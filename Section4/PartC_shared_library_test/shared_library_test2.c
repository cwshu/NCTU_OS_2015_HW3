#include <stdio.h>
#include <math.h>

#include "shared_library_test_lib.h"

int main(int argc, char *argv[]){
    int num;
    int power = (int)pow(2, 5);

    printf("shared library memory:\n");
    lib_show_code_data();
    printf("input any number to continue\n");
    scanf("%d", &num);

    num = (int)pow(num, power);


    printf("write to shared library data segment\n");
    lib_modify_data('1');
    printf("shared library memory:\n");
    lib_show_code_data();
    printf("input any number to finish program\n");
    scanf("%d", &num);

    return 0;
}
