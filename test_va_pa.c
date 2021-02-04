#include "types.h"
#include "user.h"

char a = 'a';

int
main(int argc, char *argv[])
{
#ifdef VA2PA
    char b = 'b';
    char *c = malloc(10);
    int pa = 0;

    printf(1, "logical address\tphysical addr\n");

    pa = va2pa((int) main);
    printf(1, " %p \t\t %x\tmain -> code segment\n", main, pa);

    pa = va2pa((int) &a);
    printf(1, " %p \t\t %x\ta -> data segment\n", &a, pa);

    pa = va2pa((int) &b);
    printf(1, " %p \t\t %x\tb -> stack segment\n", &a, pa);

    pa = va2pa((int) c);
    printf(1, " %p \t %x\t*c -> heap segment\n", c, pa);


#endif // VA2PA
    exit();
}