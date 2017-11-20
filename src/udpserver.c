/*
    Largely inspired to (or copied from) here:
    http://www.binarytides.com/programming-udp-sockets-c-linux/
*/

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

// https://stackoverflow.com/questions/19472546/implicit-declaration-of-function-close
#include <unistd.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    // where we keep track of the counted tickets
    unsigned long long int counter = 0;

    struct sockaddr_in si_me, si_other;
    
    unsigned int slen; 

    int s, i = sizeof(si_other) , recv_len;

    char buf[BUFLEN];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    printf("Hamster is happily running and counting on port %d.\n", PORT);

    //keep listening for data
    while(1)
    {
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        counter++;
        //print details of the client/peer and the data received
        //printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        //printf("Data: %s\n" , buf);
         
        //now reply the client with the same data
        //printf("sending %lu bytes\n", sizeof(counter));
        if (sendto(s, &counter, sizeof(counter), 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
    }
 
    close(s);

    return 0;
}
