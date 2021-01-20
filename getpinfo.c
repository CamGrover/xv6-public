//
// Created by Cameron Grover on 1/18/21.
//
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
//#include "fcntl.h"


// Source:
// Eamon Nerbonne
// https://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c
int lenHelper(unsigned x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}

int printLen(int x) {
    return x < 0 ? lenHelper(-x) + 1 : lenHelper(x);
}

int
main(){
    int i,
        n = 3;
    struct pstat ps;
    if (getpinfo(&ps, &n) < 0)
        return -1;
    printf(17, "pid\thticks\tlticks\n");
    for (i=0; i<64; i++){
        if (ps.inuse[i]){
            printf(printLen(ps.pid[i]), "%d\t", ps.pid[i]);
            printf(printLen(ps.hticks[i]), "%d\t", ps.hticks[i]);
            printf(printLen(ps.lticks[i]), "%d\t", ps.lticks[i]);
            printf(printLen(ps.tickets[i]), "%d\n", ps.tickets[i]);
//            printf(6, "pid: %d\t", ps.pid[i]);
//            printf(10, "hticks: %d\t", ps.hticks[i]);
//            printf(10, "lticks: %d\n", ps.lticks[i]);
        }
    }
    return 0;
}