#include "CPistacheEndpoint.hpp"

CPistacheEndpoint::CPistacheEndpoint() noexcept
{

}

void CPistacheEndpoint::init(Pistache::Address addr, size_t thr)
{
    httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);

    auto opts = Pistache::Http::Endpoint::options()
        .threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setupRoutes();
}

void CPistacheEndpoint::start()
{
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void CPistacheEndpoint::setupRoutes()
{
    using namespace Pistache;
    using namespace Pistache::Rest;

    Routes::NotFound(router, Routes::bind(&CPistacheEndpoint::staticfile, this));
}

void CPistacheEndpoint::register_controller(std::unique_ptr<CController>&& controller, const std::string& urlnamespace)
{
    if (!controller)
    {
        return;
    }

    controllers.push_back(std::move(controller));
    controllers.back()->register_routes(urlnamespace, router);
}

void CPistacheEndpoint::staticfile(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
{
    if (request.resource().compare(0, sizeof("/static/") - 1, "/static/") == 0 && request.method() == Pistache::Http::Method::Get)
    {
        Pistache::Http::serveFile(response, "files" + request.resource());
    }
    else
    {
        response.send(Pistache::Http::Code::Not_Found, "Isso non ecziste!");
    }
}
