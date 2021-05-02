#pragma once
#ifndef _CPistacheEndpoint_hpp
#define _CPistacheEndpoint_hpp

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <atomic>
#include <map>
#include <string>
#include <vector>
#include "CController.hpp"

class CPistacheEndpoint
{
    std::vector<std::unique_ptr<CController>> controllers;

public:
    void init(Pistache::Address addr, size_t thr = 2);
    void start();
    void register_controller(std::unique_ptr<CController>&& controller, const std::string& urlnamespace = "");

    CPistacheEndpoint() noexcept;

private:
    void setupRoutes();
    void staticfile(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    CPistacheEndpoint(CPistacheEndpoint&) = delete;

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
};

#endif
