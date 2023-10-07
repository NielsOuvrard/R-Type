/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** main
*/

// #include "Rtype.hpp"
#include "server.hpp"

int main(void)
{
    // Rtype rtype;
    // rtype.run();

    server srv(3030);
    srv.start();
    while (true)
    {
        srv.update(5, true);
    }
    return 0;
}
