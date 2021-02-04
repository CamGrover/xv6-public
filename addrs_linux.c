#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int unint_data;
static int init_data = -1;
static const char str[] = "hello world";

int 
main(int argc, char *argv[]) 
{
    static int sdata = -2;
    int x = 3;
    char *ch1 = sbrk(0);
    char *ch2 = malloc(100);
    char *ch3 = sbrk(0);

    // this is the large memory for malloc, managned by mmap
    printf("location of big malloc\t\t: %p\n", malloc(1024 * 1024));

    // this is small memory from malloc, managed by calling sbrk()
    printf("location of high water mark\t: %p\n", ch3);
    printf("location of malloc 1\t\t: %p\n", ch2);
    printf("location of malloc 2\t\t: %p\n", malloc(200));
    printf("location of malloc 3\t\t: %p\n", malloc(300));
    printf("location of low water mark\t: %p\n\n", ch1);

    printf("location of argv[0]\t\t: %p\n", &(argv[0]));
    printf("location of stack\t\t: %p\n", &x);
    printf("location of argc\t\t: %p\n", &argc);
    printf("location of argv\t\t: %p\n", &argv);
    printf("location of alloca 1\t\t: %p\n", alloca(100));
    printf("location of alloca 2\t\t: %p\n\n", alloca(200));

    printf("location of uninitialized\t: %p\n", &unint_data);
    printf("location of initialized\t\t: %p\n", &init_data);
    printf("location of static data\t\t: %p\n\n", &sdata);

    printf("location of const str\t\t: %p\n", &str);
    printf("location of main\t\t: %p\n\n", main);

    exit(0);
}
