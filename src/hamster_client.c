//  Hello World client, adapted from http://zguide.zeromq.org/c:hwclient

#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to Hamster server...\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:8888");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 100000; request_nbr++) {
        char buffer [10];
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
