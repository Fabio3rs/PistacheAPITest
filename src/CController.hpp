#pragma once
#ifndef _CController_hpp
#define _CController_hpp

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

class CController
{

public:
    virtual inline void register_routes(const std::string& base, Pistache::Rest::Router& router) {}

    CController() = default;
    CController(CController&) = default;
    CController(CController&&) = default;

    ~CController() = default;
};

#endif
