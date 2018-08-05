
//test

#include <iostream>
#include <string>
#include <string.h>

#include "tcp.h"
using std::string;
int main() {
string req;
 
for (  ;  ; ) {
string dest,service;
  std::cout<<"putin hostname\n";
  std::cin>>dest;
if(dest == "exit")
   return 0;
  std::cout<<"putin service\n";
  std::cin>>service;
TCP::TCP_C tcp(dest,service);
req =      "GET / HTTP/1.1\n";
req =req + "Accept:*/*\n";
req =req + "Host:\"61.135.169.121\"\n";
req =req + "Accept-Encoding:\"gzip,deflate\"\n";
req =req + "Connection:Keep-Alive\n";
req =req + "\n";
req =req + "\n";
if( tcp.Send((void*)req.c_str(),req.length()) > 0)
  std::cout<<"ok";
else 
  std::cout<<"failed";
char buf[150];
tcp.Recv(buf,150);
std::cout<<buf<<"\n*** ***"<<std::endl;
 
}

return 0;
}

