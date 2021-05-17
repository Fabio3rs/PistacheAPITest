#pragma once
#ifndef _CSql_hpp
#define CSql_hpp

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <memory>
#include <mutex>

typedef std::unique_ptr<sql::Connection> unique_conn_t;
typedef std::unique_ptr<sql::Statement> unique_statement_t;
typedef std::unique_ptr<sql::ResultSet> unique_resultset_t;

class CSql
{
    std::mutex sqldrvmtx;

    CSql() = default;
    CSql(const CSql&) = delete;
public:
    // Singleton
    static CSql& instance();

    unique_conn_t                       make_connection_cfg();
    sql::mysql::MySQL_Driver* get_sql_drv();

    static inline sql::mysql::MySQL_Connection* mysql_cast(sql::Connection* conn)
    {
        sql::mysql::MySQL_Connection* mconn = dynamic_cast<sql::mysql::MySQL_Connection*>(conn);

        if (mconn == nullptr)
        {
            throw std::bad_cast();
        }

        return mconn;
    }

    static inline std::string escape(sql::mysql::MySQL_Connection* conn, const std::string& val, bool null_if_empty = false)
    {
        if (!conn) throw std::invalid_argument("Resource is null");

        if (null_if_empty && val.empty())
        {
            return "NULL";
        }

        return conn->escapeString(val);
    }

    /**
     *@brief Performs escape of special characters in string to use in sql queries
     *
     * @param conn the mysql connection pointer
     * @param val string value to escape
     * @param null_if_empty return NULL if the string is empty
     * @return std::string
     */
    static inline std::string esc_add_q(sql::mysql::MySQL_Connection* conn, const std::string& val, bool null_if_empty = false)
    {
        if (!conn) throw std::invalid_argument("Resource is null");

        if (null_if_empty && val.empty())
        {
            return "NULL";
        }

        std::string result;
        result.reserve(val.size() + 2);

        result = "'";
        result += conn->escapeString(val);
        result += "'";

        return result;
    }

    static inline std::string escape_add_qwith_unhex(sql::mysql::MySQL_Connection* conn, const std::string& val, bool null_if_empty = false)
    {
        if (!conn) throw std::invalid_argument("Resource is null");

        if (null_if_empty && val.empty())
        {
            return "NULL";
        }

        std::string result;
        result.reserve(val.size() + 9);

        result = "UNHEX('";
        result += conn->escapeString(val);
        result += "')";

        return result;
    }
};

#endif

