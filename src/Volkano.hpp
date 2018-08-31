//
// Created by luiz0tavio on 8/31/18.
//

#ifndef VOLKANO_VOLKANO_HPP
#define VOLKANO_VOLKANO_HPP

#include "engine/Device.hpp"
#include "engine/Debug.hpp"
#include "engine/window/Window.hpp"

namespace vkn
{
    class Volkano
    {

    public:

        static void init() noexcept;

        static void draw() noexcept {}

        static void cleanup() noexcept;
    };
}

#endif //VOLKANO_VOLKANO_HPP
