#pragma once
#include "Server/inc/AuthenticationService/User.h"
#include "Server/inc/MenuService/MenuItem.h"
#include "Server/inc/MenuService/MenuService.h"
#include"Server/inc/MenuService/MenuRepository.h"
class Admin : public User {
    MenuService menu;
public:
    Admin(int id, const std::string& username, const std::string& password)
        : User(id, username, password,"Admin") {}

    std::string getRole() const ;
    void setService(MenuService s){menu=s;}
    void addMenuItem(const MenuItem& item);
    void updateMenuItem(int ,std::string,std::string);
    void deleteItem(int itemId);
    std::string getAllMenuItem();
    MenuService getService(){return menu;}
};
