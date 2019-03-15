/*
 ============================================================================
 Name        : main.c
 Author      : Gerald Alaniz
 Version     :
 Copyright   : Hello world with cleanup
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <signal.h>

static struct sigaction sa;

void sig_handler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nReceived SIGINT\n");
    printf("\nGoodBye World!\n");
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigaction( signo, &sa,NULL);
    raise(signo);
  }

}
int main(void) {
   printf("\n!!!Hello World!!!\n"); /* prints !!!Hello World!!! */

    // Register SIGINT Handler
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    if (sigaction(SIGINT, &sa, 0))
    {
    	printf("\ncan't catch SIGINT\n");
    }

 union {
     int i;
     char c[sizeof(int)];
 } foo;

 foo.i = 1;
 if (foo.c[0] == 1)
     printf("Little endian\n");
 else
     printf("Big endian\n");

    while (1)
    {
      printf("\nStep...\n");
      sleep(1);
    }

	return EXIT_SUCCESS;
}
