#pragma once

#include "common.hpp"

using namespace web;
using namespace http;

namespace reploid {
    /// <summary>
    /// A class representing a REST API endpoint.
    /// It listens to only one HTTP method, so if there are different HTTP methods on the same route, multiple Endpoint objects must be created.
    /// </summary>
    class Endpoint {
    private:
        EndpointType endpoint_type_;
        utility::string_t route_;
        void(*function_)(http_request request);
    public:
        /// <summary>
        /// The constructor for the Endpoint class.
        /// </summary>
        /// <param name="route">The route at which the endpoint is listening. It is the relative path added after the controller route.</param>
        /// <param name="endpoint_type">The HTTP method for the endpoint.</param>
        /// <param name="function">The actual function called when a request is made to the specified route. The function itself should call the message.reply function.</param>
        /// <returns></returns>
        Endpoint(EndpointType endpoint_type, utility::string_t route, void(*function)(http_request request));
        ~Endpoint();

        /// <summary>
        /// Returns the key for this Endpoint, for usage in maps.
        /// </summary>
        EndpointKey getKey() const;

        /// <summary>
        /// Returns the <see cref="EndpointType"/>.
        /// </summary>
        /// <returns></returns>
        EndpointType endpointType() const;

        /// <summary>
        /// Returns the relative route. This string is appended to the controller route to make up the full route of the API call.
        /// </summary>
        /// <returns></returns>
        utility::string_t route() const;

        /// <summary>
        /// Returns a pointer to the actual function called when a request is made to the specified route. The function itself should call the message.reply function.
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        void(* function() const)(http_request request);


        Endpoint& operator=(const Endpoint& other)
        {
            endpoint_type_ = other.endpoint_type_;
            route_ = other.route_;
            function_ = other.function_;
        	
            return *this;
        }
    };
}
