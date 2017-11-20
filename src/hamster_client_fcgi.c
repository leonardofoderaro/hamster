/*
   Very first fcgi client, copied from
   http://yaikhom.com/2014/09/13/lean-web-services-using-c-fast-cgi-and-mysql.html
*/

#include <fcgi_stdio.h>
#include <stdlib.h>
int main(void)
{
    int count = 0;
    while(FCGI_Accept() >= 0)
        printf("Content-type: text/html\r\n\r\n"
               "Request number %d on host <i>%s</i>\n",
               ++count, getenv("SERVER_NAME"));
    return 0;
}
