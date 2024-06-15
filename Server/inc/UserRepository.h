#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "User.h"
#include "Admin.h"
#include "Chef.h"
#include "Employee.h"


class UserRepository {
private:
    sql::Driver* driver;
    sql::Connection* con;

public:
    UserRepository();
    ~UserRepository();

    void saveUser(const User& user);
    bool authenticateUser(const std::string& username, const std::string& password);
    User* getUserByUsername(const std::string& username);
    void closeConnection();
};

