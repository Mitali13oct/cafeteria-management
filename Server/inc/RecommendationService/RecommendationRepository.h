#pragma once
#include "Recommendation.h"
#include "Server/inc/DbOperation/DbOperation.h"
#include <vector>

class RecommendationRepository {
private:
    DatabaseRepository database;

public:
    RecommendationRepository();
    ~RecommendationRepository();

    void addRecommendation(const Recommendation &recommendation);
    void deleteRecommendation(int recommendationId);
    std::vector<Recommendation> getAllRecommendations() const;
    // Recommendation getRecommendationById(int recommendationId) const;
};
