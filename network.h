#ifndef _NETWORK_H_
#define _NETWORK_H_

#define SERVER_PORT 9501
#define SERVER_IP "127.0.0.1"
#define PORTS_LIST { 8000, 8001 ,8002,5000,5009,5001}




/**

PRE: sockFdPtr is a pointer to an int variable to store the socket descriptor
  serverPort: server port number
  ipAddress: a valid IPv4 address in string format
POST: initializes a socket client with the given serverPort and ipAddress, and stores the socket file descriptor in sockFdPtr
RES: 0 on success, -1 on failure
*/
int initSocketClient(int* sockFdPtr, int serverPort, const char* ipAddress);


/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 127.0.0.1:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort);

#endif
