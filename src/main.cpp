#include <iostream>
#include "CPistacheEndpoint.hpp"
#include "CWelcomeController.hpp"
#include "CCrudTestController.hpp"
#include "CConfig.hpp"

int main(int argc, char* argv[], char* envp[])
{
    /**
     * Testing environment variables
    */
    auto& conf = CConfig::config();
    conf.load_from_envp(envp);

    conf.at("teste", "adsw");

    // API Controllers setup
    std::unique_ptr<CWelcomeController> control(std::make_unique<CWelcomeController>());
    std::unique_ptr<CCrudTestController> crudtest(std::make_unique<CCrudTestController>());

    // Webserver setup
    CPistacheEndpoint endp;

    endp.register_controller(std::move(control));
    endp.register_controller(std::move(crudtest));

    Pistache::Port port(9080);
    Pistache::Address addr(Pistache::Ipv4::any(), port);
    endp.init(addr);
    endp.start();
}
