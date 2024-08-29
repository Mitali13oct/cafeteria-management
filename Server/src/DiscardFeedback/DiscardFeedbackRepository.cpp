#include "DiscardFeedbackRepository.h"
#include "DbOperation.h"

void DiscardRepository::addDiscardQuestion(int itemid, std::string question)
{
    std::map<std::string, std::string> data = {
        {"itemId", std::to_string( itemid)},
        {"requestMessage", question}};
           database.insert("DetailedFeedbackRequest", data);
}

void DiscardRepository::addDiscardAnswer(int requestId, const std::string answer)
{
    std::map<std::string, std::string> data = {
        {"responseMessage", answer}};
    std::map<std::string, std::string> filter = {
        {"requestId", std::to_string(requestId)}};
    database.update("DetailedFeedbackRequest", data, filter);
}

void DiscardRepository::deleteDiscardFeedback(int requestId)
{
    std::map<std::string, std::string> filter = {
        {"requestId", std::to_string(requestId)}};
    database.remove("DetailedFeedbackRequest", filter);
}

std::vector<DiscardFeedback> DiscardRepository::getDiscardFeedbacks() const
{
    std::vector<DiscardFeedback> feedbacks;
    sql::ResultSet *resultSet = database.selectAll("DetailedFeedbackRequest");
    
    while (resultSet->next())
    {
        feedbacks.emplace_back(
            resultSet->getInt("requestId"),
            resultSet->getInt("itemId"),
            resultSet->getString("requestMessage"),
            resultSet->getString("responseMessage"));
    }
    
    delete resultSet; 
    return feedbacks;
}

