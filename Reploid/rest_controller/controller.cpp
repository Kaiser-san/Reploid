#include "controller.hpp"

#include <utility>
#include "network_util.hpp"

namespace reploid {

    Controller::Controller(utility::string_t route)
	    : route_(std::move(route))
    {
        uri endpointURI(route_);
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

        listener_ = std::make_unique<http_listener>(endpointBuilder.to_uri());
        endpoints_ = std::make_unique<std::unordered_map<EndpointKey, std::unique_ptr<Endpoint>>>();
    }

    Controller::~Controller()
    {
        listener_.release();
        endpoints_.release();
    }
	
    utility::string_t Controller::route() const {
        return route_;
    }

    pplx::task<void> Controller::accept() {
        initRestHandlers();
        return listener_->open();
    }

    pplx::task<void> Controller::shutdown() {
        return listener_->close();
    }

    void Controller::addEndpoint(const Endpoint& endpoint)
    {
        endpoints_->insert(std::make_pair(endpoint.getKey(), std::make_unique<Endpoint>(endpoint)));
    }

	void Controller::addEndpoints(const std::vector<Endpoint>& endpoints)
    {
        for (const Endpoint& endpoint : endpoints)
            this->addEndpoint(endpoint);
    }

    void Controller::initRestHandlers()
    {
        listener_->support(methods::GET, std::bind(&Controller::handleGet, this, std::placeholders::_1));
    }

    void Controller::handleGet(http_request message)
    {
        auto response = json::value::object();
        response[_XPLATSTR("version")] = json::value::string(_XPLATSTR("0.1.1"));
        response[_XPLATSTR("status")] = json::value::string(_XPLATSTR("ready!"));
        response[_XPLATSTR("path")] = json::value::string(message.relative_uri().path());
        message.reply(status_codes::OK, response);
    }
}
