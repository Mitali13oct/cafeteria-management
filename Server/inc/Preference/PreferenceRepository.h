#pragma once
#include "DbOperation.h"
#include "Preference.h"
#include <string>

class PreferenceRepository
{
    DatabaseRepository dbRepo;

public:
    PreferenceRepository()
        : dbRepo("RecommendationEngine", "mitalijain", "Mishu@777") {}

    void savePreference(const Preference &preference)
    {
        std::map<std::string, std::string> data = {
            {"userId", std::to_string(preference.getUserId())},
            {"dietaryPreference", preference.getDietaryPreference()},
            {"spiceLevel", preference.getSpiceLevel()},
            {"cuisinePreference", preference.getCuisinePreference()},
            {"sweetTooth", preference.hasSweetTooth() ? "1" : "0"}};
        std::map<std::string, std::string> filter = {{"userId", std::to_string(preference.getUserId())}};
        dbRepo.update("Preference", data, filter);
    }

    Preference loadPreference(int userId)
    {
        std::map<std::string, std::string> filter = {{"userId", std::to_string(userId)}};
        sql::ResultSet *result = dbRepo.selectOne("Preference ", filter);
        Preference preference(userId, "vegetarian", "medium", "other", false); // Default preferences

        if (result->next())
        {
            preference.setDietaryPreference(result->getString("dietaryPreference"));
            preference.setSpiceLevel(result->getString("spiceLevel"));
            preference.setCuisinePreference(result->getString("cuisinePreference"));
            preference.setSweetTooth(result->getBoolean("sweetTooth"));
        }

        delete result; // Clean up the result set
        
        return preference;
    }
};
