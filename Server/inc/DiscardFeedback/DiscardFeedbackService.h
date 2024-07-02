#pragma once
#include <vector>
#include<sstream>
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

    // Adds a discard feedback entry
    void addQuestion(int);

    // Updates a discard feedback entry
    void addAnswer(int requestId, const std::string &responseMessage);

    // Deletes a discard feedback entry
    void deleteDiscardFeedback(int requestId);

    // Retrieves all discard feedback entries
    std::string getDiscardFeedbacks() const;

    // Retrieves discarded items
    std::string generatePresetQuestions() const;

};
