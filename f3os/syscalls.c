#define O_RDONLY
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 4

int _read(int fd, char *buf, int count) {
   int c;
   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (c)
      : "a" (47),
      "b" (fd),
      "c" (buf),
      "d" (count)
      : "cc", "memory"
   );
   return c;
}

int _write(int fd, const char *buf, int count) {
   int c;
   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (c)
      : "a" (53),
      "b" (fd),
      "c" (buf),
      "d" (count)
      : "cc", "memory"
   );
   return c;
}

int _open(const char *path, int flags, int mode) {
   int is_write = (flags & O_WRONLY) || (flags & O_RDWR);
   int is_create = flags & O_CREAT;
   (void)mode;
   int fd;
   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (fd)
      : "a" (52),
      "b" (path),
      "c" (is_write||is_create)
      : "cc", "memory"
   );
   return fd;
}

int _close(int fd) {
   (void)fd;
   // do nothing yet
   return 0;
}

void *_sbrk(int incr) {
   int addr;

   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (addr)
      : "a" (51),
      "b" (incr)
      : "cc", "memory"
   );

   return (void*)addr;
}

void _exit(int status) {
   asm volatile(
      "int $0x30"
      :: "a" (10),
      "b" (status)
   );
}

// Stubs
int _fstat(int fd, struct stat *st) {
   //st->st_mode = S_IFCHR;
   return 0;
}

int _isatty(int fd) {
   return 1;
}

static inline int _lseek(int fd, int offset, int type) {
   int pos;
   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (pos)
      : "a" (48),
      "b" (fd),
      "c" (offset),
      "d" (type)
      : "cc", "memory"
   );
   return pos;
}

int _getpid(void) {
   return 1;
}

int _kill(int pid, int sig) {
   //errno = EINVAL;
   return -1;
}

int _unlink(const char *pathname) {
   return -1;
}

static inline int _mkdir(char *path) {
   int success;
   asm volatile (
      "int $0x30;movl %%ebx, %0;"
      : "=r" (success)
      : "a" (50),
      "b" (path)
      : "cc", "memory"
   );
   return success;
}

// references

int read(int fd, char *buf, int count) {
   return _read(fd, buf, count);
}

int write(int fd, const char *buf, int count) {
   return _write(fd, buf, count);
}

int open(const char *path, int flags, int mode) {
   return _open(path, flags, mode);
}

int close(int fd) {
   return _close(fd);
}

void *sbrk(int incr) {
   return _sbrk(incr);
}

int kill(int pid, int sig) {
   return _kill(pid, sig);
}

int getpid(void) {
   return _getpid();
}

int lseek(int fd, int offset, int whence) {
   return _lseek(fd, offset, whence);
}

int isatty(int fd) {
   return _isatty(fd);
}

int fstat(int fd, struct stat *st) {
   return 0;
}

int unlink(const char *pathname) {
   return _unlink(pathname);
}

void mkdir(const char *path) {
   _mkdir((char*)path);
}

int _link(const char *old, const char *new)
{
   return -1;
}

int link(const char *old, const char *new)
{
   return _link(old, new);
}
