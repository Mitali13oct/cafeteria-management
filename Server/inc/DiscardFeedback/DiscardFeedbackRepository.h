#pragma once
#include <vector>
#include <string>
#include "DiscardFeedback.h"
#include "DbOperation.h"

class DiscardRepository
{
private:
    DatabaseRepository database;

public:
    DiscardRepository()
        : database("RecommendationEngine",  "mitalijain", "Mishu@777")
    {
    }

    ~DiscardRepository()
    {
    }

    
    void addDiscardQuestion(int , const std::string );
    void addDiscardAnswer(int itemId, const std::string answer);
  
    void deleteDiscardFeedback(int requestId);

  
    std::vector<DiscardFeedback> getDiscardFeedbacks() const;
};
