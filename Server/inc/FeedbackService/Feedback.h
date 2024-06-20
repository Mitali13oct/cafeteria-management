
#include<string>
class Feedback
{
private:
    int feedbackId;
    double rating;
    std::string comment;
    std::string date;
    int itemId;

public:
    Feedback(int feedbackId,double rating, std::string comment,std::string date,int itemId) : feedbackId(feedbackId),rating(rating),comment(comment),date(date),itemId(itemId){}
    ~Feedback(){}

    int getFeedbackId() const {
        return feedbackId;
    }

    double getRating() const {
        return rating;
    }

    std::string getComment() const {
        return comment;
    }

    std::string getDate() const {
        return date;
    }

    int getItemId() const {
        return itemId;
    }
};
