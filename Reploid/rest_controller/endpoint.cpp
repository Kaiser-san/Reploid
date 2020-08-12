#include "endpoint.hpp"

namespace reploid {

    Endpoint::Endpoint(EndpointType endpoint_type, utility::string_t route, void(*function)(http_request request))
	        :endpoint_type_(std::move(endpoint_type)), route_(std::move(route)), function_(std::move(function))
    {
    }

    Endpoint::~Endpoint()
    {
    }

	EndpointKey Endpoint::getKey() const
	{
        return EndpointKey(endpoint_type_, route_);
	}

    EndpointType Endpoint::endpointType() const
    {
	    return endpoint_type_;
    }

    utility::string_t Endpoint::route() const
    {
	    return route_;
    }

    void(* Endpoint::function() const)(http_request request)
    {
	    return function_;
    }
}
