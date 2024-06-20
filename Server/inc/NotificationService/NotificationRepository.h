#pragma once
#include "Notification.h"
#include "Server/inc/DbOperation/DbOperation.h"
class NotificationRepository
{
private:
    DatabaseRepository database;

public:
    NotificationRepository() : database("RecommendationEngine", "mitalijain", "Mishu@777") {}
    ~NotificationRepository()
    {
    }

    void addNotification(const Notification &notification);
    void deleteNotification(int notificationId);
    std::vector<Notification> getAllNotification() const;
};