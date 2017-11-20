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

    int counted_so_far = 0;

    int step_counter = 0;

    char listener_address[16];

    memset(listener_address, 0, 16);

    snprintf(listener_address, sizeof(listener_address), "tcp://*:%d", HAMSTER_PORT);

    printf("Hamster is happily running and counting on port %d.\n", HAMSTER_PORT);

    int rc = zmq_bind (responder, listener_address);
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);

        counted_so_far++;
        step_counter++;

        if (step_counter >= 5000) {
           printf("counted so far: %d\n", counted_so_far);
           step_counter = 0;
        }

        zmq_send (responder, "ok", 2, 0);
    }
    return 0;
}
