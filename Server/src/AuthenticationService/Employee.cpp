#include "Employee.h"

std::string Employee::getRole() const { return "Employee"; }

void Employee::voteOnItem(std::vector<int> selectedItems)
{
    for (int id : selectedItems)
    {
        recommendationService.voteForItem(id);
    }
}
void Employee::provideFeedback(int itemId, std::string comment, double rating)
{
    Feedback f(rating, comment, itemId, this->getId());
    fService.addFeedback(f);
}
std::string Employee::viewNotifications(NotificationType type)
{
    return nservice.getAllNotification(type);
}
std::string Employee::getAllMenuItem()
{
    return menu.getAllMenuItem();
}
std::string Employee::getRolledOutItems(MenuRepository* mealType)
{
    return recommendationService.getSortedRecommendationsByPreference(this->getId(),mealType);
}

void Employee::updateProfile(Preference newPreference)
{

    preference.setDietaryPreference(newPreference.getDietaryPreference());
    preference.setSpiceLevel(newPreference.getSpiceLevel());
    preference.setCuisinePreference(newPreference.getCuisinePreference());
    preference.setSweetTooth(newPreference.hasSweetTooth());

    preferenceService.savePreference(preference);

}