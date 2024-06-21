
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

    int getFeedbackId() const ;

    double getRating() const ;

    std::string getComment() const ;

    std::string getDate() const ;

    int getItemId() const;
};
