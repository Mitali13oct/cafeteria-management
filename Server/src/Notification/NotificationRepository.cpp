#include "Server/inc/NotificationService/NotificationRepository.h"


    void NotificationRepository::addNotification(const Notification &notification)
    {
        std::map<std::string, std::string> data = {
            {"notificationType", notification.getTypeAsString()},
            {"message", notification.getMessage()},
            {"notificationDate", notification.getDateTime()}

        };
        database.insert("Notification", data);
    }

    void NotificationRepository::deleteNotification(int notificationId)
    {
        std::map<std::string, std::string> filter = {
            {"ItemID", std::to_string(notificationId)}};
        database.remove("Notification", filter);
    }
    std::vector<Notification> NotificationRepository::getAllNotification() const
    {

        sql::ResultSet *res = database.selectAll("Notification");
        std::vector<Notification> notifications;

        while (res->next())
        {
            int notificationId = res->getInt("notificationId");
            const std::string message = res->getString("message");    // Assuming res->getString("Name") returns std::string
            std::string typeStr = res->getString("notificationType"); // Assuming res->getString("MealType") returns std::string
            std::string dateTime = res->getString("notificationDate");
            NotificationType type;
            if (typeStr == "Recommendation")
            {
                type = NotificationType::Recommendation;
            }
            else if (typeStr == "MenuUpdate")
            {
                type = NotificationType::MenuUpdate;
            }
            else if (typeStr == "AvailabilityChange")
            {
                type = NotificationType::AvailabilityChange;
            }
            Notification notification(
                notificationId,
                type,
                message,
                dateTime);
            notifications.push_back(notification);
        }
        delete res;
        return notifications;
    }
