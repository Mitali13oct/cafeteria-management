#include <string>

class DiscardFeedback {
private:
    int requestId;
    int itemId;
    std::string question;
    std::string answer;

public:
    // Constructors
    DiscardFeedback();
    DiscardFeedback(int itemId, const std::string &question);
    DiscardFeedback(int requestId, int itemId, const std::string &question, const std::string &answer);

    // Getters and setters
    int getRequestId() const;
    void setRequestId(int requestId);

    int getItemId() const;
    void setItemId(int itemId);

    const std::string & getquestion() const;
    void setquestion(const std::string &question);

    const std::string & getanswer() const;
    void setanswer(const std::string &answer);

    // Destructor
    ~DiscardFeedback();
};

