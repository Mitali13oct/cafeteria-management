#include "DiscardFeedbackRepository.h"
#include "DbOperation.h"

// Add a discard feedback entry to the database
void DiscardRepository::addDiscardQuestion(int itemid, std::string question)
{
    std::map<std::string, std::string> data = {
        {"itemId", std::to_string( itemid)},
        {"requestMessage", question}};
           database.insert("DetailedFeedbackRequest", data);
}

// Update a discard feedback entry in the database
void DiscardRepository::addDiscardAnswer(int requestId, const std::string answer)
{
    std::map<std::string, std::string> data = {
        {"responseMessage", answer}};
    std::map<std::string, std::string> filter = {
        {"requestId", std::to_string(requestId)}};
    database.update("DetailedFeedbackRequest", data, filter);
}

// Delete a discard feedback entry from the database
void DiscardRepository::deleteDiscardFeedback(int requestId)
{
    std::map<std::string, std::string> filter = {
        {"requestId", std::to_string(requestId)}};
    database.remove("DetailedFeedbackRequest", filter);
}

// Retrieve all discard feedback entries from the database
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
    
    delete resultSet; // Remember to delete the ResultSet to avoid memory leaks
    return feedbacks;
}

// Retrieve discarded items (based on your requirement)
// std::vector<MenuItem> DiscardRepository::getDiscardedItems() const
// {
//     std::vector<MenuItem> items;
//     std::map<std::string, std::string> filter = {
//         {"isDiscarded", "1"}};
//     sql::ResultSet *resultSet = database.selectAll("MenuItem", filter);

//     while (resultSet->next())
//     {
//         items.emplace_back(
//             resultSet->getInt("ItemID"),
//             resultSet->getString("Name"),
//             resultSet->getInt("Price"),
//             resultSet->getInt("AvailabilityStatus"),
//             resultSet->getString("MealType"));
//     }

//     delete resultSet; // Remember to delete the ResultSet to avoid memory leaks
//     return items;
// }
