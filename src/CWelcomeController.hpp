#pragma once
#ifndef _CWelcomeController_hpp
#define _CWelcomeController_hpp

#include "CController.hpp"

class CWelcomeController : public CController
{
    void index_route(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

public:
    void register_routes(const std::string& base, Pistache::Rest::Router& router);

    CWelcomeController() = default;
};

#endif
