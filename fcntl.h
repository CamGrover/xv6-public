#ifndef __FCNTL_H
# define __FCNTL_H

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

# ifdef TRUNC_FILE
#  define O_TRUNC 0x1000
#endif // TRUNC_FILE

#endif // __FCNTL_H