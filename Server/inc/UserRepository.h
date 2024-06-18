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
#include"DbOperation.h"

// class UserRepository {
// private:
//     sql::Driver* driver;
//     sql::Connection* con;

// public:
//     UserRepository();
//     ~UserRepository();

//     void saveUser(const User& user);
//     bool authenticateUser(const std::string& username, const std::string& password);
//     User* getUserByUsername(const std::string& username);
//     void closeConnection();
// };
// #include"../inc/UserRepository.h"
// UserRepository::UserRepository() {
//         try {
//         driver = get_driver_instance();
//         con = driver->connect("tcp://127.0.0.1:3306", "mitalijain", "Mishu@777");
//         con->setSchema("RecommendationEngine");
//     } catch (sql::SQLException &e) {
//         std::cerr << "SQL error in UserRepository constructor: " << e.what() << std::endl;
//         throw;
//     }
// }

// // Destructor
// UserRepository::~UserRepository() {
//     closeConnection();
// }

// // Save User
// void UserRepository::saveUser(const User& user) {
//     sql::PreparedStatement* pstmt;
//     pstmt = con->prepareStatement("INSERT INTO Users(username, password, role) VALUES (?, ?, ?)");
//     pstmt->setString(1, user.getUsername());
//     pstmt->setString(2, user.getPassword());
//     pstmt->setString(3, user.getRole());
//     pstmt->executeUpdate();
//     delete pstmt;
// }

// // Authenticate User
// bool UserRepository::authenticateUser(const std::string& username, const std::string& password) {
//     sql::PreparedStatement* pstmt;
//     sql::ResultSet* res;
//     pstmt = con->prepareStatement("SELECT * FROM Users WHERE username = ? AND password = ?");
//     pstmt->setString(1, username);
//     pstmt->setString(2, password);
//     res = pstmt->executeQuery();

//     bool authenticated = res->next(); // If a result is returned, the user is authenticated

//     delete res;
//     delete pstmt;
//     return authenticated;
// }

// // Get User by Username
// User* UserRepository::getUserByUsername(const std::string& username) {
//     sql::PreparedStatement* pstmt;
//     sql::ResultSet* res;
//     pstmt = con->prepareStatement("SELECT * FROM Users WHERE username = ?");
//     pstmt->setString(1, username);
//     res = pstmt->executeQuery();

// if (res->next()) {
//         int id = res->getInt("id");
//         std::string user_username = res->getString("username");
//         std::string password = res->getString("password");
//         std::string role = res->getString("role");

//         User* user = nullptr;
//         if (role == "Admin") {
//             user = new Admin(id, user_username, password);
//         } else if (role == "Chef") {
//             user = new Chef(id, user_username, password);
//         } else if (role == "Employee") {
//             user = new Employee(id, user_username, password);
//         } else {
//             delete res;
//             delete pstmt;
//             throw std::runtime_error("Unknown role");
//         }

//         delete res;
//         delete pstmt;
//         return user;
//     } else {
//         delete res;
//         delete pstmt;
//         throw std::runtime_error("User not found");
//     }
// }

// // Close Connection
// void UserRepository::closeConnection() {
//     if (con) {
//         con->close();
//         delete con;
//         con = nullptr;
//     }
// }

#include "../inc/UserRepository.h"

class UserRepository {
public:
    UserRepository()
        : dbRepo("RecommendationEngine", "mitalijain", "Mishu@777") {}

    void saveUser(const User& user) ;

    bool authenticateUser(const std::string& username, const std::string& password) ;

    std::string getUserRole(const std::string& username);
User* getUserByUsername(const std::string& username) ;
private:
    DatabaseRepository dbRepo;
};

