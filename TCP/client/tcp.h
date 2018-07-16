/* 
*  This is a simple TCP protocol client 
*  when you create a new object it need two parameter 
*  It's the host name(IP)  and  the service name (port)
*  Of you want to connect  
*  
*  Function Send and Recv accept a pointer point buffer
*  You want send or recv 
*  The returned is a length of how many data to write or read .
*
*  auther email:22542812@qq.com
*/
#pragma once
#include <string>
#include <iostream>
namespace TCP{

class TCP_C {
  public:
      TCP_C(std::string hostname,std::string service);
      ~TCP_C();
      int Send(void *,int len);
      int Recv(void *,int len);
  private:
      int socket_fd;
 };
}// namespace end
