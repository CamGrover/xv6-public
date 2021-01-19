//
// Created by Cameron Grover on 1/18/21.
//
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
//#include "fcntl.h"

int
main(){
    int i;
    struct pstat ps;
    if (getpinfo(&ps) < 0)
        return -1;
    for (i=0; i<NPROC; i++){
        if (ps.inuse[i]){
            printf(12, "%d\t", ps.pid[i]);
            printf(12, "%d\t", ps.hticks[i]);
            printf(12, "%d\t", ps.lticks[i]);
        }
    }
    return 0;
}