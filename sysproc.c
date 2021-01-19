#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "spinlock.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_settickets(void)
{
    int t;
    if (argint(0, &t) < 0)
        return -1;
    if (t <= 0)
        return -1;
    myproc()->tickets = t;
    return 0;
}

int
sys_getpinfo(void)
{
    struct{
            struct spinlock lock;
            struct proc proc[NPROC];
        } *ptable = myptable();
    struct pstat* ps;
    if (argptr(0, (void*)&ps, sizeof(ps)) < 0)
        return -1;

    int i = 0;
    struct proc *p;
    for(p = ptable->proc; p < &ptable->proc[NPROC]; p++){
        if (p->state == UNUSED){
            ps->inuse[i] = 0;
            ps->pid[i] = 0;
            ps->hticks[i] = 0;
            ps->lticks[i] = 0;
        }
        else {
            ps->inuse[i] = 1;
            ps->pid[i] = p->pid;
            ps->hticks[i] = p->hticks;
            ps->lticks[i] = p->lticks;
        }
        i++;
    }
    return 0;
}
