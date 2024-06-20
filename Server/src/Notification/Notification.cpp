    #include"Server/inc/NotificationService/Notification.h"
    
    int Notification::getNotificationId() const {
        return id;
    }

    NotificationType Notification::getType() const {
        return type;
    }

    std::string Notification::getTypeAsString() const {
        switch (type) {
            case NotificationType::Recommendation: return "Recommendation";
            case NotificationType::MenuUpdate: return "MenuUpdate";
            case NotificationType::AvailabilityChange: return "AvailabilityChange";
            default: return "Unknown";
        }
    }

    const std::string& Notification::getMessage() const {
        return message;
    }

    std::string Notification::getDateTime() const {
        return dateTime;
    }
 

