#pragma once

#include "common.hpp"
#include "endpoint.hpp"
#include <cpprest/http_listener.h>

#include <pplx/pplxtasks.h>


using namespace web;
using namespace http;
using namespace http::experimental::listener;

namespace reploid {
    /// <summary>
    /// An abstract Controller that basically represents a collection of <see cref="Endpoint"/>s.
    /// When a call is made to the API, it routes the call to the <see cref="Endpoint"/> which then executes the requested function.
    /// All functions should be written inside the specific Controller.
    /// </summary>
    class Controller {
    private:
        utility::string_t route_;
        std::unique_ptr<http_listener> listener_;
        std::unique_ptr<std::unordered_map<EndpointKey, std::unique_ptr<Endpoint>>> endpoints_;
    public:
        /// <summary>
        /// The base constructor for the Controller class.
        /// </summary>
        /// <param name="route">The route at which the controller is listening. </param>
        /// <returns></returns>
        Controller(utility::string_t route);
        ~Controller();

        /// <summary>
        /// Returns the route for this Controller.
        /// </summary>
        utility::string_t route() const;

        /// <summary>
        /// Start listening on the specified route.
        /// </summary>
        /// <returns>The task upon which we can wait.</returns>
        pplx::task<void> accept();

        /// <summary>
        /// Shuts down the Controller.
        /// </summary>
        /// <returns>The task upon which we can wait.</returns>
        pplx::task<void> shutdown();

    private:
        void initRestHandlers();

        virtual void initEndpoints() = 0;

        void addEndpoint(const Endpoint& endpoint);
    	
        void addEndpoints(const std::vector<Endpoint>& endpoint);

        void handleGet(http_request request);

        std::vector<utility::string_t> requestPath(const http_request& message);
    };
}
