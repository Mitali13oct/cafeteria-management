#pragma once

#include"RoleHandler.h"

class AdminHandler : public RoleHandler
{
public:
    bool handleOptions(Client &client) override;
};

