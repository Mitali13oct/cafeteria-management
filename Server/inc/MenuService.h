#pragma once
#include "MenuItem.h"
#include"MenuRepository.h"
#include"Mealtype.h"
#include <vector>

class MenuService {
    MenuRepository* menu1;
public:
    bool addMenuItem(const MenuItem& item) ;
    bool updateMenuItem(const MenuItem& item) ;
    bool deleteItem(int itemId) ;
    std::vector<MenuItem>getAllMenuItem(MealType) ;
};
