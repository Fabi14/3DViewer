#include "Engine.h"


int main(void)
{
    Engine game;
    if (game.init())
    {
        game.run();
    }

    return 0;
}