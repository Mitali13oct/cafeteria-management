
#pragma once
#include "Server/inc/FeedbackService/FeedbackService.h"
#include "SentimentAnalyzer.h"
#include"Server/inc/MenuService/MenuRepository.h"
#include <vector>
#include"RecommendationRepository.h"
#include<unordered_map>
#include<chrono>
#include <iomanip>
class RecommendationService {
private:
   FeedbackService& feedbackService;
    SentimentAnalyzer& sentimentAnalyzer;
    RecommendationRepository recommendationRepository;

public:
    RecommendationService(FeedbackService &feedbackService, SentimentAnalyzer &sentimentAnalyzer);
    ~RecommendationService();

    void generateRecommendations( MenuRepository* );
};

