//  ZeroMQ-base Hamster server, largely copied from http://zguide.zeromq.org/c:hwserver

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define HAMSTER_PORT 8888

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);

    char listener_address[16];

    memset(listener_address, 0, 16);

    snprintf(listener_address, sizeof(listener_address), "tcp://*:%d", HAMSTER_PORT);

    printf("Hamster is happily running and counting on port %d.\n", HAMSTER_PORT);

    int rc = zmq_bind (responder, listener_address);
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}
