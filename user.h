#pragma once

#ifndef __USER_H
# define __USER_H

# ifndef NULL
#  define NULL 0
# endif // NULL

# ifndef TRUE
#  define TRUE 1
# endif // TRUE
# ifndef FALSE
#  define FALSE 0
# endif // FASLE

# ifndef MAX
#  define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
# endif // MAX
# ifndef MIN
#  define MIN(_a,_b) ((_a) < (_b) ? (_a) : (_b))
# endif // MIN

# ifdef NDEBUG
#  define assert(expr)
# else // NDEBUG
#  define assert(expr) \
    if (! (expr) ) { \
    printf(1, "assert failes: file %s line %d\n", __FILE__, __LINE__); \
    exit();}
# endif // NEBUG

// These usually come from some inculde files (like values.h)
# ifndef CHARBITS
#  define CHARBITS 8
# endif // CHARBITS

# define _TYPEBITS(type) (sizeof (type) * CHARBITS)

# ifndef __WORDSIZE
#  define __WORDSIZE _TYPEBITS(int)
# endif // WORDSIZE

# ifndef SHORTBITS
#  define SHORTBITS _TYPEBITS(short)
# endif // SHORTBITS

# ifndef INTBITS
#  define INTBITS _TYPEBITS(int)
# endif // INTBITS

# ifndef LONGBITS
#  define LONGBITS _TYPEBITS(long)
# endif // LONGBITS

# ifndef FLOATBITS
#  define FLOATBITS _TYPEBITS(float)
# endif // FLOATBITS

# ifndef DOUBLEBITS
#  define DOUBLEBITS _TYPEBITS(double)
# endif // DOUBLEBITS

# ifndef PTRBITS
#  define PTRBITS _TYPEBITS(void *)
# endif // PTRBITS

# ifndef PGSIZE
// This is duplicated from mmu.h
#  define PGSIZE 4096
# endif // PGSIZE

struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);


#ifdef GETPPID
int getppid(void);
#endif // GETPPID

#endif // __USER_H
