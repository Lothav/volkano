#include <iostream>
#include "engine/Instance.hpp"
#include "engine/Debug.hpp"

int main(int argc, char* argv[])
{
    vkn::Instance::init();
    {
#ifdef DEBUG
        vkn::Debug::init();
        {
#endif


#ifdef DEBUG
        }
        vkn::Debug::destroy();
#endif
    }
    vkn::Instance::destroy();

    return EXIT_SUCCESS;
}
