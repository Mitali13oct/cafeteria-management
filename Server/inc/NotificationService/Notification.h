#pragma once
#include"NotificationType.h"
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
class Notification
{
private:
    int id;
    NotificationType type;
    std::string message;
    std::string dateTime;

public:
Notification( NotificationType type, const std::string& msg, std::string time)
        : id(-1), type(type), message(msg), dateTime(time) {}
     Notification(int id, NotificationType type, const std::string& msg, std::string time)
        : id(id), type(type), message(msg), dateTime(time) {}
    ~Notification(){}
    int getNotificationId() const;

    NotificationType getType() const ;

    std::string getTypeAsString() const;

    const std::string& getMessage() const ;

    std::string getDateTime() const ;

};
