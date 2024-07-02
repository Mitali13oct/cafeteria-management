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
    // FeedbackRepository feedbackRepository;
    Feedback f(rating, comment, itemId, this->getId());
    fService.addFeedback(f);
}
std::string Employee::viewNotifications(NotificationType type)
{
    return nservice.getAllNotification(type);
}
std::string Employee::getAllMenuItem()
{
            std::cout<<"121\n";

    return menu.getAllMenuItem();
}
std::string Employee::getRolledOutItems()
{
    return recommendationService.getRolledOutItemsForToday();
}