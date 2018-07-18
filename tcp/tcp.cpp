
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "tcp.h"

namespace TCP {
//C
  TCP_C::TCP_C(std::string addr,int port){
    int sockfd;
    struct sockaddr_in servaddr;
    int err, n, i;                         
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, addr.c_str(), &servaddr.sin_addr);
    connect(socket_fd, (struct sockaddr *)&servaddr,
             sizeof(servaddr));
}
int TCP_C::Send(void * data) {
    if( socket_fd < 0)
    std::cout<<"failed";
    else
    std::cout<<"ok";
}

//S



} //namaspace ene
