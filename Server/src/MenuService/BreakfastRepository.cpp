// BreakfastRepository.cpp
#include "Server/inc/MenuService/BreakfastRepository.h"
MealType BreakfastRepository::getMealType(){
    return MealType::Breakfast;
}
void BreakfastRepository::addMenuItem(const MenuItem &item)
{
    std::string mealTypeStr;
    switch (item.getMealType()) {
        case MealType::Breakfast:
            mealTypeStr = "Breakfast";
            break;
        case MealType::Lunch:
            mealTypeStr = "Lunch";
            break;
        case MealType::Dinner:
            mealTypeStr = "Dinner";
            break;
        default:
            mealTypeStr = "Unknown";
            break;
    }
    std::map<std::string, std::string> data = {
        {"Name", item.getName()},
        {"Price", std::to_string(item.getPrice())},
        {"MealType", mealTypeStr},
        {"AvailabilityStatus", item.getAvailability() ? "1" : "0"}};

    database.insert("MenuItem", data);
}

void BreakfastRepository::updateMenuItem(int itemId,std::string columnToUpdate,std::string value)
{
    std::map<std::string, std::string> data = {
        {columnToUpdate, value}
    };
    
    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}
    };
    
    database.update("MenuItem", data, filter);
}

void BreakfastRepository::deleteItem(int itemId)
{
    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};
    database.remove("MenuItem", filter);
}

std::vector<MenuItem> BreakfastRepository::getMenuItems() const
{
    std::map<std::string, std::string> filter = {
        {"MealType", "Breakfast"}};
    sql::ResultSet *res = database.selectAll("MenuItem", filter);
    std::vector<MenuItem> items;

    while (res->next())
    {
        const int itemId = res->getInt("ItemID");
        const std::string name = res->getString("Name");      // Assuming res->getString("Name") returns std::string
        double price = res->getDouble("Price");               // Assuming res->getDouble("Price") returns double
        std::string mealTypeStr = res->getString("MealType"); // Assuming res->getString("MealType") returns std::string
        bool availability = res->getBoolean("AvailabilityStatus");
        MenuItem item(
            itemId,
            name,
            price,
            MealType::Breakfast,
            availability);
        items.push_back(item);
    }
    delete res;
    return items;
}
