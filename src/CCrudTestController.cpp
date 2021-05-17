#include "CCrudTestController.hpp"
#include "CConfig.hpp"

void CCrudTestController::index_route(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response)
{
    auto& conf = CConfig::config();

    unique_conn_t con = CSql::instance().make_connection_cfg();

    con->setSchema(conf["MYSQL_DATABASE"]);

    unique_statement_t stmt(con->createStatement());

    unique_resultset_t res(stmt->executeQuery("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES;"));

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
}
