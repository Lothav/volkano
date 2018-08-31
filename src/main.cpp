#include <iostream>
#include "Volkano.hpp"

int main(int argc, char* argv[])
{
    vkn::Volkano::init();

    vkn::Volkano::cleanup();

    return EXIT_SUCCESS;
}
