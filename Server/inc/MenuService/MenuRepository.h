#pragma once
#include "MenuItem.h"
#include "DbOperation.h"
#include <vector>

class MenuRepository
{

public:
    virtual void addMenuItem(const MenuItem &item) = 0;
    virtual void updateMenuItem(int, std::string, std::string) = 0;
    virtual void deleteItem(int itemId) = 0;
    virtual std::vector<MenuItem> getMenuItems() const = 0;
    virtual MealType getMealType() = 0;
    virtual std::vector<MenuItem> getDiscardedItems() = 0;
    virtual MenuItem getItemById(int id) = 0;
};
