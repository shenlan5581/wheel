
#include  <stdio.h>
#include  <unistd.h>
#include "tcp.h"

void * cb(void* client){
    int * cli =(int*)client;
    int readlen =300;
    char buf[readlen];
    read(*cli,buf, readlen);
    write(1,buf,readlen);
}


int main(){

TCP::TCP_S   server(cb,100,1000,80,1000);
server.Run();
}
