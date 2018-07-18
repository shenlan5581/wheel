
//test

#include <iostream>
#include <string>

#include "tcp.h"

int main() {
TCP::TCP_C tcp("127.0.0.1",80);
char K[] = "xingke";

tcp.Send((void*)K);
return 0;
}

