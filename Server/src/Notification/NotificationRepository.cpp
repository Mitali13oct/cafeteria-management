#include "NotificationRepository.h"

void NotificationRepository::addNotification(const Notification &notification)
{
    std::map<std::string, std::string> data = {
        {"notificationType", notification.getTypeAsString()},
        {"message", notification.getMessage()}
    };

    database.insert("Notification", data);
}

void NotificationRepository::deleteNotification(int notificationId)
{
    std::map<std::string, std::string> filter = {
        {"notificationId", std::to_string(notificationId)}};
    database.remove("Notification", filter);
}
std::vector<Notification> NotificationRepository::getAllNotification(std::string type) const
{
    std::map<std::string, std::string> filter = {
        {"notificationType",type },{"notificationDate",Utility::getCurrentDate()}};
    sql::ResultSet *res = database.selectAll("Notification", filter);
    std::vector<Notification> notifications;

    while (res->next())
    {
        int notificationId = res->getInt("notificationId");
        const std::string message = res->getString("message");    
        std::string typeStr = res->getString("notificationType"); 
        std::string dateTime = res->getString("notificationDate");
        NotificationType type;
        if (typeStr == "Recommendation")
        {
            type = NotificationType::Recommendation;
        }
        else if (typeStr == "ItemAdded")
        {
            type = NotificationType::ItemAdded;
        }
        else if (typeStr == "ItemUpdated")
        {
            type = NotificationType::ItemUpdated;
        }
         else if (typeStr == "ItemDeleted")
        {
            type = NotificationType::ItemDeleted;
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
