
#include"Server/inc/NotificationService/NotificationService.h"


    void NotificationService::addNotification(const Notification& notification){repository.addNotification(notification);}
    void NotificationService::deleteNotification(int notificationId){repository.deleteNotification(notificationId);}
    std::string NotificationService::getAllNotification(){std::vector<Notification> notifications = repository.getAllNotification();
    std::string result;

    for (const auto& notification : notifications) {
        result += "Notification ID: " + std::to_string(notification.getNotificationId()) + "\n"
                + "Type: " + notification.getTypeAsString() + "\n"
                + "Message: " + notification.getMessage() + "\n"
                + "Date: " + notification.getDateTime() + "\n\n";
    }

    return result;}
