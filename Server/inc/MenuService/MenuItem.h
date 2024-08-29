#pragma once
#include <string>
#include "Mealtype.h"
class MenuItem
{
private:
  std::string name;
  double price;
  MealType mealType;
  bool isAvailable;
  int id;
  std::string dietaryType;
  std::string spiceType;
  std::string cuisineType;
  bool sweetToothType;

public:
  MenuItem(const std::string &name, double price, MealType type, bool availability,
           const std::string &dietaryType, const std::string &spiceType, const std::string &cuisineType, bool sweetTooth)
      : id(-1), name(name), price(price), mealType(type), isAvailable(availability),
        dietaryType(dietaryType), spiceType(spiceType), cuisineType(cuisineType), sweetToothType(sweetTooth) {}

  MenuItem(int id, const std::string &name, double price, MealType type, bool availability,
           const std::string &dietaryType, const std::string &spiceType, const std::string &cuisineType, bool sweetTooth)
      : id(id), name(name), price(price), mealType(type), isAvailable(availability),
        dietaryType(dietaryType), spiceType(spiceType), cuisineType(cuisineType), sweetToothType(sweetTooth) {}
  MenuItem() : id(0), name(""), price(0.0), mealType(MealType::Unknown), isAvailable(false),
               dietaryType(""), spiceType(""), cuisineType(""), sweetToothType(false) {}

  std::string getName() const;
  bool getAvailability() const;
  double getPrice() const;
  int getId() const;
  MealType getMealType() const;
  std::string getDietaryType() const;
  std::string getSpiceType() const;
  std::string getCuisineType() const;
  bool getSweetToothType() const;
  void setName(const std::string &name);
  void setPrice(double price);
};
