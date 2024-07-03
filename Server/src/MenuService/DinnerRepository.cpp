// DinnerRepository.cpp
#include "DinnerRepository.h"
MealType DinnerRepository::getMealType()
{
    return MealType::Dinner;
}
void DinnerRepository::addMenuItem(const MenuItem &item)
{

    std::map<std::string, std::string> data = {
        {"Name", item.getName()},
        {"Price", std::to_string(item.getPrice())},
        {"MealType", "Dinner"},
        {"AvailabilityStatus", item.getAvailability() ? "1" : "0"},
        {"dietaryType", item.getDietaryType()},
        {"spiceType", item.getSpiceType()},
        {"cuisineType", item.getCuisineType()},
        {"sweetToothType", item.getSweetToothType() ? "1" : "0"}};
    std::cout << "Bf\n";
    database.insert("MenuItem", data);
}

void DinnerRepository::updateMenuItem(int itemId, std::string columnToUpdate, std::string value)
{
    std::map<std::string, std::string> data = {
        {columnToUpdate, value}};

    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};

    database.update("MenuItem", data, filter);
}

void DinnerRepository::deleteItem(int itemId)
{
    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};
    database.remove("MenuItem", filter);
}
MenuItem DinnerRepository::getItemById(int id)
{
    std::cout << "Fetching item with ID: " << id << std::endl;

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

            // Clean up the result set
            delete res;

            MenuItem item(id, name, price, MealType::Dinner, availability, dietaryType, spiceType, cuisineType, sweetToothType);
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

    // Return a default MenuItem or throw an exception as appropriate
    throw std::runtime_error("Failed to retrieve MenuItem from database");
}

std::vector<MenuItem> DinnerRepository::getMenuItems() const
{
  

    std::map<std::string, std::string> filter = {
        {"MealType", "Dinner"}};
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
        MenuItem item(itemId, name, price, MealType::Dinner, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    return items;
}
std::vector<MenuItem> DinnerRepository::getDiscardedItems()
{
    std::map<std::string, std::string> filter = {
        {"MealType", "Dinner"}, {"isDiscarded", "1"}};

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
        MenuItem item(itemId, name, price, MealType::Dinner, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    return items;
}
