#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shared_library_test_lib.h"
#define PAGE_SIZE 4*1024

#define SYSCALL_NUM_LOOKUP_PADDR 318
uintptr_t lookup_paddr(uintptr_t vaddr){
    uintptr_t paddr = (uintptr_t) syscall(SYSCALL_NUM_LOOKUP_PADDR, getpid(), vaddr);
    return paddr;
}

char lib_global_buf_ignore[2*PAGE_SIZE] = {1};
char lib_global_buf1[2*PAGE_SIZE] = {1};

void lib_modify_data(char value){
    lib_global_buf1[0] = value;
}

void lib_show_code_data(){
    uintptr_t rip_value = 0;
    __asm__("leaq (%%rip), %0;": "=r"(rip_value));

    printf("[code] vaddr = 0x%016" PRIxPTR " paddr = 0x%016" PRIxPTR "\n", rip_value, lookup_paddr(rip_value));
    printf("[data] vaddr = 0x%016" PRIxPTR " paddr = 0x%016" PRIxPTR "\n", (uintptr_t)(void*)lib_global_buf1, lookup_paddr((uintptr_t)(void*)lib_global_buf1));

    return;
}
