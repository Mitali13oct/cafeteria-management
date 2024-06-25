#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "MenuItem.h"
#include "sstream"
class Utility
{

public:
    static std::string showMenu(std::string role)
    {
        std::vector<std::string> options;
        if (role== "Admin")
        {
            options = showAdminMenu();
        }
        else if (role== "Chef")
        {
            options = showChefMenu();
        }
        else if (role == "Employee")
        {
            options = showEmployeeMenu();
        }
        else
        {
            std::cerr << "Unknown role: " << role<< std::endl;
        }
        std::ostringstream oss;
        for (const auto &option : options)
        {
            oss << option << "\n";
        }
        return oss.str();
    }
   static MealType mealTypeFromString(const std::string &typeStr)
{
    if (typeStr == "Breakfast") {
        return MealType::Breakfast;
    } else if (typeStr == "Lunch") {
        return MealType::Lunch;
    } else if (typeStr == "Dinner") {
        return MealType::Dinner;
    } else {
        // Throw an exception or handle invalid input as needed
        throw std::invalid_argument("Invalid meal type string");
    }
}

static std::string  mealTypeToString(MealType type)
{
    switch (type) {
        case MealType::Breakfast:
            return "Breakfast";
        case MealType::Lunch:
            return "Lunch";
        case MealType::Dinner:
            return "Dinner";
        default:
            // Throw an exception or handle unexpected enum value
            throw std::invalid_argument("Invalid meal type");
    }
}
    static std::string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    snprintf(date, sizeof(date), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return std::string(date);
}
    static std::string menuItemString(){
        return "Enter Item Details \n ";
    }
private:
    static std::vector<std::string> showAdminMenu()
    {
        return {"1. Add Menu Item\n2. Update Menu Item\n3. Delete Menu Item\n4. View All Menu Items"};
        // Additional admin options here
    }

    static std::vector<std::string> showChefMenu()
    {
        return {"1. View Menu Items\n2. Generate Monthly Report\n3. Send Notification\n"};

        // Additional chef options here
    }

    static std::vector<std::string> showEmployeeMenu()
    {
        return {"1. Choose Menu Item\n2. Provide Feedback\n3. View Notifications\n"};

        // Additional employee options here
    }
};
