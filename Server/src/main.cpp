/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** main
*/

#include <iostream>
#include <haze.hpp>
#include "Engine.hpp"

int main()
{
    std::cout << "Calling the engine!" << std::endl;
    Haze::Engine engine;
    engine.init();
    engine.update();
    return 0;
}
