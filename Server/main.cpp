//
// Created by erwan on 9/29/23.
//

#include "server.h"

int main()
{
    server srv(3030);
    srv.start();
    std::cout << "Server started" << std::endl;
    while (true) {
        srv.update(5, true);
    }
}
