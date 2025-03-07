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

    //* Vals can be swapped easily due to indirect indexing (using vars or macros instead of literals to index)
    const int readingEnd = 0;
    const int writingEnd = 1;
    //*/

    int pipeFdArr[2];

    if(pipe(pipeFdArr) == -1){ //If pipe fails...
        perror("\nPipe Failed!");

        puts("");

        return EXIT_FAILURE;
    }

    int childPid = fork();

    if(childPid == -1){ //If fork fails...
        perror("\nFork Failed!");

        puts("");

        return EXIT_FAILURE;
    }

    if(childPid > 0){ //If parent process...
        close(pipeFdArr[writingEnd]); //Close for parent process only

        dup2(pipeFdArr[readingEnd], STDIN_FILENO); //Input now comes from duplicate fd of reading end instead of stdin

        //Can call right after dup2 as closing original instead of duplicate
        close(pipeFdArr[readingEnd]); //Close for parent process only

        if(wait(NULL) == -1){ //If wait fails...
            perror("\nWait Failed!");

            puts("");

            return EXIT_FAILURE;
        }

        //Putting "./results.out" instead leads to outputFd == -1 on 2nd run (not sure why)
        //O_CREAT flag to create file if it does not alr exist
        //O_TRUNC flag to clear file contents if file exists
        //Last 4 digits (<prefix for oct><perms for Owner/User><perms for Group><perms for Others>)
        //Perms: 100 (4, Read) | 010 (2, Write) | 001 (1, Execute) | 000 (0, None)
        int outputFd = open("results.out", O_CREAT | O_TRUNC | O_WRONLY, 0777);

        if(outputFd == -1){ //If open fails...
            perror("\nOpen Failed!");

            puts("");

            return EXIT_FAILURE;
        }

        dup2(outputFd, STDOUT_FILENO); //Output now goes to duplicate outputFd instead of stdout

        //Can call right after dup2 as closing original instead of duplicate
        close(outputFd);

        execlp("./talk", "talk", NULL);
    } else{ //If child process...
        close(pipeFdArr[readingEnd]); //Close for child process only

        dup2(pipeFdArr[writingEnd], STDOUT_FILENO); //Output now goes to duplicate fd of writing end instead of stdout

        //Can call right after dup2 as closing original instead of duplicate
        close(pipeFdArr[writingEnd]); //Close for child process only

        execlp("./slow", "slow", "5", NULL);
    }

    //* If execlp fails... (only runs if so)
    perror("\nExeclp Failed!");

    puts("");

    return EXIT_FAILURE;
    //*/
}

