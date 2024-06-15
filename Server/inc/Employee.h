#pragma once
#include "User.h"
#include "MenuItem.h"

class Employee : public User {
public:
    Employee(int id, const std::string& username, const std::string& password)
        : User(id, username, password) {}

    std::string getRole() const override ;

    int chooseMenuItem();
    void provideFeedback(const MenuItem& item);
    void viewNotifications();
};
