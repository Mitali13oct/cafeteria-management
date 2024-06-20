#pragma once
#include "User.h"
#include "Server/inc/MenuService/MenuItem.h"

class Employee : public User {
public:
    Employee(int id, const std::string& username, const std::string& password)
        : User(id, username, password,"Employee") {}

    std::string getRole() const override ;

    int chooseMenuItem();
    void provideFeedback(const MenuItem& item);
    void viewNotifications();
};
