#pragma once
#include <string>

class MenuItem {
private:
    int id;
    std::string name;
    std::string description;
    double price;
    double rating;
    std::string comment;

public:
    MenuItem(int id, const std::string& name, const std::string& description, double price, double rating,std::string comment)
        : id(id), name(name), description(description), price(price),rating(rating),comment(comment) {}

    int getId()const ;
    std::string getName() const ;
    std::string getDescription() const ;
    double getPrice() const;

    void setName(const std::string& name);
    void setDescription(const std::string& description) ;
    void setPrice(double price);
};
