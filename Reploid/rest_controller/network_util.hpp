#pragma once
#include "common.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace reploid {

    using HostInetInfo = tcp::resolver::iterator;

    class NetworkUtils {
    	
	    private:
	        static HostInetInfo queryHostInetInfo();
	        static std::string hostIP(unsigned short family);
    		
	    public:
	        // gets the host IP4 string formatted
			static std::string hostIP4();

	        // gets the host IP6 string formatted
			static std::string hostIP6();
    	
			static std::string hostName();
    };

}