//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_SURFACE_HPP
#define VOLKANO_SURFACE_HPP

namespace vkn
{
    class Surface
    {

    protected:

        Surface() = default;

    public:

        virtual const char* getSurfaceName() { return nullptr; }
    };
}

#endif //VOLKANO_SURFACE_HPP
