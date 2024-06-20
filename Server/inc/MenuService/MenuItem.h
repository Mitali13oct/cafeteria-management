#pragma once
#include <string>
#include"Mealtype.h"
class MenuItem {
private:
    std::string name;
    double price;
   MealType mealType;
   bool isAvailable;
   int id;

public:
    MenuItem( const std::string& name, double price,MealType type, bool availability)
        :  id(-1),name(name), price(price) ,mealType(type), isAvailable(availability){}
    MenuItem( int id,const std::string& name, double price,MealType type, bool availability)
        :  id(id),name(name), price(price) ,mealType(type), isAvailable(availability){}

    std::string getName() const ;
    bool getAvailability() const ;
    double getPrice() const;
    int getId()const;
    MealType getMealType() const;
    void setName(const std::string& name);
    void setDescription(const std::string& description) ;
    void setPrice(double price);
};
