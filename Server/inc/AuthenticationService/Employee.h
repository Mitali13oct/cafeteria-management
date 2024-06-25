#pragma once
#include "User.h"

#include "NotificationService.h"
#include "FeedbackService.h"
#include"MenuService.h"
class Employee : public User
{
    NotificationService nservice;
    MenuService menu;
    FeedbackService fService;

public:
    Employee(int id, const std::string &username, const std::string &password)
        : User(id, username, password, "Employee") {}

    std::string getRole() const override;
    void setNotificationService(NotificationService n) { nservice = n; }
    int chooseMenuItem();
    void provideFeedback(int itemId, std::string comment, double rating);
    void viewNotifications();
    std::string getAllMenuItem();
    void setService(MenuService s) { menu = s; }

};
