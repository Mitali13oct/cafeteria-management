#include "DiscardFeedback.h"



DiscardFeedback::DiscardFeedback()
    : requestId(0), itemId(0) {}

DiscardFeedback::DiscardFeedback(int itemId, const std::string &question)
    : itemId(itemId), question(question) {}

DiscardFeedback::DiscardFeedback(int requestId, int itemId, const std::string &question, const std::string &answer)
    : requestId(requestId), itemId(itemId), question(question), answer(answer) {}

int DiscardFeedback::getRequestId() const {
    return requestId;
}

void DiscardFeedback::setRequestId(int requestId) {
    this->requestId = requestId;
}

int DiscardFeedback::getItemId() const {
    return itemId;
}

void DiscardFeedback::setItemId(int itemId) {
    this->itemId = itemId;
}

const std::string & DiscardFeedback::getquestion() const {
    return question;
}

void DiscardFeedback::setquestion(const std::string &question) {
    this->question = question;
}

const std::string & DiscardFeedback::getanswer() const {
    return answer;
}

void DiscardFeedback::setanswer(const std::string &answer) {
    this->answer = answer;
}

DiscardFeedback::~DiscardFeedback() {}

