//
// Created by erwan on 10/6/23.
//

#include "client.h"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        if (std::string(av[1]) == "sfml") {
            client cli = client(60, 0);
            cli.start();
        } else if (std::string(av[1]) == "sdl") {
            client cli = client(60, 1);
            cli.start();
        }
    } else {
        client cli;
        cli.start();
    }
    return 0;
}