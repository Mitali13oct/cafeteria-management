#include"Admin.h"


    std::string Admin::getRole() const  { return "Admin"; }

    void Admin::addMenuItem(const MenuItem& item){std::cout<<"admin";menu.addMenuItem(item);}
    void Admin::updateMenuItem(int itemId,std::string columnToUpdate,std::string value){menu.updateMenuItem( itemId, columnToUpdate, value);}
    void Admin::deleteItem(int itemId){menu.deleteItem(itemId);}
    std::string Admin::getAllMenuItem(){ return menu.getAllMenuItem();}
