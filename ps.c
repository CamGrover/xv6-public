#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
#ifdef CPS
    int val = 0;

    if (argc > 1) {
        val = atoi(argv[1]);
    }

    cps(val);
#endif // CPS
    exit();
}