#pragma once


#include <string>
#include "common.hpp"
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>

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

            void setEndpoint(const utility::string_t& value);
            utility::string_t endpoint() const;

            pplx::task<void> accept();
            pplx::task<void> shutdown();

            virtual void initRestOpHandlers()
            {
                _listener.support(methods::GET, std::bind(&Controller::handleGet, this, std::placeholders::_1));
            }
    	
            void handleGet(http_request message);


            std::vector<utility::string_t> requestPath(const http_request& message);
    };
}