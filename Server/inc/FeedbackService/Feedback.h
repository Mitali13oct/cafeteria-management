#pragma once
#include <string>
class Feedback
{
private:
    int feedbackId;
    double rating;
    std::string comment;
    std::string date;
    int itemId;
    int userId;

public:
    Feedback(int feedbackId, double rating, std::string comment, std::string date, int itemId, int userId) : feedbackId(feedbackId), rating(rating), comment(comment), date(date), itemId(itemId), userId(userId) {}
    Feedback( double rating, std::string comment,  int itemId, int userId) : feedbackId(feedbackId), rating(rating), comment(comment),  itemId(itemId), userId(userId) {}

    ~Feedback() {}

    int getFeedbackId() const;

    double getRating() const;

    std::string getComment() const;

    std::string getDate() const;

    int getItemId() const;

    int getUserId() const;
};
