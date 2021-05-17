#include "CSql.hpp"
#include "CConfig.hpp"

CSql& CSql::instance()
{
    static CSql sql;
    return sql;
}

unique_conn_t CSql::make_connection_cfg()
{
    auto& conf = CConfig::config();
    sql::mysql::MySQL_Driver* driver = get_sql_drv();

    unique_conn_t con;

    con = unique_conn_t(driver->connect(conf["MYSQL_HOST"], conf["MYSQL_USER"], conf["MYSQL_PASSWORD"]));
    con->setSchema(conf["MYSQL_DATABASE"]);

    return con;
}

sql::mysql::MySQL_Driver* CSql::get_sql_drv()
{
    /* get_driver_instance() is not thread safe */
    std::lock_guard<std::mutex> lck(sqldrvmtx);
    return sql::mysql::get_mysql_driver_instance();
}
