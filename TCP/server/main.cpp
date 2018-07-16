
#include  <stdio.h>
#include  <unistd.h>
#include "tcp.h"

void * cb(void* client){
    int * cli =(int*)client;
   char buf[50];
    read(*cli,buf, 50);
    write(1,buf,50);
}



int main(){

TCP::TCP_S   server(cb,100,1000,80,1000);
server.Run();
}