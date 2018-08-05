/* 
*  When new object created you need to set some parameter
*  When have new connected the cb_function will be perform
*  The void pointer will be a file descriptor of new connect   
*/
#pragma once
#include <string>
#include <iostream>
#include <sys/epoll.h>
#include <map>

namespace TCP{
class TCP_S {  
  public:
    TCP_S(void*(*cb_function)(void *),int maxEPFD,
          int maxCLI,int port,int backlog);
    ~TCP_S();
    int Run();  
    int Getcount(); 
  private:
    int MAXEPOLLFD;
    int LISTENPORT;
    
    int listen_fd;
    int epoll_fd;
    struct  epoll_event event,*events;
    void *(*callback)(void *);            // call back function

    std::map<int,struct sockaddr>  list;  //connect list
    std::map<int,struct sockaddr>::iterator  iter; 

    int create_listen(int backlog);          
    int setnonblcoking(int *);
 };

} // namespcae end
