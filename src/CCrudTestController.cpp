#include "CCrudTestController.hpp"
#include "CConfig.hpp"

void CCrudTestController::index_route(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
{
    std::unique_ptr<sql::Statement> stmt(con->createStatement());

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES;"));

    std::string result;
    result.reserve(128);

    while (res->next()) {
        result += res->getString("TABLE_NAME");
        result += "\n";
    }

    response.send(Pistache::Http::Code::Ok, result);
}

void CCrudTestController::register_routes(const std::string& base, Pistache::Rest::Router& router)
{
    Pistache::Rest::Routes::Get(router, base + "/crud", Pistache::Rest::Routes::bind(&CCrudTestController::index_route, this));
}

CCrudTestController::CCrudTestController() : CController()
{
    auto& conf = CConfig::config();

    /**
     * TODO: Encapsulate this on CSql.hpp
    */
    sql::Driver* driver = get_driver_instance();
    con = std::unique_ptr<sql::Connection>(driver->connect(conf["MYSQL_HOST"], conf["MYSQL_USER"], conf["MYSQL_PASSWORD"]));

    con->setSchema(conf["MYSQL_DATABASE"]);
}
