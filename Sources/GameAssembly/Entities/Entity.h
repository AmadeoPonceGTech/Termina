#pragma once
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <random>
#include <memory>

enum class EClass {
    ASSASSIN,
    CLOSEDDPS,
    RANGEDDPS,
    TANK,
    SUPPORT
};

enum class Poison {
    NOT_POISONED = 0,
    FIRST_TURN = 15,
    SECOND_TURN = 12,
    THIRD_TURN = 8,
    FOURTH_TURN = 5,
    FIFTH_TURN = 3
};

enum class Burn {
    NOT_BURNED = 0,
    FIRST_TURN = 15,
    SECOND_TURN = 12,
    THIRD_TURN = 8
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
    /// \brief current without buff/debuff
    float maxAttackDamage;

    float baseAttackPower;
    float currentAttackPower;
    /// \brief current without buff/debuff
    float maxAttackPower;

    float baseArmor;
    float currentArmor;
    float maxArmor;

    float basePowerResist;
    float currentPowerResist;
    float maxPowerResist;

    float baseSpeed;
    float currentSpeed;

    int CD1;
    int CD2;
    int CD3;
    int CD4;

    int poisonCD;
    int burnCD;
    int tauntCD;
    int stunCD;

    bool firstAbilityUp;
    bool secondAbilityUp;
    bool thirdAbilityUp;
    bool fourthAbilityUp;

    bool isPoisoned;
    bool isBurned;
    bool isTaunt;
    bool isStun;

    Poison poison;
    Burn burn;

public:
    virtual ~Entity() = default;

    Entity();

    virtual void startTurn() = 0;
    virtual void endTurn() = 0;

#pragma region Getters

    float getCurrentHealth();
    float getShield();
    float getCurrentAttackDamage();
    float getCurrentAttackPower();
    float getCurrentArmor();
    float getCurrentPowerResist();
    float getMaxHealth();
    float getMaxAttackDamage();
    float getMaxAttackPower();
    float getMaxArmor();
    float getMaxPowerResist();

    int getCD1();
    int getCD2();
    int getCD3();
    int getCD4();

    int getPoisonCD();
    int getBurnCD();
    int getTauntCD();
    int getStunCD();

    bool getFirstAbilityUp();
    bool getSecondAbilityUp();
    bool getThirdAbilityUp();
    bool getFourthAbilityUp();

    bool getIsPoisoned();
    bool getIsBurned();
    bool getIsTaunt();
    bool getIsStun();

    float getPoison();
    float getBurn();

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

    void setIsPoisoned(bool newIsPoisoned);
    void setIsBurned(bool newIsBurned);
    void setIsTaunt(bool newIsTaunt);
    void setIsStun(bool newIsStun);

#pragma endregion

};