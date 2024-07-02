#pragma once
#include "Recommendation.h"
#include "DbOperation.h"
#include "Utility.h"
#include <vector>

class RecommendationRepository
{
private:
    DatabaseRepository database;

public:
    RecommendationRepository();
    ~RecommendationRepository();

    void addRecommendation(const Recommendation &recommendation);
    void deleteRecommendation(int recommendationId);
    std::vector<Recommendation> getAllRecommendations(std::string) const;
    std::map<int, std::string> getItemNames(const std::vector<int> &itemIds) const;
    void updateRecommendationRolledOutStatus(int recommendationId, bool isRolledOut);
    std::vector<Recommendation> getRolledOutRecommendations() const;
    void voteItem(int id);
   std::vector<Recommendation>getVotedItems(const std::string &mealTypeStr) const;
   std::map<int, int> getVoteCounts(const std::vector<int>& recommendationIds) ;
   void markAsPrepared(int);

};
