/*
 * Usage: sorting_number [num]
 * input [num] numbers, and print sorted numbers.
 * This example use malloc for variable-length array of numbers
 */
#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void *a, const void *b){
    return a - b;
}

int main(int argc, char *argv[]){
    int num;
    int* number_array = NULL;
    
    if( argc < 2 ){
        fprintf(stderr, "usage: %s [num]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *endptr;
    num = strtol(argv[1], &endptr, 10);
    if( endptr == argv[1] ){
        fprintf(stderr, "%s is not a number\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("malloc size = %zu\n", num*sizeof(int));
    number_array = malloc(num*sizeof(int));
    if( !number_array ){
        perror("malloc failed\n");
        exit(EXIT_FAILURE);
    }
    
    printf("please input %d unsorted number to sort\n", num);
    for( int i = 0; i < num; ++i ){
        scanf("%d", &number_array[i]);
    }

    qsort(number_array, num, sizeof(int), int_cmp);
    
    for( int i = 0; i < num; ++i ){
        if( i != num - 1 ){
            printf("%d, ", number_array[i]);
        }
        else{
            printf("%d\n", number_array[i]);
        }
    }

    getchar();
    return 0;
}
