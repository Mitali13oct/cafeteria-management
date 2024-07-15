#pragma once
#include"RoleHandler.h"

class ChefHandler : public RoleHandler
{
public:
    bool handleOptions(Client &client) override;
};

