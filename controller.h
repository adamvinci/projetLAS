#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

/**
 * PRE:  sockets : a pointer to a socket file descriptor array
 *       nbSocket : a pointer to the number of sockets in the array
 * POST: read the responses of each sockets and print it on the standart output
 * RES:  /
 */
static void read_response(void* sockets, void* nbSocket);



/**
 * PRE:  sockets : a pointer to a socket file descriptor array
 *       nbSocket : a pointer to the number of sockets in the array
 * POST: send the command  to each sockets in the array.
 * RES:  /
 */
  void send_commande(int* sockets, int nbSocket,char*commande);



#endif
