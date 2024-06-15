#include"../inc/MenuItem.h"
    int MenuItem::getId() const { return id; }
    std::string MenuItem::getName() const { return name; }
    std::string MenuItem::getDescription() const { return description; }
    double MenuItem::getPrice() const { return price; }

    void MenuItem::setName(const std::string& name) { this->name = name; }
    void MenuItem::setDescription(const std::string& description) { this->description = description; }
    void MenuItem::setPrice(double price) { this->price = price; }

