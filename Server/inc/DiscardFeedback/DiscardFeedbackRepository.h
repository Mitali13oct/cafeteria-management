#pragma once
#include <vector>
#include <string>
#include "DiscardFeedback.h"
#include "DbOperation.h"

class DiscardRepository
{
private:
    DatabaseRepository database;

public:
    DiscardRepository()
        : database("RecommendationEngine",  "mitalijain", "Mishu@777")
    {
    }

    ~DiscardRepository()
    {
    }

    // Adds a discard feedback entry to the database
    void addDiscardQuestion(int , const std::string );
    void addDiscardAnswer(int itemId, const std::string answer);
    // Updates a discard feedback entry in the database

    // Deletes a discard feedback entry from the database
    void deleteDiscardFeedback(int requestId);

    // Retrieves all discard feedback entries from the database
    std::vector<DiscardFeedback> getDiscardFeedbacks() const;

    // Retrieves discarded items (based on your requirement)
    // std::vector<MenuItem> getDiscardedItems() const;
};
