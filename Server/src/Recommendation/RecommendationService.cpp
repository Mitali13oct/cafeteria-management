
#include "RecommendationService.h"

RecommendationService::RecommendationService(RecommendationRepository *r, FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer)
    : recommendationRepository(r), feedbackService(feedbackService), sentimentAnalyzer(sentimentAnalyzer), preferenceService() {}
RecommendationService::~RecommendationService() {}

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

        result += "ItemName: " + itemName + ", " +
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

    std::string notification = getRolledOutItemsForToday();

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

std::string RecommendationService::getSortedRecommendationsByPreference(int userId, MenuRepository *menuRepository)
{

    Preference empPreference = preferenceService.loadPreference(userId);

    std::vector<Recommendation> rolledOutRecommendations = recommendationRepository->getRolledOutRecommendations();
    if (rolledOutRecommendations.size() == 0)
    {
        return "Recommendation not rolled out for today";
    }
    std::vector<MenuItem> menuItems = menuRepository->getMenuItems();
    std::unordered_map<int, MenuItem> menuItemMap;
    for (const auto &recommendation : rolledOutRecommendations)
    {
        MenuItem item = menuRepository->getItemById(recommendation.getItemid());
        menuItemMap.emplace(recommendation.getItemid(), item);
    }
    std::sort(rolledOutRecommendations.begin(), rolledOutRecommendations.end(),
              [&menuItemMap, &empPreference](const Recommendation &a, const Recommendation &b)
              {
                  MenuItem itemA = menuItemMap[a.getItemid()];
                  MenuItem itemB = menuItemMap[b.getItemid()];

                  if (empPreference.getDietaryPreference() == "vegetarian")
                  {
                      if (itemA.getDietaryType() != "vegetarian" && itemB.getDietaryType() == "vegetarian")
                          return false;
                      if (itemA.getDietaryType() == "vegetarian" && itemB.getDietaryType() != "vegetarian")
                          return true;
                  }

                  if (empPreference.getSpiceLevel() != itemA.getSpiceType() && empPreference.getSpiceLevel() == itemB.getSpiceType())
                      return false;

                  if (empPreference.getCuisinePreference() != itemA.getCuisineType() && empPreference.getCuisinePreference() == itemB.getCuisineType())
                      return false;

                  if (empPreference.hasSweetTooth() && !itemA.getSweetToothType() && itemB.getSweetToothType())
                      return false;

                  return true;
              });
    std::ostringstream result;
    result << "Sorted Recommendations by your Preference:\n";
    for (const auto &recommendation : rolledOutRecommendations)
    {
        MenuItem item = menuItemMap[recommendation.getItemid()];
        result << " ID: " << recommendation.getRecommendationId() << ", Name: " << item.getName() << "\n";
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
