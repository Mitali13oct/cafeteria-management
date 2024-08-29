
#include "BreakfastRepository.h"
MealType BreakfastRepository::getMealType()
{
    return MealType::Breakfast;
}
void BreakfastRepository::addMenuItem(const MenuItem &item)
{

    std::map<std::string, std::string> data = {
        {"Name", item.getName()},
        {"Price", std::to_string(item.getPrice())},
        {"MealType", "Breakfast"},
        {"AvailabilityStatus", item.getAvailability() ? "1" : "0"},
        {"dietaryType", item.getDietaryType()},
        {"spiceType", item.getSpiceType()},
        {"cuisineType", item.getCuisineType()},
        {"sweetToothType", item.getSweetToothType() ? "1" : "0"}};
    
    database.insert("MenuItem", data);
}

void BreakfastRepository::updateMenuItem(int itemId, std::string columnToUpdate, std::string value)
{
    std::map<std::string, std::string> data = {
        {columnToUpdate, value}};

    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};

    database.update("MenuItem", data, filter);
}

void BreakfastRepository::deleteItem(int itemId)
{
    std::map<std::string, std::string> filter = {
        {"ItemID", std::to_string(itemId)}};
    database.remove("MenuItem", filter);
}
MenuItem BreakfastRepository::getItemById(int id)
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

      
            MealType mealType;
            if (mealTypeStr == "Breakfast")
            {
                mealType = MealType::Breakfast;
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
                mealType = MealType::Unknown;
            }

            MenuItem item(id, name, price, mealType, availability, dietaryType, spiceType, cuisineType, sweetToothType);
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

std::vector<MenuItem> BreakfastRepository::getMenuItems() const
{
    

    std::map<std::string, std::string> filter = {
        {"MealType", "Breakfast"}};
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
        MenuItem item(itemId, name, price, MealType::Breakfast, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    
    return items;
}
std::vector<MenuItem> BreakfastRepository::getDiscardedItems()
{
    std::map<std::string, std::string> filter = {
        {"MealType", "Breakfast"}, {"isDiscarded", "1"}};

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
        MenuItem item(itemId, name, price, MealType::Breakfast, availability, dietaryType, spiceType, cuisineType, sweetToothType);
        items.push_back(item);
    }
    delete res;
    return items;
}
