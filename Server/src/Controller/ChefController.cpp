

#include "ChefController.h"
    std::string processOption(Chef* chef, int option, int socket, char* buffer){
       std::string result;
        if (option == 1)
        {
            std::string mealTypeStr;
            sendPrompt(socket, "Enter the meal type to view items (Breakfast/Lunch/Dinner): ");
            if (!readFromSocket(socket, buffer, mealTypeStr))
            {
                return "Failed to read meal type";
            }
            FeedbackRepository frepo;
            FeedbackService feedbackService(frepo);

            WordLoader wload;

            std::unordered_set<std::string> positive = wload.loadWords("/home/L&C/Cafeteria-management/PositiveWords.txt");
            std::unordered_set<std::string> negative = wload.loadWords("/home/L&C/Cafeteria-management/NegativeWords.txt");
            SentimentAnalyzer sentimentAnalyzer(positive, negative);

            // result = "View Menu Items";
            RecommendationRepository recommendationRepository;
            RecommendationService recommendationService(&recommendationRepository, feedbackService, sentimentAnalyzer);
            MenuRepository *menuRepository;
            MealType mealType;
            
            if (mealTypeStr == "Breakfast")
            {
                mealType = MealType::Breakfast;
                menuRepository = (new BreakfastRepository());
            }
            else if (mealTypeStr == "Lunch")
            {
                mealType = MealType::Lunch;
            }
            else if (mealTypeStr == "Dinner")
            {
                mealType = MealType::Dinner;
            }

            sendPrompt(socket,recommendationService.getAllRecommendations(mealType));
        }
        else if (option == 2)
        {
            result = "Generate Monthly Report";
        }
        else if (option == 3)
        {
            result = "Choose Item to prepare";

        }
    }
