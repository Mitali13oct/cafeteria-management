#pragma once
#include "User.h"

#include "NotificationService.h"
#include "FeedbackService.h"
#include "MenuService.h"
#include "DiscardFeedbackService.h"
#include "RecommendationService.h"
#include "WordLoader.h"
class Employee : public User
{
    NotificationService nservice;
    MenuService menu;
    FeedbackService fService;
    DiscardService discardService;
    RecommendationService recommendationService;

public:
    Employee(int id, const std::string &username, const std::string &password)
        : User(id, username, password, "Employee"),recommendationService(new RecommendationRepository(),
                                *(new FeedbackService()),
                                *(new SentimentAnalyzer(
                                    WordLoader().loadWords("/home/L&C/Cafeteria-management/PositiveWords.txt"),
                                    WordLoader().loadWords("/home/L&C/Cafeteria-management/NegativeWords.txt")))), discardService() {}

    std::string getRole() const override;
    void voteOnItem(std::vector<int>);
    void provideFeedback(int itemId, std::string comment, double rating);
    std::string viewNotifications(NotificationType);
    std::string getAllMenuItem();
    void setService(MenuService s) { menu = s; }
    std::string getRolledOutItems();
};
