#pragma once
#include "MenuItem.h"
#include "MenuRepository.h"
#include "Mealtype.h"
#include <vector>
#include"NotificationService.h"
#include"Utility.h"
#include"FeedbackService.h"
class MenuService
{
    MenuRepository *menuType;
    // NotificationService nservice;
public:
    MenuService(MenuRepository *mealType) : menuType(mealType) {std::cout<<"MenuService\n";}
    MenuService() = default;
    bool addMenuItem(const MenuItem &item);
    bool updateMenuItem(int ,std::string,std::string);
    bool deleteItem(int itemId);
    std::string getAllMenuItem();
    std::string getDiscardedItems();

};
