#pragma once

#include"NotificationRepository.h"

class NotificationService {
private:
    NotificationRepository* repository;
    public:
    NotificationService(NotificationRepository* repo):repository(repo){}
    NotificationService()= default;
    ~NotificationService(){}

    void addNotification(const Notification& notification);
    void deleteNotification(int notificationId);
    std::string getAllNotification(NotificationType);
    std::string convertTypeToString(NotificationType type);
};