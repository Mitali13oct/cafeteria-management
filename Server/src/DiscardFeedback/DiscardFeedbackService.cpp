#include "DiscardFeedbackService.h"
std::string DiscardService::generatePresetQuestions() const
{
    std::string question = "Share detailed Feedback";

    return question;
}
// Add a discard feedback entry
void DiscardService::addQuestion(int itemid)
{
    std::string presetQuestions = generatePresetQuestions();
    discardRepository.addDiscardQuestion(itemid, presetQuestions);
}

// Update a discard feedback entry
void DiscardService::addAnswer(int requestId, const std::string &responseMessage)
{
    discardRepository.addDiscardAnswer(requestId, responseMessage);
}

// Delete a discard feedback entry
void DiscardService::deleteDiscardFeedback(int requestId)
{
    discardRepository.deleteDiscardFeedback(requestId);
}

// Retrieve all discard feedback entries
std::string DiscardService::getDiscardFeedbacks() const
{
    std::vector<DiscardFeedback> feedbacks = discardRepository.getDiscardFeedbacks();
    std::ostringstream oss;

    for (const auto &fb : feedbacks)
    {
        oss << "Request ID: " << fb.getRequestId() << ", Item ID: " << fb.getItemId()
            << ", Request Message: " << fb.getquestion()
            << ", Response Message: " << fb.getanswer() << "\n";
    }

    return oss.str();
}

// Retrieve discarded items as a formatted string
// std::string DiscardService::getDiscardedItems() const
// {
//     std::vector<MenuItem> items = discardRepository.getDiscardedItems();
//     std::ostringstream oss;
//     FeedbackService fservice;

//     for (const auto &item : items)
//     {
//         std::vector<Feedback> feedbacks = fservice.getAllFeedback(item.getId());
//         oss << "Item ID: " << item.getId() << ", Name: " << item.getName() << ", Sentiments: ";

//         for (const auto &feedback : feedbacks)
//         {
//             oss << feedback.getComment() << ", Rating: " << feedback.getRating() << "; ";
//         }

//         oss << "\n";
//     }

//     return oss.str();
// }