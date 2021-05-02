#include "CWelcomeController.hpp"

void CWelcomeController::index_route(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
{
    response.send(Pistache::Http::Code::Ok, "Welcome!");
}

void CWelcomeController::register_routes(const std::string& base, Pistache::Rest::Router& router)
{
    Pistache::Rest::Routes::Get(router, base + "/", Pistache::Rest::Routes::bind(&CWelcomeController::index_route, this));
}

