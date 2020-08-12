#pragma once

#include "rest_controller/controller.hpp"

class SimpleService : public reploid::Controller
{
public:
	explicit SimpleService(const utility::string_t& route);

private:
	void initEndpoints() override;
};