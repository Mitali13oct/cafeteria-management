#include "Employee.h"

std::string Employee::getRole() const { return "Employee"; }

int Employee::chooseMenuItem() {}
void Employee::provideFeedback(int itemId,std::string comment,double rating) {
    // FeedbackRepository feedbackRepository;
    Feedback f(rating,comment,itemId,this->getId());
    fService.addFeedback(f);


}
void Employee::viewNotifications() {}
std::string Employee::getAllMenuItem()
{
    return  menu.getAllMenuItem();
}
