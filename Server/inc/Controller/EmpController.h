// EmployeeController.h
#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

#include "Employee.h"
#include "FeedbackService.h"
#include"RecommendationService.h"
#include<unordered_set>
#include"WordLoader.h"
#include"BreakfastRepository.h"


class EmployeeController {
public:
    std::string processOption(Employee* emp, int option, int socket, char* buffer);
};

#endif // EMPLOYEE_CONTROLLER_H