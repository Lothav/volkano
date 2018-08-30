//
// Created by luiz0tavio on 8/30/18.
//

#ifndef VOLKANO_XCBWINDOW_HPP
#define VOLKANO_XCBWINDOW_HPP

#include "../Instance.hpp"
#include "Surface.hpp"
#include <memory>
#include <vulkan/vulkan.h>
#include <iostream>

namespace vkn
{
    class XCBSurface : Surface
    {

    private:

        static std::shared_ptr<Surface> class_instance;

        xcb_screen_t* 			screen{};
        xcb_window_t 			window{};
        xcb_connection_t*		connection{};

        XCBSurface()
        {
            Surface::width  = 800;
            Surface::height = 600;
        };

    public:

        static std::shared_ptr<Surface> getInstance();
        const char* getSurfaceName() override;

        void initWindow() override
        {
            const xcb_setup_t *setup;
            xcb_screen_iterator_t iter;
            int scr;

            connection = xcb_connect(nullptr, &scr);
            if (connection == nullptr || xcb_connection_has_error(connection)) {
                std::cout << "Unable to make an XCB connection\n";
                exit(-1);
            }

            setup = xcb_get_setup(connection);
            iter = xcb_setup_roots_iterator(setup);
            while (scr-- > 0) xcb_screen_next(&iter);

            screen = iter.data;
            uint32_t value_mask, value_list[32];

            window = xcb_generate_id(connection);

            value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
            value_list[0] = screen->black_pixel;
            value_list[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS |
                            XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
                            XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION;

            xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, width, height, 0,
                              XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, value_mask, value_list);

            /* Magic code that will send notification when window is destroyed */
            xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS");

            {
                std::unique_ptr<xcb_intern_atom_reply_t> reply (xcb_intern_atom_reply(connection, cookie, 0));
                xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");

                std::unique_ptr<xcb_intern_atom_reply_t> atom_wm_delete_window (xcb_intern_atom_reply(connection, cookie2, 0));
                xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, (*reply).atom, 4, 32, 1, &(*atom_wm_delete_window).atom);
            }

            xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window,
                                XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(APP_NAME), APP_NAME);

            xcb_flush(connection);

            xcb_map_window(connection, window);

            // Force the x/y coordinates to 100, 100 results are identical in consecutive runs
            const uint32_t coords[] = {100, 100};
            xcb_configure_window(connection, window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, coords);
            xcb_flush(connection);
        }

        void initSurface() override
        {
            VkXcbSurfaceCreateInfoKHR createInfo = {};
            createInfo.sType 		= VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
            createInfo.pNext 		= nullptr;
            createInfo.connection 	= connection;
            createInfo.window 		= window;

            VkResult res = vkCreateXcbSurfaceKHR(vkn::Instance::instance, &createInfo, nullptr, &surface);
            assert(res == VK_SUCCESS);
        }

        void destroySurface() override
        {
            vkDestroySurfaceKHR(Instance::instance, surface, nullptr);
        }

        void destroyWindow() override
        {
            xcb_destroy_window(connection, window);
            xcb_disconnect(connection);
        }

    };
}

#endif //VOLKANO_XCBWINDOW_HPP
