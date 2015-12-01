/*
 * compilation: gcc -std=gnu11 -Wall basic_fork_ex.c -o basic_fork_ex
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>

/* system call number for address translation system call */
#define SYSCALL_NUM_LOOKUP_PADDR 318
/* system call wrapper */
unsigned long lookup_paddr(void* vaddr){
    unsigned long paddr = syscall(SYSCALL_NUM_LOOKUP_PADDR, getpid(), vaddr);
    return paddr;
}

void child_process();
void parent_process();
int *mem_alloc;

void child_process()
{
    int temp;
    sleep(2);
    unsigned long paddr = lookup_paddr(mem_alloc);
    printf("Child pid: %d. [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), (unsigned long)mem_alloc, paddr, *mem_alloc);
    
    temp = *mem_alloc;
    *mem_alloc = 1;
    printf("\n*** Modify variable 'mem_alloc' from %d to %d ***\n\n", temp, *mem_alloc);

    sleep(2);
    paddr = lookup_paddr(mem_alloc);
    printf("Child pid: %d. [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), (unsigned long)mem_alloc, paddr, *mem_alloc);

}

void parent_process()
{
    sleep(1);
    unsigned long paddr = lookup_paddr(mem_alloc);
    printf("Parent pid: %d. [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), (unsigned long)mem_alloc, paddr, *mem_alloc);
    
    sleep(2); 
    paddr = lookup_paddr(mem_alloc);
    printf("Parent pid: %d. [Var 'mem_alloc']vaddr: 0x%lx, paddr: 0x%lx, val: %d\n",
            getpid(), (unsigned long)mem_alloc, paddr, *mem_alloc);
}



int main()
{
    int status;
    pid_t pid;
    
    mem_alloc = (int*) malloc(sizeof(int));
    *mem_alloc = 1000;

    pid = fork();
    
    if (pid == 0)
        child_process();
    else
        parent_process();

    wait(&status);
    return 0;
}
