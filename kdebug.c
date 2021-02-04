#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
#ifdef KDEBUG
    int kdebug_value = 0;

    if (argc > 1) {
        kdebug_value = atoi(argv[1]);
        if (kdebug_value < 0) {
            printf(1, "debug value must eb >= 0\n");
            exit();
        }
    }
    kdebug(kdebug_value);
#endif // KDEBUG
    exit();
}