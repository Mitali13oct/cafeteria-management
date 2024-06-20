#pragma once
#include "Server/inc/MenuService/Mealtype.h"
#include <string>
class Recommendation {
private:
    int recommendationId;
    MealType type;
    std::string recommendationDate;
    int totalRating;
    int itemid;
public:
    Recommendation(int recommendationId, MealType type, const std::string& recommendationDate,
                   int totalRating ,int);

    int getRecommendationId() const;
    MealType getType() const;
    std::string getRecommendationDate() const;
    int getTotalRating() const;
    int getItemid() const ;

};
