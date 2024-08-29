// LunchRepository.h
#pragma once
#include "MenuRepository.h"

class LunchRepository : public MenuRepository
{
private:

    DatabaseRepository database;

public:
    LunchRepository() : database("RecommendationEngine", "mitalijain", "Mishu@777")
    {
    }
    ~LunchRepository()
    {
    }
    MealType getMealType();
    void addMenuItem(const MenuItem &item) override;
    void updateMenuItem(int, std::string, std::string) override;
    void deleteItem(int itemId) override;
    std::vector<MenuItem> getMenuItems() const override;
     std::vector<MenuItem> getDiscardedItems()override;
     MenuItem getItemById(int id);


};
