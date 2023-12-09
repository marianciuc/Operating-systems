// SO IS1 222A LAB08
// Volodymyr Marianchuk
// mv53868@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define MAX_LENGTH 25

void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int main(int argc, char *argv[]){
    if (argc != 2 || strlen(argv[1]) > MAX_LENGTH) {
        error("Invalid number or length of arguments: ");
    } 

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            error("Argument must contain only decimal digits");
        }
    }

    if (strlen(argv[1]) == 1){
        return argv[1][0] - '0';
    }

    int length = strlen(argv[1]);
    char first_half[(int) ceil(length / 2) + 1];
    char second_half[(int) floor(length / 2) + 1];

    strncpy(first_half, argv[1], ceil(length / 2));
    strcpy(second_half, argv[1] + (int) floor(length / 2));

    pid_t pid_first  = fork();
    pid_t pid_second = fork();

    if (pid_first == 0) {
         execl("lab8", "lab8", first_half, (char *)NULL);
    } else if (pid_second == 0) {
        execl("lab8", "lab8", second_half, (char *)NULL);
    }

    int status1, status2;

    pid_first  = wait(&status1);
    pid_second = wait(&status2);

    printf("%d\t%d \t\t%5d %d\n", getpid(), pid_first, atoi(first_half), WEXITSTATUS(status1));
    printf("%d\t%d \t\t%5d %d\n", getpid(), pid_second, atoi(second_half), WEXITSTATUS(status2));

    exit(WEXITSTATUS(status1) + WEXITSTATUS(status2));
}
