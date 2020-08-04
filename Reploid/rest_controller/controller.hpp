#pragma once


#include <string>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>
#undef U
#include <pplx/pplxtasks.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

namespace reploid {
    /// <summary>
    /// An abstract class representing a collection of <see cref="Endpoint{RValue}"/>s.
    /// </summary>
    class Controller {
        protected:
            http_listener _listener; // Main micro service network endpoint.
        public:
            Controller();
            ~Controller();

            pplx::task<void> accept();
            pplx::task<void> shutdown();

            virtual void initRestOpHandlers() = 0;


            std::vector<utility::string_t> requestPath(const http_request& message);
    };
}