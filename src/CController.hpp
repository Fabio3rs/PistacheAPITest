/**
 *@file CController.hpp
 * @author Fabio Rossini Sluzala ()
 * @brief Controller base class for use with CPistacheEndpoint
 * @version 0.1
 *
 */
#pragma once
#ifndef _CController_hpp
#define CController_hpp

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

 /**
  *@brief CControler base class
  *
 */
class CController
{

public:
    /**
     *@brief Function CPistacheEndpoint calls to the controller register the routes
     *
     */
    virtual void register_routes(const std::string&, Pistache::Rest::Router&);

    CController() = default;
    CController(const CController&) = default;
    CController(CController&&) = default;

    virtual ~CController() {}
};

#endif
