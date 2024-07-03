#include "DiscardFeedbackService.h"
std::string DiscardService::generatePresetQuestions() const
{
    std::string question = "Share detailed Feedback";

    return question;
}

void DiscardService::addQuestion(int itemid)
{
    std::string presetQuestions = generatePresetQuestions();
    discardRepository.addDiscardQuestion(itemid, presetQuestions);
}


void DiscardService::addAnswer(int requestId, const std::string &responseMessage)
{
    discardRepository.addDiscardAnswer(requestId, responseMessage);
}

void DiscardService::deleteDiscardFeedback(int requestId)
{
    discardRepository.deleteDiscardFeedback(requestId);
}

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



