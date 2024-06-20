#pragma once
#include "MenuItem.h"
#include "MenuRepository.h"
#include "Mealtype.h"
#include <vector>
#include"Server/inc/NotificationService/NotificationService.h"
class MenuService
{
    MenuRepository *menuType;

public:
    MenuService(MenuRepository *mealType) : menuType(mealType) {}
    MenuService() = default;
    bool addMenuItem(const MenuItem &item);
    bool updateMenuItem(int ,std::string,std::string);
    bool deleteItem(int itemId);
    std::string getAllMenuItem();
    std::string mealTypeToString(MealType mealType);
};
