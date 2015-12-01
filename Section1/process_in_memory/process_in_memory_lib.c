#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "process_in_memory_lib.h"

#define STOP() \
    getchar(); getchar();

int lib_global_var;
void lib_show_variable(){
    int local_buf;
    int* heap_buf = (int*)malloc(1024);
    uint64_t rip_value = 0;
    __asm__("leaq (%%rip), %0;": "=r"(rip_value));

    printf("In share library libpim:\n");
    printf("[code]  0x%016" PRIx64 "\n", rip_value);
    printf("[data]  %018p\n", &lib_global_var);
    printf("[stack] %018p\n", &local_buf);
    printf("[heap]  %018p\n", heap_buf);
    STOP()   

    free(heap_buf);
    return;
}
