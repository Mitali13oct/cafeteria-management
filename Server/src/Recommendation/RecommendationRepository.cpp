#include "RecommendationRepository.h"

RecommendationRepository::RecommendationRepository()
    : database("RecommendationEngine", "mitalijain", "Mishu@777") {}

RecommendationRepository::~RecommendationRepository() {}

void RecommendationRepository::addRecommendation(const Recommendation &recommendation)
{
    std::map<std::string, std::string> data = {
        {"type", Utility::mealTypeToString(recommendation.getType())},
        {"recommendationDate", recommendation.getRecommendationDate()},
        {"totalRating", std::to_string(recommendation.getTotalRating())},
        {"ItemID", std::to_string(recommendation.getItemid())}};
    database.insert("Recommendation", data);
}
void RecommendationRepository::voteItem(int id)
{
    std::map<std::string, std::string> filter = {
        {"recommendationId", std::to_string(id)}};

    sql::ResultSet *res = database.selectOne("Vote", filter);
    if (res->next())
    {
        int voteCount = res->getInt("voteCount");
        voteCount++;

        std::map<std::string, std::string> updateValues = {
            {"voteCount", std::to_string(voteCount)}};

        database.update("Vote", updateValues, filter);
    }
    else
    {
        std::map<std::string, std::string> insertValues = {
            {"recommendationId", std::to_string(id)},
            {"voteCount", "1"}};

        database.insert("Vote", insertValues);
    }

    delete res;
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

        std::string recommendationDate = res->getString("recommendationDate");
        int totalRating = res->getInt("totalRating");
        int itemid = res->getInt("ItemId");
        MealType type = Utility ::mealTypeFromString(res->getString("type"));
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

std::map<int, int> RecommendationRepository::getVoteCounts(const std::vector<int> &recommendationIds)
{
    std::map<int, int> voteCounts;
    if (recommendationIds.empty())
    {
        return voteCounts;
    }

    std::ostringstream idList;
    for (size_t i = 0; i < recommendationIds.size(); ++i)
    {
        idList << recommendationIds[i];
        if (i < recommendationIds.size() - 1)
        {
            idList << ", ";
        }
    }

    std::map<std::string, std::string> filter = {
        {"recommendationId", "(" + idList.str() + ")"}};

    sql::ResultSet *res = database.selectAll("Vote", filter, {}, "IN");

    while (res->next())
    {
        int recommendationId = res->getInt("recommendationId");
        int voteCount = res->getInt("voteCount");
        voteCounts[recommendationId] = voteCount;
    }
    delete res;
    return voteCounts;
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
std::vector<Recommendation> RecommendationRepository::getRolledOutRecommendations() const
{
    std::map<std::string, std::string> filter = {
        {"recommendationDate", Utility::getCurrentDate()},
        {"isRolledOut", "1"}};

    sql::ResultSet *res = database.selectAll("Recommendation", filter);
    std::vector<Recommendation> recommendations;
    while (res->next())
    {
        int recommendationId = res->getInt("recommendationId");
        std::string recommendationDate = res->getString("recommendationDate");
        MealType type = Utility ::mealTypeFromString(res->getString("type"));
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
    return recommendations;
}
void RecommendationRepository::updateRecommendationRolledOutStatus(int recommendationId, bool isRolledOut)
{
    std::map<std::string, std::string> data = {
        {"isRolledOut", isRolledOut ? "1" : "0"}};
    std::map<std::string, std::string> filter = {
        {"recommendationId", std::to_string(recommendationId)}};
    database.update("Recommendation", data, filter);
}
std::vector<Recommendation> RecommendationRepository::getVotedItems(const std::string &mealTypeStr) const
{
    std::map<std::string, std::string> filter = {
        {"type", mealTypeStr}, {"DATE(voteDate)", Utility::getCurrentDate()}};
    std::map<std::string, std::string> orderBy = {
        {"voteCount", "desc"}};

    sql::ResultSet *res = database.selectAll("Recommendation r JOIN Vote v ON r.recommendationId = v.recommendationId", filter, orderBy);
    std::vector<Recommendation> recommendations;
    while (res->next())
    {
        int recommendationId = res->getInt("recommendationId");
        std::string recommendationDate = res->getString("recommendationDate");
        MealType type = Utility::mealTypeFromString(res->getString("type"));
        int totalRating = res->getInt("totalRating");
        int itemId = res->getInt("ItemId");
        Recommendation recommendation(recommendationId, type, recommendationDate, totalRating, itemId);
        recommendations.push_back(recommendation);
    }
    delete res;
    return recommendations;
}
void RecommendationRepository::markAsPrepared(int id)
{
    std::map<std::string, std::string> data = {
        {"isPrepared", "1"}};
    std::map<std::string, std::string> filter = {
        {"recommendationId", std::to_string(id)}};
    database.update("Recommendation", data, filter);
}
