#pragma once
#include "User.h"
#include "MenuItem.h"
#include "MenuService.h"

class Admin : public User {
    MenuService menu;
public:
    Admin(int id, const std::string& username, const std::string& password)
        : User(id, username, password) {}

    std::string getRole() const ;

    void addMenuItem(const MenuItem& item);
    void updateMenuItem(const MenuItem& item);
    void deleteItem(int itemId);
};
