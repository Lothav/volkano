#include <iostream>
#include "engine/Instance.hpp"
#include "engine/Debug.hpp"

int main(int argc, char* argv[])
{

    vkn::Window::init();
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
    }
    vkn::Window::destroy();

    return EXIT_SUCCESS;
}
