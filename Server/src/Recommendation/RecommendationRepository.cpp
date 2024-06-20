#include"Server/inc/RecommendationService/RecommendationRepository.h"

RecommendationRepository::RecommendationRepository()
    : database("RecommendationEngine", "mitalijain", "Mishu@777") {}

RecommendationRepository::~RecommendationRepository() {}

void RecommendationRepository::addRecommendation(const Recommendation &recommendation) {
    std::map<std::string, std::string> data = {
        {"type", recommendation.getType() == MealType::Lunch ? "Lunch" :
                 (recommendation.getType() == MealType::Dinner ? "Dinner" : "Breakfast")},
        {"recommendationDate", recommendation.getRecommendationDate()},
        {"totalRating", std::to_string(recommendation.getTotalRating())},
        {"ItemID",std::to_string(recommendation.getItemid())}
    };
    database.insert("Recommendation", data);
}

void RecommendationRepository::deleteRecommendation(int recommendationId) {
    std::map<std::string, std::string> filter = {
        {"recommendationId", std::to_string(recommendationId)}
    };
    database.remove("Recommendation", filter);
}

std::vector<Recommendation> RecommendationRepository::getAllRecommendations() const {
    sql::ResultSet *res = database.selectAll("Recommendation");
    std::vector<Recommendation> recommendations;

    while (res->next()) {
        int recommendationId = res->getInt("recommendationId");
        std::string typeStr = res->getString("type");
        MealType type;
        if (typeStr == "Lunch") {
            type = MealType::Lunch;
        } else if (typeStr == "Dinner") {
            type = MealType::Dinner;
        } else if (typeStr == "Breakfast") {
            type = MealType::Breakfast;
        }
        std::string recommendationDate = res->getString("recommendationDate");
        int totalRating = res->getInt("totalRating");
        int itemid = res->getInt("ItemId");
        Recommendation recommendation(
            recommendationId,
            type,
            recommendationDate,
            totalRating,
            itemid
        );

        recommendations.push_back(recommendation);
    }
    delete res;
    return recommendations;
}

// Recommendation RecommendationRepository::getRecommendationById(int recommendationId) const {
//     std::map<std::string, std::string> filter = {
//         {"recommendationId", std::to_string(recommendationId)}
//     };
//     sql::ResultSet *res = database.selectAll("Recommendation", filter);
//     Recommendation recommendation(0, MealType::Lunch, "", 0, false, 0);

//     if (res->next()) {
//         int recommendationId = res->getInt("recommendationId");
//         std::string typeStr = res
