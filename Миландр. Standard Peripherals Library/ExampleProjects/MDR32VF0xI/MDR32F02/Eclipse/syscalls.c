/**
 ******************************************************************************
 * @file    syscalls.c
 * @author  Milandr Application Team
 * @version V0.1.0
 * @date    13/03/2024
 * @brief   Implementation of newlib syscalls.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE IS FOR GUIDANCE ONLY. IT AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING MILANDR'S PRODUCTS IN ORDER TO FACILITATE
 * THE USE AND SAVE TIME. MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES RESULTING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR A USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2025 Milandr</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <sys/stat.h>
#include <sys/times.h>
#include <errno.h>

/* Private define ------------------------------------------------------------*/
#define UNUSED(X) (void)(X)

/* Private variables ---------------------------------------------------------*/
char*  __env[1] = { 0 };
char** environ  = __env;

/* Private function prototypes -----------------------------------------------*/
void    _exit(int status);
int     _close(int file);
int     _execve(char* name, char** argv, char** env);
int     _fork(void);
int     _fstat(int file, struct stat* st);
int     _getpid(void);
int     _isatty(int file);
int     _kill(int pid, int sig);
int     _link(char* old, char* new);
int     _lseek(int file, int ptr, int dir);
int     _open(const char* name, int flags, int mode);
int     _read(int file, char* ptr, int len);
caddr_t _sbrk(int incr);
int     _stat(char* file, struct stat* st);
int     _times(struct tms* buf);
int     _unlink(char* name);
int     _wait(int* status);
int     _write(int file, char* ptr, int len);

/* Private functions ---------------------------------------------------------*/
void _exit(int status)
{
    _kill(status, -1);
    while (1) { }
}

int _close(int file)
{
    UNUSED(file);
    return -1;
}

int _execve(char* name, char** argv, char** env)
{
    UNUSED(name);
    UNUSED(argv);
    UNUSED(env);
    errno = ENOMEM;
    return -1;
}

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int _fstat(int file, struct stat* st)
{
    UNUSED(file);
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid(void)
{
    return 1;
}

int _isatty(int file)
{
    UNUSED(file);
    return 1;
}

int _kill(int pid, int sig)
{
    UNUSED(pid);
    UNUSED(sig);
    errno = EINVAL;
    return -1;
}

int _link(char* old, char* new)
{
    UNUSED(old);
    UNUSED(new);
    errno = EMLINK;
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    UNUSED(file);
    UNUSED(ptr);
    UNUSED(dir);
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    UNUSED(name);
    UNUSED(flags);
    UNUSED(mode);
    return -1;
}

int _read(int file, char* ptr, int len)
{
    UNUSED(file);
    UNUSED(ptr);
    UNUSED(len);
    return 0;
}

caddr_t _sbrk(int incr)
{
    extern char  __heap_top[];   // end of the bss section (start of heap)
    extern char  __heap_limit[]; // end of the heap section (start of stack)
    char*        prev_heap_end;
    static char* heap_end = __heap_top;

    if (heap_end + incr > __heap_limit) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    prev_heap_end = heap_end;
    heap_end += incr;

    return (caddr_t)prev_heap_end;
}

int _stat(char* file, struct stat* st)
{
    UNUSED(file);
    st->st_mode = S_IFCHR;
    return 0;
}

int _times(struct tms* buf)
{
    UNUSED(buf);
    return -1;
}

int _unlink(char* name)
{
    UNUSED(name);
    errno = ENOENT;
    return -1;
}

int _wait(int* status)
{
    UNUSED(status);
    errno = ECHILD;
    return -1;
}

int _write(int file, char* ptr, int len)
{
    UNUSED(file);
    UNUSED(ptr);
    UNUSED(len);
    return 0;
}

/*********************** (C) COPYRIGHT 2025 Milandr ****************************
 *
 * END OF FILE syscalls.c */

