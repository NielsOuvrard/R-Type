//
// Created by erwan on 9/29/23.
//

#include "server.h"

int main(int ac, char **av)
{
    server srv(3030);
    srv.start();
    if (ac == 2 && std::string(av[1]) == "-p") {
        srv.is_pong = true;
    }
    std::cout << "Server started" << std::endl;
    while (true) {
        srv.update(5, true);
    }
}
