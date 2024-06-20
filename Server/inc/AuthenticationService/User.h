#pragma once
#include <string>

class User {
protected:
    int id;
    std::string username;
    std::string password;
    std::string role;
public:
    User(int id, const std::string& username, const std::string& password,std::string role)
        : id(id), username(username), password(password), role(role){}

    virtual std::string getRole() const = 0;
     std::string getPassword() const ;
    int getId() const ;
    std::string getUsername() const;
    
};
