#include"../inc/MenuService.h"
    bool MenuService::addMenuItem(const MenuItem& item) {menuType->addMenuItem(item);}
    bool MenuService::updateMenuItem(int itemId,std::string columnToUpdate,std::string value){menuType->updateMenuItem( itemId, columnToUpdate, value);}
    bool MenuService::deleteItem(int itemId) {menuType->deleteItem(itemId);}
    std::string MenuService::getAllMenuItem() {
    std::vector<MenuItem> items = menuType->getMenuItems(); // Get all menu items
    std::string result;

    for (const auto& item : items) {
        result += "ID: " + std::to_string(item.getId()) + ", "
                + "Name: " + item.getName() + ", "
                + "Meal Type: " + mealTypeToString(item.getMealType()) + ", "
                + "Price: " + std::to_string(item.getPrice()) + ", "
                + "Availability: " + (item.getAvailability() ? "Yes" : "No") + "\n";
    }

    return result;
}

std::string MenuService::mealTypeToString(MealType mealType) {
    switch (mealType) {
        case MealType::Breakfast:
            return "Breakfast";
        case MealType::Lunch:
            return "Lunch";
        case MealType::Dinner:
            return "Dinner";
        default:
            return "Unknown";
    }
}

