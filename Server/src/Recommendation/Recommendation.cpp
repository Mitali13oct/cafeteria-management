#include"Server/inc/RecommendationService/Recommendation.h"

Recommendation::Recommendation(int recommendationId, MealType type, const std::string& recommendationDate,
                               int totalRating,int itemid)
    : recommendationId(recommendationId), type(type), recommendationDate(recommendationDate),
      totalRating(totalRating),itemid(itemid) {}

int Recommendation::getRecommendationId() const {
    return recommendationId;
}

MealType Recommendation::getType() const {
    return type;
}

std::string Recommendation::getRecommendationDate() const {
    return recommendationDate;
}

int Recommendation::getTotalRating() const {
    return totalRating;
}
int Recommendation::getItemid() const {
    return itemid;
}


