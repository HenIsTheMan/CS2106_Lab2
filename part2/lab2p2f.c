#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {

    printf("Be patient, the program will take around 7 seconds to run.\n");
    printf("At the end you can do \"cat results.out\" to see the result.\n");

    //
    // Add code here to pipe from ./slow 5 to ./talk and redirect
    // output of ./talk to results.out
    // I.e. your program should do the equivalent of ./slow 5 | talk > results.out
    // WITHOUT using | and > from the shell.
    //

    int pipeFdArr[2]; //0 for reading end, 1 for writing end

    if(pipe(pipeFdArr) < 0){
        perror("lab2p2f: ");
    }

    const int forkResult = fork();

    if(forkResult < 0){
        printf("lab2p2f: Fork Failed!\n");
        return 1;
    }

    if(forkResult > 0){ //Parent process
        //execlp("./talk", "talk", NULL);
    } else{ //Child process
        //execlp("./slow", "slow", "5", NULL);
    }
}

