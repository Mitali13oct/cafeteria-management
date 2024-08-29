#pragma once
#include <vector>
#include <sstream>
#include "DiscardFeedbackRepository.h"

class DiscardService
{
private:
    DiscardRepository discardRepository;

public:
    DiscardService()
        : discardRepository()
    {
    }

    void addQuestion(int);

    void addAnswer(int requestId, const std::string &responseMessage);

    void deleteDiscardFeedback(int requestId);

    std::string getDiscardFeedbacks() const;

    std::string generatePresetQuestions() const;
};
