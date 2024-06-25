

#include "EmpController.h"


    std::string processOption(Employee* emp, int option, int socket, char* buffer){
        std::string result;
        if (option == 1)
        {
            result = "Choose Menu Item";
        }
        else if (option == 2)
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
            else
            {
                return "Invalid meal type entered.";
            }

            RecommendationRepository recommendationRepository;
            RecommendationService recommendationService(&recommendationRepository, feedbackService, sentimentAnalyzer);
            recommendationService.generateRecommendations(menuRepository);
            sendPrompt(socket, recommendationService.getAllRecommendations(mealType));
        }
        else if (option == 3)
        {
            // NotificationRepository *nrepo = new NotificationRepository();
            // NotificationService nservice(nrepo);

            // std::string type;
            // if (!readFromSocket(socket, buffer, type))
            //     return "Failed to read meal type";
            // NotificationType notificationType;
            // if (type == "Recommendation")
            // {
            //     notificationType = NotificationType::Recommendation;
            // }
            // else if (type == "ItemAdded")
            // {
            //     notificationType = NotificationType::ItemAdded;
            // }
            // else if (type == "AvailabilityChange")
            // {
            //     notificationType = NotificationType::AvailabilityChange;
            // }
            //  nservice.getAllNotification(notificationType);
            getNotification(socket, buffer);
        }
        else
        {
            result = "Invalid Option";
        }
    }
    }
