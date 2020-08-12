#pragma once
#include "common.hpp"
#include "endpoint_type.hpp"
#include <boost/functional/hash.hpp>


namespace reploid {

	/// <summary>
	/// A key that represents an <see cref="Endpoint"/> used in maps.
	/// </summary>
	struct EndpointKey
	{
		EndpointType endpoint_type;
		utility::string_t route;

		EndpointKey(EndpointType endpoint_type, utility::string_t route)
			:endpoint_type(std::move(endpoint_type)), route(std::move(route))
		{}

		EndpointKey(const EndpointKey& other)
			:endpoint_type(other.endpoint_type), route(other.route)
		{}

		~EndpointKey()
		{
		}

		EndpointKey& operator=(const EndpointKey& other) 
		{
			endpoint_type = other.endpoint_type;
			route = other.route;

			return *this;
		}

		bool operator==(const EndpointKey& other) const
		{
			return (endpoint_type == other.endpoint_type
				&& route == other.route);
		}
	};
}

namespace std {

    template <>
    struct hash<reploid::EndpointKey>
    {
        std::size_t operator()(const reploid::EndpointKey& k) const
        {
			std::size_t seed = 0x0A934AA4;
			boost::hash_combine(seed, k.endpoint_type);
			boost::hash_combine(seed, k.route);
			return seed;
        }
    };

}