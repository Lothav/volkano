//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_WINDOW_HPP
#define VOLKANO_WINDOW_HPP

#include <memory>
#include <cassert>
#include <iostream>
#include "Surface.hpp"
#include "XCBSurface.hpp"

namespace vkn
{
    class Window
    {

    private:

        static std::shared_ptr<Surface> surface;

    public:

        static void init();
        static void destroy();

        static const char* getSurfaceName();

    };
}

#endif //VOLKANO_WINDOW_HPP
