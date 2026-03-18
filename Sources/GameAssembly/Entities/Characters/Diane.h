#pragma once
#include "Character.h"

class Diane : public Character
{
public :
    Diane();

    void checkAbilites() override;
    void firstAbility() override;
};
