//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_WINDOW_HPP
#define VOLKANO_WINDOW_HPP

namespace vkn
{
    class Window
    {

    protected:

        Window() = default;

    public:

        virtual const char* getSurface() { return nullptr;};
    };
}

#endif //VOLKANO_WINDOW_HPP
