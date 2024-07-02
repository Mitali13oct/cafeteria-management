#include "MenuService.h"
bool MenuService::addMenuItem(const MenuItem &item)
{

    menuType->addMenuItem(item);
    NotificationRepository notificationrepo;
    NotificationService notificationService(&notificationrepo);

    std::string addNotification = "Added Item: " + item.getName();
    std::cout<<"addNotification";
    Notification notificationObj(NotificationType::ItemAdded, addNotification);

    notificationService.addNotification(notificationObj);
}
bool MenuService::updateMenuItem(int itemId, std::string columnToUpdate, std::string value) { menuType->updateMenuItem(itemId, columnToUpdate, value); }
bool MenuService::deleteItem(int itemId) { menuType->deleteItem(itemId); }
std::string MenuService::getAllMenuItem()
{
            std::cout<<"122\n";

    std::vector<MenuItem> items = menuType->getMenuItems();
    std::string result;

    for (const auto &item : items)
    {
        result += "ID: " + std::to_string(item.getId()) + ", " + "Name: " + item.getName() + ", " + "Meal Type: " + Utility::mealTypeToString(item.getMealType()) + ", " + "Price: " + std::to_string(item.getPrice()) + ", " + "Availability: " + (item.getAvailability() ? "Yes" : "No") + "\n";
    }

    return result;
}

std::string MenuService::getDiscardedItems()
{
    std::vector<MenuItem> items = menuType->getDiscardedItems();
    std::string result;
    FeedbackService fservice;

    for (const auto &item : items)
    {
        std::vector<Feedback> feedbacks = fservice.getAllFeedback(item.getId());

        std::string feedbackComments;
        double totalRating = 0;
        int feedbackCount = feedbacks.size();

        for (const auto &feedback : feedbacks)
        {
            if (!feedbackComments.empty())
            {
                feedbackComments += ", ";
            }
            feedbackComments += feedback.getComment();
            totalRating += feedback.getRating();
        }

        double averageRating = (feedbackCount > 0) ? (totalRating) / feedbackCount : 0;

        result += "Item ID: " + std::to_string(item.getId()) + ", Name: " + item.getName() + ", Average Rating: " + std::to_string(averageRating) + ", Sentiments - " + feedbackComments + "\n";
    }
    return result;
}
