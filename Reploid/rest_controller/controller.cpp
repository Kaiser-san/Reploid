#include "controller.hpp"
#include "network_util.hpp"

namespace reploid {

    Controller::Controller()
    {
    }

    Controller::~Controller()
    {
    }

    void Controller::setEndpoint(const utility::string_t& value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == _XPLATSTR("host_auto_ip4")) {
            endpointBuilder.set_host(NetworkUtils::hostIP4());
        }
        else if (endpointURI.host() == _XPLATSTR("host_auto_ip6")) {
            endpointBuilder.set_host(NetworkUtils::hostIP6());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri());
    }

    utility::string_t Controller::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> Controller::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> Controller::shutdown() {
        return _listener.close();
    }

    void Controller::handleGet(http_request message)
    {
        auto response = json::value::object();
        response[_XPLATSTR("version")] = json::value::string(_XPLATSTR("0.1.1"));
        response[_XPLATSTR("status")] = json::value::string(_XPLATSTR("ready!"));
        message.reply(status_codes::OK, response);
    }

    std::vector<utility::string_t> Controller::requestPath(const http_request& message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);
    }
}
