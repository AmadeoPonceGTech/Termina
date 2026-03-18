#pragma once
#include <iostream>

enum class EClass {
    ASSASSIN,
    CLOSEDDPS,
    RANGEDDPS,
    TANK,
    SUPPORT
};

class Entity
{
protected:
    std::string name;
    EClass entityClass;
    std::string description;

    int level;
    int maxLevel;

    float baseHealth; // lvl 1 value
    float currentHealth;
    float maxHealth; // calculated depending on the level

    float shield;

    float baseAttackDamage;
    float currentAttackDamage;
    float maxAttackDamage;

    float baseAttackPower;
    float currentAttackPower;
    float maxAttackPower;

    float baseArmor;
    float currentArmor;
    float maxArmor;

    float basePowerResist;
    float currentPowerResist;
    float maxPowerResist;

    float speed;

    int CD1;
    int CD2;
    int CD3;
    int CD4;

public:
    virtual ~Entity() = default;

    Entity();

#pragma region Getters

    float getCurrentHealth();
    float getShield();
    float getCurrentAttackDamage();
    float getCurrentAttackPower();
    float getCurrentArmor();
    float getCurrentPowerResist();

    int getCD1();
    int getCD2();
    int getCD3();
    int getCD4();

#pragma endregion

#pragma region Setters

    void setCurrentHealth(float newHealth);
    void setShield(float newShield);
    void setCurrentAttackDamage(float newDamage);
    void setCurrentAttackPower(float newPower);
    void setCurrentArmor(float newArmor);
    void setCurrentPowerResist(float newPowerResist);

    void setCD1(int newCD1);
    void setCD2(int newCD2);
    void setCD3(int newCD3);
    void setCD4(int newCD4);

#pragma endregion

};