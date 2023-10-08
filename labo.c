#include "utils_v2.h"
#include "network.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <string.h>

#define BUFFERSIZE 1024

volatile sig_atomic_t end = 0;

static void spawn_zombie() {
execl("./zombie", "zombie", (char*)NULL);
}

void handler() {
    end = 1;
}

int main(int argc, char const *argv[]) {
    ssigaction(SIGUSR1, handler);

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        spawn_zombie();
        
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        spawn_zombie();
    }

    char bfr[BUFFERSIZE];

    pid_t pid = getpid();
    while (!end) {
        if (fgets(bfr, 1024, stdin) == NULL) {
            skill(pid,SIGUSR1);
        }else{
            continue;
        }
    }

    skill(pid1, SIGINT);
    skill(pid2, SIGINT);
    swaitpid(pid1, NULL, 0);
    swaitpid(pid2, NULL, 0);
    

    return 0;
}