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
#include "DbOperation.h"

class UserRepository
{
public:
    UserRepository()
        : dbRepo("RecommendationEngine", "mitalijain", "Mishu@777") {}

    void saveUser(const User &user);

    bool authenticateUser(const std::string &username, const std::string &password);

    std::string getUserRole(const std::string &username);
    User *getUserByUsername(const std::string &username);
    

private:
    DatabaseRepository dbRepo;
};
