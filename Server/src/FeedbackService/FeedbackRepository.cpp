
#include "FeedbackRepository.h"

void FeedbackRepository::addFeedback(const Feedback &feedback) {
    std::map<std::string, std::string> data = {
        {"rating", std::to_string(feedback.getRating())},
        {"comment", feedback.getComment()},
        {"itemId", std::to_string(feedback.getItemId())},
        {"id",std::to_string(feedback.getUserId())}
    };
    database.insert("Feedback", data);
}



std::vector<Feedback> FeedbackRepository::getAllFeedback(int itemid) const {
    std::map<std::string, std::string> filter = {
        {"itemId", std::to_string(itemid)}};
    sql::ResultSet *res = database.selectAll("Feedback",filter);
    std::vector<Feedback> feedbacks;

    while (res->next()) {
        int feedbackId = res->getInt("feedbackId");
        double rating = res->getDouble("rating");
        std::string comment = res->getString("comment");
        std::string date = res->getString("feedbackDate");
        int userId = res->getInt("id");

        Feedback feedback(
            feedbackId,
            rating,
            comment,
            date,
            itemid,
            userId
        );

        feedbacks.push_back(feedback);
    }
    delete res;
    return feedbacks;
}
