

/*

** ADAM BARHDADI

** ELIAS ZEMMOURI

** STEVEN AGBASSAH


*/
#include "utils_v2.h"
#include "network.h"
#include "controller.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>

#define BUFFERSIZE 1024

#define NOMBREIP 10

#define NOMBREZOMBIE 10

 void send_commande(int *sockets,int nbSocket,char *commande) {

  for(int i=0;i<nbSocket;i++){
    swrite(sockets[i],commande,strlen(commande)+1);
  }

  
}



static void read_response(void* sockets, void* nbSocket) {
  int* socketPtr = (int*)sockets;
  int* socketArray = socketPtr;

  int* ptr1 = (int*)nbSocket;
  int nbreSocket = *ptr1;

  struct pollfd fds[NOMBREZOMBIE];
    int nbreSocketInvalide = 0;
  char buffer[BUFFERSIZE];

  // Initialize pollfd structure for each socket
  for (int i = 0; i < nbreSocket; i++) {
    fds[i].fd = socketArray[i];
    fds[i].events = POLLIN;
  }

  while (1) {
     spoll(fds, nbreSocket, -1);
   
    for (int i = 0; i < nbreSocket; i++) {
      if (fds[i].revents & POLLIN) {
        int bytes_read = read(fds[i].fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
          buffer[bytes_read] = '\0';
          printf("\n%s\n", buffer);
        }
        if(bytes_read == 0){
          // un socket est ferme
            sclose(fds[i].fd);
            nbreSocketInvalide++;
          // si il n'y a plus de socket on ferme le subprocess et previent le main process
          if(nbreSocket == nbreSocketInvalide){
          skill(getppid(), SIGINT);
          exit(0);
          }

        }
      }
    }
  }
}






int main(int argc, char const *argv[]) {
  const char *ipAddresses[NOMBREIP];
  int numIPs=0;
  if (argc > 1) {
    numIPs = argc - 1;      
    for (int i = 1; i <= numIPs; i++) {
      ipAddresses[i - 1] = argv[i];
    }

  }else {
    ipAddresses[0] = SERVER_IP;
    numIPs++;
  }


  // try to connect to all know zombie port
  int ports[] = PORTS_LIST;
  int taillePortsList = ( sizeof(ports) / sizeof(ports[0]) );

  int zombieSockets[NOMBREZOMBIE];
  int nbreZombieSocket=0 ;

  for(int x = 0 ; x < numIPs ; x++){
    for ( int i = 0; i < taillePortsList; i++) {

      int sockfd;
      if ( initSocketClient(&sockfd, ports[i], ipAddresses[x])!= -1 ) {
        zombieSockets[nbreZombieSocket++] = sockfd;
        printf("Connected to %s :: %d\n",ipAddresses[x], ports[i]);
      }
      else{
        sclose(sockfd);
      }
    }
  }



  if (nbreZombieSocket == 0) {
    checkNeg(-1,"Could not connect to any zombie\n");
  }

  pid_t chulID = fork_and_run2(read_response,(void*)&zombieSockets,(void*)&nbreZombieSocket);

  while(1){
    char commande[BUFFERSIZE];
    printf("\nEntrer votre commande a envoyer aux zombies: \n");


    if(fgets(commande, 1024, stdin)==NULL){
      skill(chulID,SIGKILL);
      break;
    }


    send_commande(zombieSockets,nbreZombieSocket,commande);

  }
  for(int i=0;i<nbreZombieSocket;i++){
      sclose(zombieSockets[i]);
  }

}

