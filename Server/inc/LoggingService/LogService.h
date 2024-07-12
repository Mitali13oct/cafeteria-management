#pragma once
#include "LogRepository.h"
class LogService
{
    LogRepository activityRepo;
public:
    LogService() : activityRepo() {}
    ~LogService() = default;
    void addLogInfo(int ,std::string);
   
};
