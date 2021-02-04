#include "types.h"
#include "user.h"
#include "fcntl.h"

#ifdef LSEEK
# define CHARS "1234567890abcdefghijklmnopqrstuvwxyz"
# define FNAME "lseek_test.txt"

char buf[] = CHARS;
char lbuf[] = "ABC";
#endif // LSEEK

int
main(int argc, char *argv[]) {
#ifdef LSEEK
    int flags = O_CREATE | O_RDWR | O_TRUNC;
    int fd = open(FNAME, flags);
    char ch = 0x0;
    int rez = -1;

    if (fd < 0) {
        printf(2, "could not open file\n");
        exit();
    }
    write(fd, buf, strlen(buf));

    // Check the first char of the file
    rez = lseek(fd, 0, SEEK_SET);
    assert(rez == 0);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == '1');
    
    // Check the fifth character of the file
    rez = lseek(fd, 4, SEEK_SET);
    assert(rez == 4);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == '5');
    
    // Back up and check 5 again
    rez = lseek(fd, -1, SEEK_CUR);
    assert(rez == 4);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == '5');
    
    // Seek forward 5 places
    rez = lseek(fd, 5, SEEK_CUR);
    assert(rez == 10);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == 'a');

    // Seek to the end and backup 1 location
    rez = lseek(fd, -1, SEEK_END);
    assert(rez == strlen(buf) - 1);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == 'z');

    // Overwrite some chars and seek back to read
    rez = lseek(fd, 10, SEEK_SET);
    assert(rez == 10);
    write(fd, lbuf, strlen(lbuf));
    rez = lseek(fd, - strlen(lbuf), SEEK_CUR);
    assert(rez == 10);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == 'A');

    // Seek past end of file
    rez = lseek(fd, 5000, SEEK_END);
    assert(rez == (5000 + strlen(buf)));
    write(fd, lbuf, strlen(lbuf));
    rez = lseek(fd, -1, SEEK_END);
    read(fd, &ch, 1);
    printf(1, "%s %d:  '%c'  %d\n", __FILE__, __LINE__, ch, rez);
    assert(ch == 'C');

    // Try to seek before the beginning of the file
    rez = lseek(fd, -1, SEEK_SET);
    assert(rez = -1);

    close(fd);
#endif // LSEEK
    exit();
}
