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

    ///"./" refers to the curr directory
    if(forkResult > 0){ //Parent process
        close(pipeFdArr[0]); //Close reading end

        dup2(pipeFdArr[1], STDOUT_FILENO); //Output now goes to writing end instead of stdout

        execlp("./slow", "slow", "5", NULL);

        //* If execlp fails... (only runs if so)
        perror("\nExeclp Failed!");

        puts("");

        return 1;
        //*/








        int status;

        printf("here");

        if(wait(&status) == -1){ //WAIT, THEY DON'T LOVE U LIKE I LOVE U
            close(myFd);

            perror("\nWait Failed!");

            puts("");

            return 1;
        }

        printf("here1");

        close(myFd); //Must be after wait as child uses myFd, must be before status check as still need to close myFd if child's execlp failed

        if(status == 1){ //If child's execlp failed... (printing alr done by child)
            return 1;
        }

        printf("here2");

        //myFd = open("./results.out", O_RDWR); //??

        //dup2(myFd, STDIN_FILENO);
        //dup2(myFd, STDOUT_FILENO);

        //execlp("./talk", "talk", NULL);

        //??
    } else{ //Child process
    }
}

