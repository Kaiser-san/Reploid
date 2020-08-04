#include "network_util.hpp"

using namespace reploid;


HostInetInfo NetworkUtils::queryHostInetInfo() {
    io_service ios;
    tcp::resolver resolver(ios);
    tcp::resolver::query query(host_name(), "");
    return resolver.resolve(query);
}

std::string NetworkUtils::hostIP(unsigned short family) {
    auto hostInetInfo = queryHostInetInfo();
    tcp::resolver::iterator end;
    while (hostInetInfo != end) {
        tcp::endpoint ep = *hostInetInfo++;
        sockaddr sa = *ep.data();
        if (sa.sa_family == family) {
            return ep.address().to_string();
        }
    }
    return nullptr;
}

std::string NetworkUtils::hostIP4()
{
    return hostIP(AF_INET);
}

std::string NetworkUtils::hostIP6()
{
    return hostIP(AF_INET6);
}

std::string NetworkUtils::hostName()
{
    return host_name();
}
