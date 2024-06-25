#pragma once

#include "FeedbackRepository.h"

class FeedbackService
{
private:
    FeedbackRepository repository;

public:
    FeedbackService() : repository() {}
    // FeedbackService() = default;
    ~FeedbackService() {}
    double calculateAverageRating(int itemId);
    void addFeedback(const Feedback &Feedback);
    std::vector<Feedback> getAllFeedback(int);
};
