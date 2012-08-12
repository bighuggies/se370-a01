/* 
 * File:   a1.1.c
 * Author: Robert Sheehan
 *
 * Created on 11 July 2012, 2:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define TICKETS 100000000
int numThreads = 0;

int ticket = -1;
int usedTickets[TICKETS];

// all threads try to get some of the tickets
void *grabATicket(void *unused) {
  int i;
  bool ticketsReused = false;

  for (i = 0; i < TICKETS / numThreads; i++) {
    ticket++;

    int localTicket = ticket;

    if (usedTickets[localTicket])
      ticketsReused = true;

    usedTickets[localTicket] = 1;
  }

//  if (ticketsReused)
//    puts("At least one ticket was reused.");
  return NULL ;

}

int main(int argc, char *argv[]) {
  numThreads = atoi(argv[1]);
  printf("%d,", numThreads);

  pthread_t threads[numThreads];

  int i;

  for (i = 0; i < numThreads; i++)
    pthread_create(&threads[i], NULL, grabATicket, NULL );

  for (i = 0; i < numThreads; i++)
    pthread_join(threads[i], NULL );

  printf("%d", ticket + 1);

  return EXIT_SUCCESS;
}
