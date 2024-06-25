#pragma once
#include "Recommendation.h"
#include "DbOperation.h"
#include"Utility.h"
#include <vector>

class RecommendationRepository {
private:
    DatabaseRepository database;

public:
    RecommendationRepository();
    ~RecommendationRepository();

    void addRecommendation(const Recommendation &recommendation);
    void deleteRecommendation(int recommendationId);
    std::vector<Recommendation> getAllRecommendations(std::string) const;
std::map<int, std::string> getItemNames(const std::vector<int> &itemIds) const;
};
