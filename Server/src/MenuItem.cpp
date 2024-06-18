#include"../inc/MenuItem.h"
    std::string MenuItem::getName() const { return name; }
    bool MenuItem::getAvailability() const { return isAvailable; }
    double MenuItem::getPrice() const { return price; }
    MealType MenuItem::getMealType() const { return mealType; }
    int MenuItem::getId() const {return id;}
    void MenuItem::setName(const std::string& name) { this->name = name; }
    void MenuItem::setPrice(double price) { this->price = price; }

