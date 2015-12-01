/*
 * compilation: gcc -std=gnu11 -Wall stack_single_page.c -o stack_single_page
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PAGE_SIZE 4*1024

/* system call number for address translation system call */
#define SYSCALL_NUM_LOOKUP_PADDR 318

/* system call wrapper */
uintptr_t lookup_paddr(uintptr_t vaddr){
    uintptr_t paddr = (uintptr_t) syscall(SYSCALL_NUM_LOOKUP_PADDR, getpid(), vaddr);
    return paddr;
}

void print_address(uintptr_t stack1, uintptr_t stack2){
    /* uintptr_t is a integer type which is large enough for pointer address (system memory address).
     * For more detail, 
     *   please google "fixed size integer C/C++", "32-bit/64-bit data model(e.g. ILP32, LP64)",
     *   and read this site: https://goo.gl/Qy5OsR
     */

    printf("[stack] vaddr: 0x%016" PRIxPTR " paddr: 0x%016" PRIxPTR "\n", stack1, lookup_paddr(stack1));
    printf("[stack] vaddr: 0x%016" PRIxPTR " paddr: 0x%016" PRIxPTR "\n", stack2, lookup_paddr(stack2));
}

void print_address_wrapper(unsigned char* stack1, unsigned char* stack2){
    print_address((uintptr_t)(void*)stack1, \
                  (uintptr_t)(void*)stack2);
}

int main(int argc, char *argv[]){
    /* stack segment */
    unsigned char local_buf_ignore[2*PAGE_SIZE], local_buf1[2*PAGE_SIZE], local_buf2[2*PAGE_SIZE];

    /* initial value of memory page to non-zero for simplifying condition (zero page in linux kernel) */
    memset(local_buf_ignore, 1, 2*PAGE_SIZE);
    memset(local_buf1, 2, 2*PAGE_SIZE);
    memset(local_buf2, 3, 2*PAGE_SIZE);

    /* forking */
    pid_t child_pid = fork();

    if(child_pid > 0){
        /* parent */
        printf("-- parent address --\n");
        print_address_wrapper(local_buf1, local_buf2);

        /* wait for child died
         * We doesn't want that parent process dies when child process is still testing memory CoW strategy. */
        wait(NULL);
    }
    else if(child_pid == 0){
        /* child */

        /* start after parent print address */
        sleep(3);

        printf("\n-- child address --\n");

        printf("origin:\n");
        print_address_wrapper(local_buf1, local_buf2);

        /* TODO */

        /* TODO finished */
    }
    
    return 0;
}
