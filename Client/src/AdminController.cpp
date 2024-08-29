#include "AdminController.h"
#include <iostream>
#include <map>
#include <string>

bool AdminHandler::handleOptions(Client &client)
{
    std::string option;
    std::cout << "Admin Menu:\n" + Utility::showMenu("Admin");
    std::cin >> option;
    if (option == "6")
    {
        client.sendOption(option);
        return true;
    }

    client.sendOption(option);
    int optionInt = std::stoi(option);
    char buffer[BUFFER_SIZE] = {0};

    if (optionInt == 1)
    {
        std::string name, price, available, mealTypeStr, dietaryPreference, spiceType, cuisineType, sweetToothType;
        std::cout << "Item name: ";
        std::cin >> name;
        std::cout << "Price: ";
        std::cin >> price;
        std::cout << "Availability (Yes/No): ";
        std::cin >> available;
        std::cout << "Meal Type (Breakfast/Lunch/Dinner): ";
        std::cin >> mealTypeStr;
        std::cout << "Dietary Preference (vegetarian/non-vegetarian/eggetarian): ";
        std::cin >> dietaryPreference;
        std::cout << "Spice Type (high/medium/low): ";
        std::cin >> spiceType;
        std::cout << "Cuisine Type (north-indian/south-indian/other): ";
        std::cin >> cuisineType;
        std::cout << "Sweet Tooth (Yes/No): ";
        std::cin >> sweetToothType;
        std::map<std::string, std::string> itemDetail = {{"Name", name}, {"Price", price}, {"AvailabilityStatus", available}, {"MealType", mealTypeStr}, {"DietaryType", dietaryPreference}, {"SpiceType", spiceType}, {"CuisineType", cuisineType}, {"SweetToothType", sweetToothType}};
        client.sendMulitpleDetails(itemDetail);
        client.readResponse(buffer);
    }
   else  if (optionInt == 2)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        std::string id, column, value;
        std::cout << "Enter item ID to edit: ";
        std::cin >> id;
        std::cout << "Enter column to edit: ";
        std::cin >> column;
        std::cout << "Enter value to edit: ";
        std::cin >> value;
        std::map<std::string, std::string> updateItemDetails = {{"ItemID", id}, {"ColumnName", column}, {"Value", value}};
        client.sendMulitpleDetails(updateItemDetails);
        client.readResponse(buffer);
    }
   else  if (optionInt == 3)
    {
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

        std::string mealType;
        std::cin >> mealType;

        client.sendOption(mealType);
        client.readResponse(buffer);

        client.readResponse(buffer);
        std::string id;
        std::cin >> id;
        client.sendOption(id);
    }
    else if (optionInt == 4)
    {
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

        std::string mealType;
        std::cin >> mealType;

        client.sendOption(mealType);
        client.readResponse(buffer);
    }
    else if (optionInt == 5)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        if (optionInt == 5)
        {
            int deleteOption;
            std::cout << Utility::discardItem();
            std::cin >> deleteOption;
            client.sendOption(std::to_string(deleteOption));
            if (deleteOption == 1)
            {
                std::cout << "Enter item ID to delete: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
            else if (deleteOption == 2)
            {
                std::cout << "Enter item ID to add Question for: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
        }
    }
    return false;
}
