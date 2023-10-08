
#include "utils_v2.h"
#include "network.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>



int initSocketClient(int* sockFdPtr, int serverPort, const char* ipAddress) 
{

  struct sockaddr_in addr;
  memset( &addr, 0, sizeof(addr) ); 
  addr.sin_family = AF_INET;
  addr.sin_port = htons(serverPort);
  inet_aton(ipAddress, &addr.sin_addr);

 
  *sockFdPtr = ssocket();
  if(connect(*sockFdPtr, (struct sockaddr *) &addr, sizeof(addr)) == -1) return -1;
  return 0;
}

int initSocketServer(int serverPort)
{
  int ports[] = PORTS_LIST;
  int taillePortsList =(sizeof(ports) / sizeof(ports[0]));
  int socket = ssocket();

  if(serverPort == -1){
    for (int i = 0; i < taillePortsList; i++) {
      int serverPort = ports[randomIntBetween(0,taillePortsList-1)];
      if (sbind(serverPort, socket) == 0) {
        printf("Bound to port %d\n", serverPort);
        break;
      }
    }
  }else{
    sbind(serverPort, socket) ;
    printf("Bound to port %d\n", serverPort);
  }

  slisten(socket,5);
  return socket;
}