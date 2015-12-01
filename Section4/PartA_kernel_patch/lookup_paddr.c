#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <asm/pgtable_types.h>

#define INVALID_ADDR 0x5555555555555555

unsigned long virtaddr_to_physaddr(struct mm_struct *mm, unsigned long vaddr)
{
    /* virtual address translation for x86_64 platform 
     * 48 bits virtual address, 4 level translation for 9 bits index each and 12 bits offset.
     */
    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    unsigned long paddr = 0;

    printk("translate vaddr 0x%lx by page table at 0x%lx\n", vaddr, mm->pgd);
    printk("page table index: %lu:%lu:%lu:%lu\n", pgd_index(vaddr), pud_index(vaddr), pmd_index(vaddr), pte_index(vaddr));

    /* mm => pgd 
     * page table base address(record in mm->pgd) to 1st level entry */
    pgd = pgd_offset(mm, vaddr);
    if (pgd_none(*pgd)) {
        printk("[page table at 0x%lx] no pgd at index %lu\n", mm->pgd, pgd_index(vaddr));
        return INVALID_ADDR;
    }
    printk("pgd_val = 0x%lx\n", pgd_val(*pgd));

    /* pgd => pud 
     * 1st level to 2nd level entry */
    pud = pud_offset(pgd, vaddr);
    if (pud_none(*pud)) {
        printk("[page table at 0x%lx] no pud at index %lu:%lu\n", mm->pgd, pgd_index(vaddr), pud_index(vaddr));
        return INVALID_ADDR;
    }
    printk("pud_val = 0x%lx\n", pud_val(*pud));

    /* pud => pmd
     * 2nd level to 3rd level entry */
    pmd = pmd_offset(pud, vaddr);
    if(pmd_none(*pmd)){
        printk("[page table at 0x%lx] no pmd at index %lu:%lu:%lu\n", mm->pgd, \
               pgd_index(vaddr), pud_index(vaddr), pmd_index(vaddr));
        return INVALID_ADDR;
    }
    printk("pmd_val = 0x%lx\n", pmd_val(*pmd));

    /* If page is 2MB huge page, pmd is the last level */
    if(pmd_large(*pmd)){
        printk("vaddr %lx is at 2MB huge page\n", vaddr);
        
        /* compute physical address */
        paddr = pmd_val(*pmd) & PMD_MASK;
        paddr = paddr | (vaddr & ~PMD_MASK);
        return paddr;
    }

    /* pud => pte 
     * 3rd level to 4th level entry */
    pte = pte_offset_kernel(pmd, vaddr);
    if(pte_none(*pte)){
        return INVALID_ADDR;
    }
    printk("pte_val = 0x%lx\n", pte_val(*pte));

    /* pte is the last level, compute physical address
     * you may use PAGE_MASK = 0xfffffffffffff000 to help you get [0:11] bits
     */
    printk("vaddr %lx is at 4KB page\n", vaddr);

    /* compute physical address 
     */
    paddr = pte_val(*pte) & PAGE_MASK;
    paddr = paddr | (vaddr & ~PAGE_MASK);
    return paddr;
}


asmlinkage unsigned long sys_lookup_paddr(pid_t pid, unsigned long vaddr)
{
    struct task_struct *p;
    unsigned long ret = INVALID_ADDR;

    p = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (p == NULL){
        printk("Wrong pid: %d\n", pid);
        return ret;
    }

    ret = virtaddr_to_physaddr(p->mm, vaddr);

    return ret;
}
