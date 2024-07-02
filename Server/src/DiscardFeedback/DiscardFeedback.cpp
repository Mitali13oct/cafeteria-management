#include "DiscardFeedback.h"



// Default constructor
DiscardFeedback::DiscardFeedback()
    : requestId(0), itemId(0) {}

// Constructor with itemId and question
DiscardFeedback::DiscardFeedback(int itemId, const std::string &question)
    : itemId(itemId), question(question) {}

// Constructor with all fields
DiscardFeedback::DiscardFeedback(int requestId, int itemId, const std::string &question, const std::string &answer)
    : requestId(requestId), itemId(itemId), question(question), answer(answer) {}

// Getter for requestId
int DiscardFeedback::getRequestId() const {
    return requestId;
}

// Setter for requestId
void DiscardFeedback::setRequestId(int requestId) {
    this->requestId = requestId;
}

// Getter for itemId
int DiscardFeedback::getItemId() const {
    return itemId;
}

// Setter for itemId
void DiscardFeedback::setItemId(int itemId) {
    this->itemId = itemId;
}

// Getter for question
const std::string & DiscardFeedback::getquestion() const {
    return question;
}

// Setter for question
void DiscardFeedback::setquestion(const std::string &question) {
    this->question = question;
}

// Getter for answer
const std::string & DiscardFeedback::getanswer() const {
    return answer;
}

// Setter for answer
void DiscardFeedback::setanswer(const std::string &answer) {
    this->answer = answer;
}

// Destructor
DiscardFeedback::~DiscardFeedback() {}

