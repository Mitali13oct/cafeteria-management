#pragma once
#include"DbOperation.h"
class LogRepository
{
private:

    DatabaseRepository database;

public:
    LogRepository() : database("RecommendationEngine", "mitalijain", "Mishu@777")
    {
    }
    ~LogRepository()
    {
    }
    
    void addLog(int,std::string) ;
    


};
