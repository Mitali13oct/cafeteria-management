
#pragma once
#include "FeedbackService.h"
#include "SentimentAnalyzer.h"
#include "MenuService.h"
#include <vector>
#include "RecommendationRepository.h"
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <BreakfastRepository.h>
#include "PreferenceService.h"
#include "ServerUtility.h"
class RecommendationService
{
private:
    FeedbackService &feedbackService;
    SentimentAnalyzer &sentimentAnalyzer;
    RecommendationRepository *recommendationRepository;
    PreferenceService preferenceService;
public:
    RecommendationService(RecommendationRepository *, FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer);
    ~RecommendationService();

    void rollOutRecommendations(int numberOfItems, std::string mealTypeStr);
    void generateRecommendations(MenuRepository *);
    std::string getAllRecommendations(MealType mealtype);
    std::string getVotedItems(const std::string &mealTypeStr);
    void prepareItem(int id);

    std::string getRolledOutItemsForToday();
    void voteForItem(int id);
    std::string getSortedRecommendationsByPreference(int userId,MenuRepository*);
};
