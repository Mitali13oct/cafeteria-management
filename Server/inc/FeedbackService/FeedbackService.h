#pragma once

#include "FeedbackRepository.h"

class FeedbackService
{
private:
    FeedbackRepository &repository;

public:
    FeedbackService(FeedbackRepository &repo) : repository(repo) {}
    ~FeedbackService() {}
double calculateAverageRating(int itemId) ;
    void addFeedback(const Feedback &Feedback);
    std::vector<Feedback> getAllFeedback(int);
};
