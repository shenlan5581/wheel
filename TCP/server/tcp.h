
#pragma once
#include <string>
#include <iostream>
#include <sys/epoll.h>

namespace TCP{
class TCP_S {  
  public:
    TCP_S(void*(*cb_function)(void *),int maxEPFD,
                    int maxCLI,int port,int backlog);
    ~TCP_S();
    int Run();  
  private:
    int MAXEPOLLFD;
    int LISTENPORT;

    int     listen_fd;
    int     epoll_fd;
    struct epoll_event event,*events;

    int create_listen(int backlog);          
    int setnonblcoking(int *);
    void *(*callback)(void *);  
 };

} // namespcae end
