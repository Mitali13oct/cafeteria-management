#pragma once
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <map>
#include <vector>
#include <stdexcept>

class DatabaseRepository
{
public:
    DatabaseRepository(const std::string &db, const std::string &user, const std::string &password);

    ~DatabaseRepository();

    void insert(const std::string &entityName, const std::map<std::string, std::string> &data);

    void update(const std::string &entityName, const std::map<std::string, std::string> &data, const std::map<std::string, std::string> &filter);

    sql::ResultSet *selectAll(const std::string &entityName, const std::map<std::string, std::string> &filter = {}, const std::map<std::string, std::string> &orderBy = {}, const std::string &condition = "=", const std::string& groupBy="") const;

    sql::ResultSet *selectOne(const std::string &entityName, const std::map<std::string, std::string> &filter);

    void remove(const std::string &entityName, const std::map<std::string, std::string> &filter);
    sql::ResultSet *executeSelectQuery(const std::string &query, const std::vector<std::string> &queryParams) const;


private:
    sql::Connection *connection = nullptr;

    void init(const std::string &db, const std::string &user, const std::string &password);

    void ensureInitialized() const;

    void closeConnection();

    void executeQuery(const std::string &query, const std::map<std::string, std::string> &data, const std::map<std::string, std::string> &filter = {});

};