
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

    std::map<int, std::string> itemNames = recommendationRepository->getItemNames(itemIds);
    std::string result;
    for (const auto &recommendation : existingRecommendations)
    {
        std::string itemName = itemNames[recommendation.getItemid()];

        result += "ItemName: " + itemName  + ", " +
                  "Rating: " + std::to_string(recommendation.getTotalRating()) + ", " +
                  "Meal Type: " + mealTypeStr + ", " +
                  "Date: " + recommendation.getRecommendationDate() + 
                  "\n";
    }
    return result;
}
void RecommendationService::rollOutRecommendations(int numberOfItems, std::string mealTypeStr)
{
    std::vector<Recommendation> recommendations = recommendationRepository->getAllRecommendations(mealTypeStr); 

    int count = 0;
    for (const auto &recommendation : recommendations)
    {
        if (count >= numberOfItems)
        {
            break;
        }
        recommendationRepository->updateRecommendationRolledOutStatus(recommendation.getRecommendationId(), true);
        ++count;
    }
    NotificationRepository notificationrepo;
    NotificationService notificationService(&notificationrepo);
    
    std::string notification =  getRolledOutItemsForToday();
   
    Notification notificationObj(NotificationType::Recommendation, notification);

    notificationService.addNotification(notificationObj);
}
std::string RecommendationService::getRolledOutItemsForToday()
{

    std::vector<Recommendation> rolledOutRecommendations = recommendationRepository->getRolledOutRecommendations();
    std::vector<int> itemIds;
    for (const auto &recommendation : rolledOutRecommendations)
    {
        itemIds.push_back(recommendation.getItemid());
    }
    std::map<int, std::string> itemNames = recommendationRepository->getItemNames(itemIds);

    std::ostringstream result;
    result << "Items Rolled Out for Today\n";

    for (const auto &recommendation : rolledOutRecommendations)
    {
        int itemId = recommendation.getItemid();
        std::string itemName = itemNames[itemId];

        result << "ID: " + std::to_string(recommendation.getRecommendationId()) + ", " +
                      "Rating: " + std::to_string(recommendation.getTotalRating()) + ", " +
                      "ItemName: " + itemName + "\n";
    }

    return result.str();
}
void RecommendationService ::voteForItem(int id) { recommendationRepository->voteItem(id); }
void RecommendationService ::prepareItem(int id) { recommendationRepository->markAsPrepared(id); }

std::string RecommendationService::getVotedItems(const std::string &mealTypeStr)
{
    std::vector<Recommendation> recommendations = recommendationRepository->getVotedItems(mealTypeStr);
    std::vector<int> recommendationIds;

    for (const auto &recommendation : recommendations)
    {
        recommendationIds.push_back(recommendation.getRecommendationId());
    }

    std::map<int, int> voteCounts = recommendationRepository->getVoteCounts(recommendationIds);
    std::vector<int> itemIds;

    for (const auto &recommendation : recommendations)
    {
        itemIds.push_back(recommendation.getItemid());
    }

    std::map<int, std::string> itemNames = recommendationRepository->getItemNames(itemIds);
    std::ostringstream result;

    for (const auto &rec : recommendations)
    {
        int itemId = rec.getItemid();
        int recommendationId = rec.getRecommendationId();
        std::string itemName = itemNames[itemId];
        int voteCount = voteCounts[recommendationId];

        result << "ID: " + std::to_string(recommendationId) + ", Name: " + itemName + ", Votes: " + std::to_string(voteCount) + "\n";
    }

    return result.str();
}
