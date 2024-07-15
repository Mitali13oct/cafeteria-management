#include "ChefHandler.h"

bool ChefHandler::handleOptions(Client &client)
{
    std::string option;
    std::cout << "Chef Menu:\n" + Utility::showMenu("Chef");
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
        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);
    }
    else if (optionInt == 2)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        if (optionInt == 2)
        {
            std::string id;
            std::cin >> id;
            client.sendOption(id);
            client.readResponse(buffer);
        }
    }
    else if (optionInt == 3)
    {
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        std::string itemID;
        std::cout << "Enter Item IDs you want to prepare (comma-separated): ";
        std::cin.ignore();
        std::getline(std::cin, itemID);
        client.sendOption(itemID);
        client.readResponse(buffer);
    }
    else if (optionInt == 4)
    {
        std::cout << "Enter the meal type to view Discarded items (Breakfast/Lunch/Dinner): ";
        std::string mealType;
        std::cin >> mealType;
        client.sendOption(mealType);
        client.readResponse(buffer);

        int discardOption;
        std::cout << Utility::discardItem();
        std::cin >> discardOption;
        client.sendOption(std::to_string(discardOption));
        if (discardOption == 1)
        {
            std::cout << "Enter item ID to delete: ";
            int id;
            std::cin >> id;
            client.sendOption(std::to_string(id));
            client.readResponse(buffer);
        }
        else if (discardOption == 2)
        {
            std::cout << "Enter item ID to add Question for: ";
            int id;
            std::cin >> id;
            client.sendOption(std::to_string(id));
            client.readResponse(buffer);
        }
    }
    return false;
}
