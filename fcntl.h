#ifndef __FCNTL_H
# define __FCNTL_H

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

# ifdef TRUNC_FILE
#  define O_TRUNC 0x1000
#endif // TRUNC_FILE

#ifdef LSEEK
# define SEEK_SET 0x1
# define SEEK_CUR 0x2
# define SEEK_END 0x4
#endif // LSEEK

#ifdef APPEND_FILE
# define O_APPEND 0x2000

# define FILE_NOWRITE    0x0
# define FILE_WRITEABLE  0x1
# define FILE_APPENDABLE 0x2
#endif // APPEND_FILE

#endif // __FCNTL_H