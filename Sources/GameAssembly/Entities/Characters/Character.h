#pragma once
#include "../Entity.h"

class Character : public Entity
{
public:
    Character() = default;

    virtual void checkAbilites() = 0;

    void firstAbility() override;
    void secondAbility() override;
    void thirdAbility() override;
    void fourthAbility() override;
};
