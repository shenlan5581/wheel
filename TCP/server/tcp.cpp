#include  <sys/epoll.h>
#include  <fcntl.h>
#include  <netdb.h>
#include  <string.h>
#include  <unistd.h>
#include "tcp.h"
namespace TCP{
TCP_S::TCP_S(void*(*cb_function)(void *),int maxEPFD,
                    int maxCLI,int port,int backlog){
      int err;
      callback = cb_function;
      MAXEPOLLFD = maxEPFD;
      LISTENPORT =  port;

      events =(struct epoll_event *)malloc(sizeof(struct epoll_event)*MAXEPOLLFD); 
      memset(events,0,MAXEPOLLFD);
      err =  create_listen(backlog);
      if(err == -1) {
         listen_fd = -1;
         return ;
      }
      setnonblcoking(&listen_fd);            // 非阻塞模式
      event.data.fd = listen_fd;
      event.events = EPOLLIN | EPOLLET;
      epoll_fd = epoll_create(MAXEPOLLFD);   //epoll
      err = epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&event);
      if(epoll_fd <  0 ||  err <0) {
         listen_fd = -1;
      }
}

int TCP_S::Run() {   
    if(listen_fd == -1) {
      std::cout<<"listen error"<<std::endl;
      return -1;
    }
    std::cout<<"****Running****"<<std::endl;
    struct sockaddr    addr;
           socklen_t   len;  
    int client;

    while(1) { 
        int i,n;
        memset(events,0,sizeof(struct epoll_event)*MAXEPOLLFD);
        n = epoll_wait(epoll_fd,events,MAXEPOLLFD,-1);
        for(i =0; i < n ; i++) { 
            if(events[i].data.fd == listen_fd) {    //new clinet       
                client=accept(listen_fd,&addr,&len); 
               if(client< 0)
                  continue;
                  list[client]=addr; //save addr
                  setnonblcoking(&client);
                  event.data.fd = client;
                  event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;  
                  epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client,&event);

            } else if(events[i].events & EPOLLRDHUP) {   //closed                
                  iter = list.find(events[i].data.fd);
                  list.erase(iter);
                  close(events[i].data.fd);              
                  epoll_ctl(epoll_fd,EPOLL_CTL_DEL,events[i].data.fd,NULL);

            } else if(events[i].events & EPOLLIN ) {     // read
							 int client = int(events[i].data.fd);
										callback((void*)&client);
            }
        } 
    }
}

int TCP_S::setnonblcoking(int * fd) { 
      int flags;
      flags = fcntl(*fd,F_GETFL,0);
      fcntl(*fd,F_SETFL,flags | O_NONBLOCK);
      return 0;
 }
 
 int TCP_S::create_listen(int backlog) {  //return listen file descriptor 
      int fd;
      int err;  
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(LISTENPORT);
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      fd= socket(AF_INET, SOCK_STREAM, 0);
  
      err = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
      if(err <0) 
         return -1;
      err = listen(fd,backlog);
      if(err <0)  
        return -1;   
      listen_fd = fd;
  return fd;
 }

int  TCP_S::Getcount(){
     return list.size();
}

 TCP_S::~TCP_S(){

 }
}  // namespace end
