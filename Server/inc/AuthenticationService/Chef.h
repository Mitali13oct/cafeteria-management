#pragma once
#include "User.h"
#include "MenuRepository.h"
#include "RecommendationService.h"
#include "WordLoader.h"
#include "DiscardFeedbackService.h"
class Chef : public User
{
    RecommendationService recommendationService;
    MenuService menu;
    DiscardService discardService;

public:
    Chef(int id, const std::string &username, const std::string &password)
        : User(id, username, password, "Chef"),
          recommendationService(new RecommendationRepository(),
                                *(new FeedbackService()),
                                *(new SentimentAnalyzer(
                                    WordLoader().loadWords("/home/L&C/Cafeteria-management/PositiveWords.txt"),
                                    WordLoader().loadWords("/home/L&C/Cafeteria-management/NegativeWords.txt")))),
          discardService()
    {
    }

    std::string getRole() const;
    void setService(MenuService m) { menu = m; }

    std::string getRecommendation(MenuRepository *);
    void rollOutMenu(int, std::string);
    void chooseItemToPrepare(std::vector<int> itemIds);
    std::string getDiscardedItems();
    std::string getVotedItems(std::string mealTypeStr);
    void deleteItem(int itemId);
    void addQuestion(int);
};
