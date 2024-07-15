
#pragma once
#include"RoleHandler.h"


class EmployeeHandler : public RoleHandler
{
public:
    bool handleOptions(Client &client) override;
};
