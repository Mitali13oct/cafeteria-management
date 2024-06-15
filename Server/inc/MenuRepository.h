#pragma once
#include "MenuItem.h"
#include <vector>

class MenuRepository {
public:
    virtual void addMenuItem(const MenuItem& item) = 0;
    virtual void updateMenuItem(const MenuItem& item) = 0;
    virtual void deleteItem(int itemId) = 0;
    virtual std::vector<MenuItem> getMenuItems() const = 0;
};
