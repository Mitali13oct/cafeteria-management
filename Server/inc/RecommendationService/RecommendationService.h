
#pragma once
#include "FeedbackService.h"
#include "SentimentAnalyzer.h"
#include"MenuRepository.h"
#include <vector>
#include"RecommendationRepository.h"
#include<unordered_map>
#include<chrono>
#include <iomanip>
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

