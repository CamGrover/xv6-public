#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512
#define DIRSTR 128

void cp(char *, char *);

int
main(int argc, char *argv[])
{
    int i;
    int res;
    char *oname;
    struct stat st;
    char dirstr[DIRSTR];

    if (argc < 3) {
        printf(2, "must have at least 2 arguments\n");
        exit();
    }

    // cp f1 f2
    oname = argv[argc - 1];
    res = stat(oname, &st);
    if (res < 0) {
        // in form of
        //   cp f1 f2
        cp(oname, argv[1]);
    }
    else {
        switch (st.type) {
        case T_FILE:
            //   cp f1 f2
            cp(oname, argv[1]);
            break;
        case T_DIR:
            for (i = 1; i < (argc - 1); i++) {
                // cp f1 f2 f3 dir
                memset(dirstr, 0, DIRSTR);
                strcpy(dirstr, oname);
                dirstr[strlen(dirstr)] = '/';
                strcpy(&(dirstr[strlen(dirstr)]), argv[i]);
                cp(dirstr, argv[i]);
            }
            break;
        default:
            printf(2, "cannot copy to a device\n");
            exit();
            break;
        }
    }

    exit();
}

void
cp(char *oname, char *iname)
{
    int n;
    int ofd = -1;
    int ifd = -1;
    int res = -1;
    int flags;
    char buf[BUFSIZE];

    if ((ifd = open(iname, O_RDONLY)) >= 0) {
#ifdef TRUNC_FILE
        flags = O_WRONLY | O_CREATE | O_TRUNC;
#endif // TRUNC_FILE
        struct stat st;
        res = stat(oname, &st);
        if (res >= 0) {
            unlink(oname);
        }
        flags = O_WRONLY | O_CREATE;
        if ((ofd = open(oname, flags)) >= 0) {
            for ( ; ((n = read(ifd, buf, BUFSIZE)) > 0) && ((res = write(ofd, buf, n))); ) ;
            close(ofd);
            close(ifd);
        }
        else {
            printf(2, "could not open o/p file  %s\n", oname);
            close(ifd);
            exit();
        }
    }
    else {
        printf(2, "could not open i/p file  %s\n", iname);
        exit();
    }
}
