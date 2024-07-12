
#include "LogRepository.h"
void LogRepository::addLog(int userId, std::string activity)
{
    std::map<std::string, std::string> data = {
        {"userID", std::to_string(userId)}, 
        {"activityType", activity}};
    database.insert("UserActivityInfo", data);
}
