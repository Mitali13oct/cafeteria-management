#include "RecommendationRepository.h"

RecommendationRepository::RecommendationRepository()
    : database("RecommendationEngine", "mitalijain", "Mishu@777") {}

RecommendationRepository::~RecommendationRepository() {}

void RecommendationRepository::addRecommendation(const Recommendation &recommendation)
{
    std::map<std::string, std::string> data = {
        {"type", recommendation.getType() == MealType::Lunch ? "Lunch" : (recommendation.getType() == MealType::Dinner ? "Dinner" : "Breakfast")},
        {"recommendationDate", recommendation.getRecommendationDate()},
        {"totalRating", std::to_string(recommendation.getTotalRating())},
        {"ItemID", std::to_string(recommendation.getItemid())}};
    database.insert("Recommendation", data);
}

void RecommendationRepository::deleteRecommendation(int recommendationId)
{
    std::map<std::string, std::string> filter = {
        {"recommendationId", std::to_string(recommendationId)}};
    database.remove("Recommendation", filter);
}

std::vector<Recommendation> RecommendationRepository::getAllRecommendations(std::string mealType) const
{
    std::map<std::string, std::string> filter = {
        {"type", mealType}, {"recommendationDate", Utility::getCurrentDate()}};
    std::map<std::string, std::string> order = {
        {"totalRating", "ASC"}};
    sql::ResultSet *res = database.selectAll("Recommendation", filter, order);
    std::vector<Recommendation> recommendations;
    while (res->next())
    {
        int recommendationId = res->getInt("recommendationId");

        MealType type;
        if (mealType == "Lunch")
        {
            type = MealType::Lunch;
        }
        else if (mealType == "Dinner")
        {
            type = MealType::Dinner;
        }
        else if (mealType == "Breakfast")
        {
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
            itemid);

        recommendations.push_back(recommendation);
    }
    delete res;
    return recommendations;
}
std::map<int, std::string> RecommendationRepository::getItemNames(const std::vector<int> &itemIds) const
{
    std::map<int, std::string> itemNames;
    if (itemIds.empty())
    {
        return itemNames;
    }

    std::ostringstream oss;
    for (size_t i = 0; i < itemIds.size(); ++i)
    {
        oss << itemIds[i];
        if (i != itemIds.size() - 1)
        {
            oss << ",";
        }
    }
    std::string itemIdsStr = oss.str();
    std::map<std::string, std::string> filter;
    filter["ItemID"] = "(" + itemIdsStr + ")";
    sql::ResultSet *res = database.selectAll("MenuItem", filter, {}, "IN", "");
    while (res->next())
    {
        int itemId = res->getInt("ItemID");
        std::string itemName = res->getString("Name");
        itemNames[itemId] = itemName;
    }
    delete res;
    return itemNames;
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
