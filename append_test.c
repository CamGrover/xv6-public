#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

#ifdef APPEND_FILE
# define NUMS "1234567890"
# define LCASE "abcdefghijklmnopqrstuvqxyz"
# define UCASE "ABCDEFGHIJKLMNOPQRSTUVQXYZ"
# define PLUSSES "+++++"
# define MINUSES "-----"
# define FNAME1 "atest1.txt"
# define FNAME2 "atest2.txt"

char buf[1000] = {0};
#endif // APPEND_FILE

int
main(int argc, char *argv[]){
#ifdef APPEND_FILE
    int flags = O_CREATE | O_RDWR | O_TRUNC | O_APPEND;
    int fd = -1;
    int rez = -1;
    struct stat st;

    if ((fd = open(FNAME1, flags)) < 0) {
        printf(2, "could not open file\n");
        exit();
    }
    // Put some data into the file
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, NUMS);
    write(fd, buf, strlen(buf));

    // If wee seek back and then write to it, will it still append?
    rez = lseek(fd, 0, SEEK_SET);
    assert(rez == 0);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, PLUSSES);
    write(fd, buf, strlen(buf));

    // If we seek into the middle of the file and write to it, 
    // will is still append?
    rez = lseek(fd, 10, SEEK_SET);
    assert(rez == 10);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, LCASE);
    write(fd, buf, strlen(buf));

    // If we seek into another place the middle of the file and write to it, 
    // will is still append?
    rez = lseek(fd, 20, SEEK_SET);
    assert(rez == 20);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, MINUSES);
    write(fd, buf, strlen(buf));

    // If we seek to the beginning of the file...
    rez = lseek(fd, 0, SEEK_SET);
    assert(rez == 0);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, UCASE);
    write(fd, buf, strlen(buf));

    // If we seek past the end of the file...
    rez = lseek(fd, 100, SEEK_END);
    // assert(rez == 0);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, NUMS);
    write(fd, buf, strlen(buf));
    printf(1, "%d >>>%d<<<\n", __LINE__, fd);
    close(fd);

    // Now check the contents of the file
    rez = stat(FNAME1, &st);
    fd = open(FNAME1, O_RDONLY);
    printf(1, "%d >>>%d<<<\n", __LINE__, fd);
    read(fd, buf, sizeof(buf));
    printf(1, "file contents    : \"%s\"\n", buf);
    printf(1, "length of string: %d\n", strlen(buf));
    printf(1, "size of file  : %d\n", st.size);

    // Test to ensure we did not mess up other non-append
    // write to file
    flags = O_CREATE | O_WRONLY | O_TRUNC;
    if ((fd = open(FNAME2, flags)) < 0) {
        printf(1, "could not open file");
        exit();
    }
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, NUMS);
    write(fd, buf, strlen(buf));
    
    rez = lseek(fd, 0, SEEK_SET);
    memset(buf, 0x0, sizeof(buf));
    strcpy(buf, PLUSSES);
    write(fd, buf, strlen(buf));
    close(fd);
#endif // APPEND_FILE
    exit();
}
