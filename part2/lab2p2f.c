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

    if(pipe(pipeFdArr) == -1){ //If pipe fails...
        perror("lab2p2f: ");
        return 1;
    }
    
    int forkResult = fork();

    if(forkResult == -1){ //If fork fails...
        perror("lab2p2f: ");
        return 1;
    }

    ///"./" refers to the curr directory
    if(forkResult > 0){ //Parent process (does talk as can wait, ./talk < results.out > results.out [(a < b) > c, > instead of >> so overwrite instead of append])
        wait(NULL); //WAIT, THEY DON'T LOVE U LIKE I LOVE U

        /*int myReadFd = open("./results.out", O_RDONLY);
        int myWriteFd = open("./results.out", O_WRONLY);

        dup2(myReadFd, STDIN_FILENO);
        dup2(myWriteFd, STDOUT_FILENO);

        execlp("./talk", "talk", NULL);

        close(myReadFd);
        close(myWriteFd);*/

        //        int savedStdoutFd = dup(STDOUT_FILENO);
        //dup2(savedStdoutFd, STDOUT_FILENO); //Restore file descriptor of stdout
    } else{ //Child process (does slow as cannot wait, ./slow 5 > results.out)
        int myFd = open("./results.out", O_CREAT | O_WRONLY); //O_CREAT flag to create file if it does not alr exist

        if(myFd == -1){ //If open fails...
            perror("lab2p2f: ");
            return 1;
        }

        dup2(myFd, STDOUT_FILENO);

        execlp("./slow", "slow", "5", NULL);

        //* If execlp fails... (only runs if so)
        close(myFd);

        perror("lab2p2f: ");

        return 1;
        //*/
    }
}

