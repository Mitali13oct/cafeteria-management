#pragma once
#include "User.h"
#include "MenuService.h"
#include "DiscardFeedbackService.h"
class Admin : public User
{
    MenuService menu;
    DiscardService discardService;
public:
    Admin(int id, const std::string &username, const std::string &password)
        : User(id, username, password, "Admin"),discardService() {}

    std::string getRole() const;
    void setService(MenuService& s) { menu = s; }
    void addMenuItem(const MenuItem &item);
    void updateMenuItem(int, std::string, std::string);
    void deleteItem(int itemId);
    std::string getAllMenuItem();
    MenuService getService() { return menu; }
    std::string getDiscardedItems();
    void addQuestion(int);
};
