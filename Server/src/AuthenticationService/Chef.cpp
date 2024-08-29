#include "Chef.h"

std::string Chef::getRole() const { return "Chef"; }

std::string Chef::getRecommendation(MenuRepository *menu)
{
    std::string recommendations = recommendationService.getAllRecommendations(menu->getMealType());
    if (recommendations.empty())
    {
        recommendationService.generateRecommendations(menu);
        recommendations = recommendationService.getAllRecommendations(menu->getMealType());
    }
    return recommendations;
}
std::string Chef::getVotedItems(std::string mealTypeStr)
{
    return recommendationService.getVotedItems(mealTypeStr);
}
void Chef::rollOutMenu(int number, std::string mealType) { recommendationService.rollOutRecommendations(number, mealType); }
void Chef::chooseItemToPrepare(std::vector<int> itemIds)
{

    for (int id : itemIds)
    {
        recommendationService.prepareItem(id);
    }
}
std::string Chef::getDiscardedItems()
{
    return menu.getDiscardedItems();
}

void Chef::deleteItem(int itemId)
{
    menu.deleteItem(itemId);
}

void Chef::addQuestion(int itemid)
{
    discardService.addQuestion(itemid);
}