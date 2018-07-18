/*
*
*
*/
#include <string>
#include <iostream>

namespace TCP{

class TCP_C {
  public:
      TCP_C(std::string addr,int port);
      int Send(void *);
      int Recv(void *){};
  private:
      int socket_fd;
};

/*
class Tcp_S : public Tcp {
  public:
          TCP_S(    );
      int Send(void *){};
      int Recv(void *){};
  private:
      int Init()=0;
};

*/

}// namespace end
