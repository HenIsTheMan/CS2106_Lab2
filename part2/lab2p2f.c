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
        perror("\nPipe Failed!");

        puts("");

        return 1;
    }
    
    int forkResult = fork();

    if(forkResult == -1){ //If fork fails...
        perror("\nFork Failed!");

        puts("");

        return 1;
    }

    int myFd = open("./results.out", O_CREAT | O_WRONLY); //O_CREAT flag to create file if it does not alr exist

    if(myFd == -1){ //If open fails...
        perror("\nOpen Failed!");

        puts("");

        return 1;
    }

    ///"./" refers to the curr directory
    if(forkResult > 0){ //Parent process (does talk as can wait, ./talk < results.out > results.out [(a < b) > c, > instead of >> so overwrite instead of append])
        int status;

        if(wait(&status) == -1){ //WAIT, THEY DON'T LOVE U LIKE I LOVE U
            close(myFd);

            perror("\nWait Failed!");

            puts("");

            return 1;
        }

        close(myFd); //Must be after wait as child uses myFd, must be before status check as still need to close myFd if child's execlp failed

        if(status == 1){ //If child's execlp failed... (printing alr done by child)
            return 1;
        }

        myFd = open("./results.out", O_RDWR); //??

        dup2(myFd, STDIN_FILENO);
        dup2(myFd, STDOUT_FILENO);

        execlp("./talk", "talk", NULL);

        //??




        //int myReadFd = open("./results.out", O_RDONLY);
        //int myWriteFd = open("./results.out", O_WRONLY);

        //dup2(myReadFd, STDIN_FILENO);
        //dup2(myWriteFd, STDOUT_FILENO);

        //        int savedStdoutFd = dup(STDOUT_FILENO);
        //dup2(savedStdoutFd, STDOUT_FILENO); //Restore file descriptor of stdout
    } else{ //Child process (does slow as cannot wait, ./slow 5 > results.out)
        dup2(myFd, STDOUT_FILENO);

        execlp("./slow", "slow", "5", NULL);

        //* If execlp fails... (only runs if so)
        perror("\nExeclp Failed!");

        puts("");

        return 1;
        //*/
    }
}

