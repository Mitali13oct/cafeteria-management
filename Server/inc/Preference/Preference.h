#pragma once
#include <string>

class Preference {
private:
    int userId;
    std::string dietaryPreference;
    std::string spiceLevel;
    std::string cuisinePreference;
    bool sweetTooth;

public:
    Preference(int userId, const std::string &dietaryPreference, const std::string &spiceLevel, const std::string &cuisinePreference, bool sweetTooth)
        : userId(userId), dietaryPreference(dietaryPreference), spiceLevel(spiceLevel), cuisinePreference(cuisinePreference), sweetTooth(sweetTooth) {}

  
    int getUserId() const {
        return userId;
    }

    std::string getDietaryPreference() const {
        return dietaryPreference;
    }

    std::string getSpiceLevel() const {
        return spiceLevel;
    }

    std::string getCuisinePreference() const {
        return cuisinePreference;
    }

    bool hasSweetTooth() const {
        return sweetTooth;
    }

    void setDietaryPreference(const std::string &preference) {
        dietaryPreference = preference;
    }

    void setSpiceLevel(const std::string &level) {
        spiceLevel = level;
    }

    void setCuisinePreference(const std::string &preference) {
        cuisinePreference = preference;
    }

    void setSweetTooth(bool hasSweetTooth) {
        sweetTooth = hasSweetTooth;
    }
};
