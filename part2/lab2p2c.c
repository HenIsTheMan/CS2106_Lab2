#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    if(fork() == 0) {
        char* const argv[] = {"cat", "file.txt", NULL};
        execvp("cat", argv);
    }
    else
        wait(NULL);
}

