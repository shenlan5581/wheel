
//test

#include <iostream>
#include <string>
#include <string.h>

#include "tcp.h"
using std::string;
int main() {
TCP::TCP_C tcp("47.94.154.159",80);

string req;

req = "GET / HTTP/1.1\n";
req =req + "Accept:*/*\n";
req =req + "Host:k@linux\n";
req =req + "Connection:Keep-Alive\n";
req =req + "\n";
req =req + "\n";

if( tcp.Send((void*)req.c_str(),req.length()) > 0)
  std::cout<<"ok";
else 
  std::cout<<"failed";

char buf[350];
tcp.Recv(buf,350);

std::cout<<buf;

return 0;
}

