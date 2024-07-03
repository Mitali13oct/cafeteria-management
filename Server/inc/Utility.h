#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "MenuItem.h"
#include "sstream"
class Utility
{

public:
    
   static MealType mealTypeFromString(const std::string &typeStr)
{
    if (typeStr == "Breakfast") {
        return MealType::Breakfast;
    } else if (typeStr == "Lunch") {
        return MealType::Lunch;
    } else if (typeStr == "Dinner") {
        return MealType::Dinner;
    } else {
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
   

};
