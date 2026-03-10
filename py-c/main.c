#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        execlp("python3", "python3", "main.py", NULL);
        perror("Errore main.py");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        execlp("python3", "python3", "seconda.py", NULL);
        perror("Errore seconda.py");
        exit(1);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        execlp("python3", "python3", "spam.py", NULL);
        perror("Errore spam.py");
        exit(1);
    }

    // Aspetta entrambi i processi
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("tutti e 3 gli script Python sono stati spenti.\n");
    return 0;
}