#pragma once
#include "User.h"
#include "MenuItem.h"
#include"NotificationService.h"
class Employee : public User {
    NotificationService nservice;
public:
    Employee(int id, const std::string& username, const std::string& password)
        : User(id, username, password,"Employee") {}

    std::string getRole() const override ;
    void setNotificationService(NotificationService n){nservice = n;}
    int chooseMenuItem();
    void provideFeedback(const MenuItem& item);
    void viewNotifications();
};
