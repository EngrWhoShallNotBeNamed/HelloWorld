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

int listen_fd;
int connection_fd;

void sig_handler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nReceived SIGINT\n");

    if (listen_fd !=0){
        printf("\nClosing listen File Descriptor\n");
        close(listen_fd);
    }

    if (connection_fd !=0){
        printf("\nClosing connection File Descriptor\n");
        close(connection_fd);
    }

    printf("\nGoodBye World!\n");
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigaction( signo, &sa,NULL);
    raise(signo);
  }

}
// Network includes
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism

// Creating a Packet structure
typedef struct
{
    double dR_ITRF[3];
    double dV_ITRF[3];
} __attribute__((__packed__)) GPS_type_t;

int main(int argc, char **argv) {
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

// Begin network UDP Server

 if ( (listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ) {
     perror( "socket failed" );
     return 1;
 }

 struct sockaddr_in serveraddr;
 memset( &serveraddr, 0, sizeof(serveraddr) );
 serveraddr.sin_family = AF_INET;
 serveraddr.sin_port = htons( 9002 );

 uint8_t ip_addrD[4] = {127, 0, 0, 1}; // Because we are in a little endian machine...
 in_addr_t local = {0};
 memcpy(&local, ip_addrD, sizeof(local));
 serveraddr.sin_addr.s_addr = local ;

 if ( bind(listen_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
     perror( "bind failed" );
     return 1;
 }

 if(listen(listen_fd, 5) < 0){
     printf("\nFailed to listen\n");
 }
     struct sockaddr_in sa_in;
     size_t length = sizeof(sa_in);
     connection_fd = -1;

    // Wait for a connection to be accepted
    while (connection_fd < 0)
    {
        connection_fd = accept(listen_fd, (struct sockaddr *) &sa_in, (socklen_t *) &length);
    }
    printf("\nWe Accepted What do I do now?\n");
    close(listen_fd); // Stop listening for new connections

    uint8_t in_addrD[4] ={0};
    memcpy(in_addrD, &sa_in.sin_addr, sizeof(sa_in.sin_addr));
    printf("Accepted Connection from: %d.%d.%d.%d\n", in_addrD[0], in_addrD[1], in_addrD[2],in_addrD[3]);
    printf("On Port: %d", ntohs(sa_in.sin_port));

    // Create the packet
    GPS_type_t pkt = {0};
    pkt.dR_ITRF[0]=0.0;
    pkt.dR_ITRF[1]=10.0;
    pkt.dR_ITRF[2]=20.0;

    pkt.dV_ITRF[0]=30.0;
    pkt.dV_ITRF[1]=40.0;
    pkt.dV_ITRF[2]=50.0;

    // Attempt to send data.
    int totalByteSent = 0;
    while (totalByteSent >= 0){

        printf("\nAttempt to write bytes!\n");
        totalByteSent = write(connection_fd, &pkt, sizeof(pkt));

        pkt.dR_ITRF[0]+=1.0;
        pkt.dR_ITRF[1]+=1.1;
        pkt.dR_ITRF[2]+=1.2;

        pkt.dV_ITRF[0]+=1.3;
        pkt.dV_ITRF[1]+=1.4;
        pkt.dV_ITRF[2]+=1.5;
        printf("\nSent %d Bytes \n", totalByteSent);
        sleep(1);
    }

    printf("\nReached the end. Calling the end function\n");

    // Note: Try not to Ctnl+C after a connection has been made and sending bytes? IDK why.
    sig_handler(SIGINT);

	return EXIT_SUCCESS;
}
