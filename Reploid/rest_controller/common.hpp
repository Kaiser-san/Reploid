#pragma once


#define _TURN_OFF_PLATFORM_STRING
#include <cpprest/asyncrt_utils.h>
#include <cpprest/http_msg.h>


#define BOOST_SPIRIT_THREADSAFE // enable thread safety to json read on property tree!

#include <boost/format.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>


#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

#include "endpoint_type.hpp"
#include "endpoint_key.hpp"