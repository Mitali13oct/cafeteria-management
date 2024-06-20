#pragma once

#include "Server/inc/FeedbackService/FeedbackService.h"

void FeedbackService::addFeedback(const Feedback &Feedback) { repository.addFeedback(Feedback); }
std::vector<Feedback> FeedbackService::getAllFeedback(int itemid)
{
    std::vector<Feedback> Feedbacks = repository.getAllFeedback(itemid);

    return Feedbacks;
}
double FeedbackService::calculateAverageRating(int itemId) {
    std::vector<Feedback> feedbacks = repository.getAllFeedback(itemId);
    if (feedbacks.empty()) {
        return 0.0;
    }

    double totalRating = 0.0;
    for (const Feedback &feedback : feedbacks) {
        totalRating += feedback.getRating();
    }

    return totalRating / feedbacks.size();
}