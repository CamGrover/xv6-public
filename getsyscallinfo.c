//
// Created by Cameron Grover on 1/7/21.
//
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(void)
{
    printf(1, "%d\n", getsyscallinfo());
    exit();
}
