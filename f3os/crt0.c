extern int main(int argc, char **argv);
extern void exit(int code);

extern char __bss_start[];
extern char __bss_end[];

void _start(int argc, char **argv) {
    // clear bss
    char *bss = __bss_start;
    while (bss < __bss_end) {
        *bss++ = 0;
    }
    int ret = main(argc, argv);
    
    exit(ret);
    
    while(1);
}