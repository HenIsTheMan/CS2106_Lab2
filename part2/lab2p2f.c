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
        return 1;
    }
    
    int forkResult = fork();

    if(forkResult < 0){
        printf("lab2p2f: Fork Failed!\n");
        return 1;
    }

    if(forkResult > 0){ //Parent process (does talk as can wait)
        wait(NULL); //WAIT, THEY DON'T LOVE U LIKE I LOVE U

        int intermediateFd = open("./temp.txt", O_RDONLY);
        int writeFd = open("./results.out", O_CREAT | O_WRONLY);

        //execlp("./talk", "talk", NULL);

        close(intermediateFd);


    } else{ //Child process (does slow as cannot wait)
        //"./" refers to the curr directory
        //O_CREAT flag to create file if it does not alr exist
        int intermediateFd = open("./temp.txt", O_CREAT | O_WRONLY);

        dup2(intermediateFd, STDOUT_FILENO);

        execlp("./slow", "slow", "5", NULL);

        close(intermediateFd);
    }
}

