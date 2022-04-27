#include "application.h"

int main(int argc, char** argv)
{
    graphics::initDisplay(&argc, argv,
        graphics::size{ 400, 400 },
        "재미난 게임!"
    );
}