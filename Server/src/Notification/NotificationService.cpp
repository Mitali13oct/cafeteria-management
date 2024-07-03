
#include "NotificationService.h"

void NotificationService::addNotification(const Notification &notification) { repository->addNotification(notification); }
void NotificationService::deleteNotification(int notificationId) { repository->deleteNotification(notificationId); }
std::string NotificationService::getAllNotification(NotificationType type)
{
    std::string notificationTypeStr;
    if (type == NotificationType::Recommendation)
    {
        notificationTypeStr = "Recommendation";
    }
    else if (type == NotificationType::ItemAdded)
    {
        notificationTypeStr = "ItemAdded";
    }
    else if (type == NotificationType::ItemUpdated)
    {
        notificationTypeStr = "ItemUpdated";
    }
    else if (type == NotificationType::ItemDeleted)
    {
        notificationTypeStr = "ItemDeleted";
    }
    std::vector<Notification> notifications = repository->getAllNotification(notificationTypeStr);
    std::string result;

    for (const auto &notification : notifications)
    {
        result += "Notification ID: " + std::to_string(notification.getNotificationId()) + "\n" + "Type: " + notification.getTypeAsString() + "\n" + "Message: " + notification.getMessage() + "\n" + "Date: " + notification.getDateTime() + "\n\n";
    }

    return result;
}
std::string NotificationService::convertTypeToString(NotificationType type)
{
    switch (type)
    {
    case NotificationType::Recommendation:
        return "Recommendation";
    case NotificationType::ItemAdded:
        return "ItemAdded";
    case NotificationType::ItemUpdated:
        return "ItemUpdated";
    case NotificationType::ItemDeleted:
        return "ItemDeleted";
    default:
        return "Unknown";
    }
}
