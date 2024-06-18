#pragma once
#include "User.h"
#include "MenuRepository.h"

class Chef : public User
{
public:
    Chef(int id, const std::string &username, const std::string &password)
        : User(id, username, password,"Chef") {}

    std::string getRole() const;

    void provideMenuToEmp(MenuRepository *menuRepo);
    void generateMonthlyReport();
    void sendNotification();
};
