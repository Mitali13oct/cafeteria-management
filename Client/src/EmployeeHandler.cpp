#include "EmployeeHandler.h"

bool EmployeeHandler::handleOptions(Client &client)
{
    std::string option;
    std::cout << "Employee Menu:\n" + Utility::showMenu("Employee");
    std::cin >> option;
    if (option == "5")
    {
        client.sendOption(option);
        return true;
    }

    client.sendOption(option);
    int optionInt = std::stoi(option);
    char buffer[BUFFER_SIZE] = {0};

    if (optionInt == 1)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);
        std::string serverResponse(buffer);
        if (serverResponse == "Recommendation not rolled out for today")
        {
            return false;
        }
        std::string itemID;
        std::cout << "Enter Item IDs you want to vote for (comma-separated): ";
        std::cin.ignore();
        std::getline(std::cin, itemID);
        client.sendOption(itemID);
        client.readResponse(buffer);
    }
    else if (optionInt == 2)
    {
        client.readResponse(buffer);
        std::string typeOption;
        std::cin >> typeOption;
        client.sendOption(typeOption);
        client.readResponse(buffer);
    }
    else if (optionInt == 3)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        std::string itemID, comment, rating;
        std::cout << "Enter item ID to give Feedback and rating on: ";
        std::cin >> itemID;
        std::cout << "Enter comment: ";
        std::cin.ignore();
        std::getline(std::cin, comment);
        std::cout << "Enter Rating: ";
        std::cin >> rating;
        std::map<std::string, std::string> feedback = {{"ItemId", itemID}, {"comment", comment}, {"rating", rating}};
        client.sendMulitpleDetails(feedback);
        client.readResponse(buffer);
    }
    else if (optionInt == 4)
    {
        std::string diet, spice, cuisine, sweetTooth;
        std::cout << "Dietary Preference (vegetarian/non-vegetarian/eggetarian): ";
        std::cin >> diet;
        std::cout << "Spice Level (high/medium/low): ";
        std::cin >> spice;
        std::cout << "Cuisine Preference (north-indian/south-indian/other): ";
        std::cin >> cuisine;
        std::cout << "Sweet Tooth (Yes/No): ";
        std::cin >> sweetTooth;
        std::map<std::string, std::string> preference = {{"Dietary Preference", diet}, {"Spice Level", spice}, {"Cuisine Preference", cuisine}, {"Sweet Tooth", sweetTooth}};
        client.sendMulitpleDetails(preference);
        client.readResponse(buffer);
    }
    return false;
}
