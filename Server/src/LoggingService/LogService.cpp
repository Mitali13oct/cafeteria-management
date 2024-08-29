#include "LogService.h"
    void LogService::addLogInfo(int userId ,std::string activity){
        activityRepo.addLog(userId,activity);
    }
   

