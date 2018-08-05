#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include "tcp.h"

namespace TCP {
  TCP_C::TCP_C(std::string hostname,std::string service){
    struct sockaddr_in servaddr;
    int err, n, i;                         
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//use name creat struct by hostname 
    struct addrinfo set,ret,*result;
    set.ai_flags       = AI_CANONNAME;
    set.ai_family     = AF_INET;
    set.ai_socktype = SOCK_STREAM;
    set.ai_protocol  = IPPROTO_TCP;
    result = &ret;
    err =  getaddrinfo(hostname.c_str(),service.c_str(),&set,&result);
    if(!err) 
    err = connect(socket_fd, (struct sockaddr *)result->ai_addr,
            sizeof(*(result->ai_addr)));
    if(err != 0 ) {
       socket_fd = -1;
    } else {
      freeaddrinfo(result);
    }
}
/* Write to a valid socket 
*  Paramater data you want to send and len is length of data
*  If filed descriptor is invalid then returned -1 
*  Else returned a length of how many data to write.
*/
int TCP_C::Send(void * data,int len) {
    if( socket_fd <= 0) 
      return -1;
    else {
      int size = 0,i=0;
      for(i;i<len;i+=size){
          const char * p  =((char *)data)+i;
					size = write(socket_fd,p,len-size);
          if(size == 0){
             return i;
          }
       }
     return i;
   }
}

int TCP_C::Recv(void * buf,int len){
    memset(buf,0,len);
    if( socket_fd <= 0)
       return -1;
    else { 
       int size=0 ,i=0;
       for( i;i<len;i+=size){
          char * p  =((char *)buf)+i;
          size = read(socket_fd,p,len-size);
       }
    return i;
    }
}

TCP_C::~TCP_C(){
  if(socket_fd >0 ){
    close(socket_fd);
  }
}

} //namaspace ene
