
#pragma once
#include "FeedbackService.h"
#include "SentimentAnalyzer.h"
#include"MenuService.h"
#include <vector>
#include"RecommendationRepository.h"
#include<unordered_map>
#include<chrono>
#include <iomanip>
#include<BreakfastRepository.h>
class RecommendationService {
private:
   FeedbackService& feedbackService;
    SentimentAnalyzer& sentimentAnalyzer;
    RecommendationRepository* recommendationRepository;

public:
    RecommendationService(RecommendationRepository*,FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer);
    ~RecommendationService();

    void generateRecommendations( MenuRepository* );
    std::string getAllRecommendations(MealType mealtype);
};

