#pragma once
#include "Recommendation.h"
#include "DbOperation.h"
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
    // Recommendation getRecommendationById(int recommendationId) const;
};
