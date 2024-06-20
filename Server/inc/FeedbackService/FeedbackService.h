#pragma once

#include "/home/L&C/Cafeteria-management/Server/inc/FeedbackService/FeedbackRepository.h"

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