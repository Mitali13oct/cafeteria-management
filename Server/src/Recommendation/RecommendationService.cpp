
#include "RecommendationService.h"

RecommendationService::RecommendationService(RecommendationRepository *r, FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer)
    : recommendationRepository(r), feedbackService(feedbackService), sentimentAnalyzer(sentimentAnalyzer) {}
RecommendationService::~RecommendationService() {}

std::string getCurrentDate()
{
    std::time_t now = std::time(0);
    std::tm *localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d");
    return oss.str();
}

void RecommendationService::generateRecommendations(MenuRepository *type)
{
    std::vector<MenuItem> menu = type->getMenuItems();
    std::vector<int> itemIds;

    for (auto item : menu)
    {
        itemIds.push_back(item.getId());
    }
    std::unordered_map<int, std::vector<Feedback>> allFeedbacks;

    for (const auto &itemId : itemIds)
    {
        std::vector<Feedback> feedbacks = feedbackService.getAllFeedback(itemId);
        allFeedbacks[itemId] = feedbacks;
    }

    std::unordered_map<int, std::pair<int, int>> menuIdToRatingAndSentimentCount;
    std::unordered_map<int, std::vector<int>> menuIdToSentimentScores;

    for (const auto &pair : allFeedbacks)
    {
        int itemId = pair.first;
        const std::vector<Feedback> &feedbacks = pair.second;

        for (const Feedback &feedback : feedbacks)
        {
            int sentimentScore = sentimentAnalyzer.analyzeSentiment(feedback.getComment());
            menuIdToRatingAndSentimentCount[itemId].first += feedback.getRating();
            menuIdToRatingAndSentimentCount[itemId].second++;
            menuIdToSentimentScores[itemId].push_back(sentimentScore);
        }
    }

    std::vector<Recommendation> recommendations;

    for (const auto &pair : menuIdToRatingAndSentimentCount)
    {
        int itemId = pair.first;
        int totalRating = pair.second.first;
        int count = pair.second.second;

        int averageRating = count > 0 ? totalRating / count : 0;

        int totalSentimentScore = 0;
        for (int score : menuIdToSentimentScores[itemId])
        {
            totalSentimentScore += score;
        }
        int averageSentimentScore = menuIdToSentimentScores[itemId].size() > 0 ? totalSentimentScore / menuIdToSentimentScores[itemId].size() : 0;

        int recommendationScore = averageRating + averageSentimentScore;

        Recommendation recommendation(
            0,
            type->getMealType(),
            Utility::getCurrentDate(),
            recommendationScore,
            itemId);

        recommendations.push_back(recommendation);
    }

    // Store recommendations in the repository
    for (const Recommendation &recommendation : recommendations)
    {
        recommendationRepository->addRecommendation(recommendation);
    }
}
std::string RecommendationService::getAllRecommendations(MealType mealtype)
{
    std::string mealTypeStr;

    if (mealtype == MealType::Breakfast)
    {
        mealTypeStr = "Breakfast";
    }
    else if (mealtype == MealType::Lunch)
    {
        mealTypeStr = "Lunch";
    }
    else if (mealtype == MealType::Dinner)
    {
        mealTypeStr = "Dinner";
    }
    std::vector<Recommendation> existingRecommendations = recommendationRepository->getAllRecommendations(mealTypeStr);
    std::vector<int> itemIds;
    for (const auto &recommendation : existingRecommendations)
    {
        itemIds.push_back(recommendation.getItemid());
    }

    // Fetch item names for the item IDs
    std::map<int, std::string> itemNames = recommendationRepository->getItemNames(itemIds);
    std::string result;
    for (const auto &recommendation : existingRecommendations)
    {
         std::string itemName = itemNames[recommendation.getItemid()];  // Get the item name for the item ID

        result += "ID: " + std::to_string(recommendation.getRecommendationId()) + ", " +
                  "Rating: " + std::to_string(recommendation.getTotalRating()) + ", " +
                  "Meal Type: " + mealTypeStr + ", " +
                  "Date: " + recommendation.getRecommendationDate() + ", " +
                //   "ItemId: " + std::to_string(recommendation.getItemid()) + ", " +
                  "ItemName: " + itemName + "\n";  // Include item name
    }
    return result;
}
