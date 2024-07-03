
#include "LunchRepository.h"
MealType LunchRepository::getMealType()
{
    return MealType::Lunch;
}
void LunchRepository::addMenuItem(const MenuItem &item)
{

    std::map<std::string, std::string> data = {
        {"Name", item.getName()},
        {"Price", std::to_string(item.getPrice())},
        {"MealType", "Lunch"},
        {"AvailabilityStatus", item.getAvailability() ? "1" : "0"},
        {"dietaryType", item.getDietaryType()},
        {"spiceType", item.getSpiceType()},
        {"cuisineType", item.getCuisineType()},
        {"sweetToothType", item.getSweetToothType() ? "1" : "0"}};
    database.insert("MenuItem", data);
}

void LunchRepository::updateMenuItem(int itemId, std::string columnToUpdate, std::string value)
{
    std::map<std::string, std::string> data = {
        {columnToUpdate, value}};

    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};

    database.update("MenuItem", data, filter);
}

void LunchRepository::deleteItem(int itemId)
{
    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};
    database.remove("MenuItem", filter);
}
MenuItem LunchRepository::getItemById(int id)
{

    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(id)}};

    try
    {
        sql::ResultSet *res = database.selectOne("MenuItem", filter);

        if (res->next())
        {
            const std::string name = res->getString("Name");
            double price = res->getDouble("Price");
            std::string mealTypeStr = res->getString("MealType");
            bool availability = res->getBoolean("AvailabilityStatus");
            std::string dietaryType = res->getString("dietaryType");
            std::string spiceType = res->getString("spiceType");
            std::string cuisineType = res->getString("cuisineType");
            bool sweetToothType = res->getBoolean("sweetToothType");

            delete res;

            MenuItem item(id, name, price, MealType::Lunch, availability, dietaryType, spiceType, cuisineType, sweetToothType);
            return item;
        }
        else
        {
            std::cerr << "No item found with ID: " << id << std::endl;
            delete res;
        }
    }
    catch (const sql::SQLException &e)
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    throw std::runtime_error("Failed to retrieve MenuItem from database");
}

std::vector<MenuItem> LunchRepository::getMenuItems() const
{

    std::map<std::string, std::string> filter = {
        {"MealType", "Lunch"}};
    sql::ResultSet *res = database.selectAll("MenuItem", filter);
    std::vector<MenuItem> items;

    while (res->next())
    {
        const int itemId = res->getInt("ItemID");
        const std::string name = res->getString("Name");   
        double price = res->getDouble("Price");             
        std::string mealTypeStr = res->getString("MealType"); 
        bool availability = res->getBoolean("AvailabilityStatus");
        std::string dietaryType = res->getString("dietaryType");
        std::string spiceType = res->getString("spiceType");
        std::string cuisineType = res->getString("cuisineType");
        bool sweetToothType = res->getBoolean("sweetToothType");
        MenuItem item(itemId, name, price, MealType::Lunch, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    return items;
}
std::vector<MenuItem> LunchRepository::getDiscardedItems()
{
    std::map<std::string, std::string> filter = {
        {"MealType", "Lunch"}, {"isDiscarded", "1"}};

    sql::ResultSet *res = database.selectAll("MenuItem", filter);
    std::vector<MenuItem> items;

    while (res->next())
    {
        const int itemId = res->getInt("ItemID");
        const std::string name = res->getString("Name");    
        double price = res->getDouble("Price");               
        std::string mealTypeStr = res->getString("MealType"); 
        bool availability = res->getBoolean("AvailabilityStatus");
        std::string dietaryType = res->getString("dietaryType");
        std::string spiceType = res->getString("spiceType");
        std::string cuisineType = res->getString("cuisineType");
        bool sweetToothType = res->getBoolean("sweetToothType");
        MenuItem item(itemId, name, price, MealType::Lunch, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    return items;
}
