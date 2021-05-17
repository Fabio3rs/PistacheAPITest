#pragma once
#ifndef _CCrudTestController_hpp
#define _CCrudTestController_hpp

#include "CController.hpp"
#include "CSql.hpp"

class CCrudTestController : public CController
{
    void index_route(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

public:
    void register_routes(const std::string& base, Pistache::Rest::Router& router);

    CCrudTestController();
};

#endif
