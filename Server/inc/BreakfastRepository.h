// BreakfastRepository.h
#pragma once
#include "MenuRepository.h"

class BreakfastRepository : public MenuRepository
{
private:
    sql::Driver *driver;
    sql::Connection *con;

    DatabaseRepository database;

public:
    BreakfastRepository() : database("RecommendationEngine", "mitalijain", "Mishu@777")
    {
    }
    ~BreakfastRepository()
    {
    }

    void addMenuItem(const MenuItem &item) override;
    void updateMenuItem(int,std::string,std::string) override;
    void deleteItem(int itemId) override;
    std::vector<MenuItem> getMenuItems() const override;
};
