#include "Server/inc/MenuService/MenuService.h"
bool MenuService::addMenuItem(const MenuItem &item)
{

    menuType->addMenuItem(item);
    NotificationRepository notificationrepo;
    NotificationService notificationService(notificationrepo);
    auto now = std::chrono::system_clock::now();

    // Convert to time_t (since epoch)
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to struct tm
    std::tm* now_tm = std::localtime(&now_c);

    // Format time as string (e.g., "YYYY-MM-DD HH:MM:SS")
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

    std::string addNotification = "Added Item: "+item.getName();
    std::string time =ss.str();
    Notification notificationObj(NotificationType::MenuUpdate,addNotification,time);
   std::cout<<"menuservice";
    notificationService.addNotification(notificationObj);


}
bool MenuService::updateMenuItem(int itemId, std::string columnToUpdate, std::string value) { menuType->updateMenuItem(itemId, columnToUpdate, value); }
bool MenuService::deleteItem(int itemId) { menuType->deleteItem(itemId); }
std::string MenuService::getAllMenuItem()
{
    std::vector<MenuItem> items = menuType->getMenuItems(); // Get all menu items
    std::string result;

    for (const auto &item : items)
    {
        result += "ID: " + std::to_string(item.getId()) + ", " + "Name: " + item.getName() + ", " + "Meal Type: " + mealTypeToString(item.getMealType()) + ", " + "Price: " + std::to_string(item.getPrice()) + ", " + "Availability: " + (item.getAvailability() ? "Yes" : "No") + "\n";
    }

    return result;
}

std::string MenuService::mealTypeToString(MealType mealType)
{
    switch (mealType)
    {
    case MealType::Breakfast:
        return "Breakfast";
    case MealType::Lunch:
        return "Lunch";
    case MealType::Dinner:
        return "Dinner";
    default:
        return "Unknown";
    }
}
