#pragma once
#include "Feedback.h"
#include "Server/inc/DbOperation/DbOperation.h"
#include <vector>

class FeedbackRepository {
private:
    DatabaseRepository database;

public:
    FeedbackRepository() : database("RecommendationEngine", "mitalijain", "Mishu@777") {}
    ~FeedbackRepository() {}

    void addFeedback(const Feedback &feedback);
    std::vector<Feedback> getAllFeedback(int itemid) const;
};



