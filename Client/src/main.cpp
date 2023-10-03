/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** main
*/

#include "Component.hpp"
#include "GraphicClient.hpp"
#include <haze-core.hpp>
#include "./Rttype.hpp"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Rttype rtype;
    rtype.run();
    return 0;
}
