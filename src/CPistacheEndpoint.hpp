/**
 *@file CPistacheEndpoint.hpp
 * @author Fabio Rossini Sluzala ()
 * @brief Pistache webserver helper with controllers
 * @version 0.1
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#ifndef _CPistacheEndpoint_hpp
#define CPistacheEndpoint_hpp

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <atomic>
#include <map>
#include <string>
#include <vector>
#include "CController.hpp"

 /**
  *@brief CPistacheEndpoint webserver manager, the same program can have many of this and each can have many controllers objects attached
  *
  */
class CPistacheEndpoint
{
    /**
     *@brief Attached controllers vector
     * Maybe a deque or other non contiguous container will be a better option?
     */
    std::vector<std::unique_ptr<CController>> controllers;

public:
    /**
     *@brief Initialize server options
     *
     * @param addr The address and port of the server
     * @param thr The number of threads the server is allowed to use
     */
    void init(Pistache::Address addr, size_t thr = 2);

    /**
     *@brief Start pistache server threaded
     *
     */
    void start();

    /**
     *@brief Shutdown with safe the pistache server
     *
     */
    void stop();

    /**
     *@brief Attaches new CController derivated class to the server
     *
     * @param controller the controller
     * @param urlnamespace the base uri of the controller routes
     */
    void register_controller(std::unique_ptr<CController>&& controller, const std::string& urlnamespace = "");

    /**
     * @brief Construct a new CPistacheEndpoint object
     *
     */
    CPistacheEndpoint() noexcept;

private:
    /**
     *@brief Internal setup routes functions
     *
     */
    void setupRoutes();

    /**
     *@brief Route to serve files, disabled actually
     *
     * @param request pistache web request data
     * @param response pistache web response writer
     */
    void staticfile(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    /**
     *@brief Disable de construction of CPistacheEndpoint
     *
     */
    CPistacheEndpoint(const CPistacheEndpoint&) = delete;

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
};

#endif
