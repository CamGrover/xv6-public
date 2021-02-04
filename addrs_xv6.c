#include "types.h"
#include "user.h"

static int unint_data;
static int int_data = -1;
static const char str[] = "hello world";

int 
main(int argc, char *argv[]) 
{
    static int sdata = -2;
    int x = 3;
    char *ch1 = sbrk(0);
    char *ch2 = malloc(100);
    char *ch3 = sbrk(0);

    printf(1, "location of high water mark\t: %p\n", ch3);
    printf(1, "location of malloc 1\t\t: %p\n", ch2);
    printf(1, "location of malloc 2\t\t: %p\n", malloc(200));
    printf(1, "location of malloc 3\t\t: %p\n", malloc(300));
    printf(1, "location of sbrk(0)\t\t: %p\n\n", ch1);

    printf(1, "location of argv[0]\t\t: %p\n\n", &(argv[0]));

    printf(1, "location of stack\t\t: %p\n", &x);
    printf(1, "location of argc\t\t: %p\n", &argc);
    printf(1, "location of argv\t\t: %p\n", &argv);

    printf(1, "location of uninitialized\t: %p\n", &unint_data);
    printf(1, "location of initialized\t\t: %p\n", &int_data);

    printf(1, "location of static data\t\t: %p\n", &sdata);
    printf(1, "location of const str\t\t: %p\n", &str);

    printf(1, "location of main\t\t: %p\n\n", main);

    exit();
}
