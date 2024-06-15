#pragma once
#include <string>

class User {
protected:
    int id;
    std::string username;
    std::string password;

public:
    User(int id, const std::string& username, const std::string& password)
        : id(id), username(username), password(password) {}

    virtual std::string getRole() const = 0;
     std::string getPassword() const ;
    int getId() const ;
    std::string getUsername() const;
};
