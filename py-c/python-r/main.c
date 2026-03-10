#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 10; i++) {
        pid_t requ = fork();

        if (requ < 0) {
            printf("Fork fallito\n");
            exit(0);
        } else if (requ == 0) {
            execlp("python3", "python3", "req.py", NULL);
            perror("Errore req.py\n");
            exit(1);
        }
    }

    for (int i = 0; i < 10; i++) {
        wait(NULL);
    }

    printf("Spam request finito!\n");

    return 0;
}