
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
class RecommendationService
{
private:
    FeedbackService &feedbackService;
    SentimentAnalyzer &sentimentAnalyzer;
    RecommendationRepository *recommendationRepository;

public:
    RecommendationService(RecommendationRepository *, FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer);
    ~RecommendationService();
    void rollOutRecommendations(int numberOfItems, std::string mealTypeStr);
    void generateRecommendations(MenuRepository *);
    std::string getAllRecommendations(MealType mealtype);
    std::string getRolledOutItemsForToday();
    void voteForItem(int id);
     std::string getVotedItems(const std::string &mealTypeStr);
    void markItemAsPrepared(int id);
};
