/*
   Very first fcgi client, copied from
   http://yaikhom.com/2014/09/13/lean-web-services-using-c-fast-cgi-and-mysql.html
*/

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int count = 0;

    char buffer [10];

    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:8888");

    while(FCGI_Accept() >= 0) {
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);

        printf("Content-type: text/html\r\n\r\n"
               "Hamster says %s on host <i>%s</i>\n",
               buffer, getenv("SERVER_NAME"));

    }

    zmq_close (requester);
    zmq_ctx_destroy (context);

    return 0;
}
