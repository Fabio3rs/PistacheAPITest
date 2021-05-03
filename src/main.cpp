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

    int config_port = 9000;

    {
        std::string PORT = conf.at("PORT", "9000");
        try
        {
            config_port = std::stoi(PORT, nullptr, 0);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    // API Controllers setup
    std::unique_ptr<CWelcomeController> control(std::make_unique<CWelcomeController>());
    std::unique_ptr<CCrudTestController> crudtest(std::make_unique<CCrudTestController>());

    // Webserver setup
    CPistacheEndpoint endp;

    endp.register_controller(std::move(control));
    endp.register_controller(std::move(crudtest));

    Pistache::Port port(config_port);
    Pistache::Address addr(Pistache::Ipv4::any(), port);
    endp.init(addr);
    endp.start();
}
