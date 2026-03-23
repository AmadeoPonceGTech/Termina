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

    bool firstAbilityUp;
    bool secondAbilityUp;
    bool thirdAbilityUp;
    bool fourthAbilityUp;

    bool isPoisoned;
    bool isBurnt;
    bool isTaunt;
    bool isStun;

public:
    virtual ~Entity() = default;

    Entity();

    virtual void startTurn() = 0;
    virtual void endTurn() = 0;

    virtual bool entityTurn(std::vector<std::shared_ptr<Entity>> characters, std::vector<std::shared_ptr<Entity>> enemies) = 0;

    void manageStatusEffect();
    void resetStats();

#pragma region Getters

    std::string getName() const;
    float getCurrentHealth() const;
    float getShield() const;
    float getCurrentAttackDamage() const;
    float getCurrentAttackPower() const;
    float getCurrentArmor() const;
    float getCurrentPowerResist() const;
    float getMaxHealth() const;
    float getMaxAttackDamage() const;
    float getMaxAttackPower() const;
    float getMaxArmor() const;
    float getMaxPowerResist() const;
    float getCurrentSpeed() const;

    int getCD1() const;
    int getCD2() const;
    int getCD3() const;
    int getCD4() const;

    int getPoisonCD() const;
    int getBurnCD() const;
    int getTauntCD() const;

    bool getFirstAbilityUp() const;
    bool getSecondAbilityUp() const;
    bool getThirdAbilityUp() const;
    bool getFourthAbilityUp() const;

    bool getIsPoisoned() const;
    bool getIsBurnt() const;
    bool getIsTaunt() const;
    bool getIsStun() const;

    EClass getClass() const;

#pragma endregion

#pragma region Setters

    void setCurrentHealth(float newHealth);
    void setShield(float newShield);
    void setCurrentAttackDamage(float newDamage);
    void setCurrentAttackPower(float newPower);
    void setCurrentArmor(float newArmor);
    void setCurrentPowerResist(float newPowerResist);
    void setCurrentSpeed(float newSpeed);

    void setCD1(int newCD1);
    void setCD2(int newCD2);
    void setCD3(int newCD3);
    void setCD4(int newCD4);

    void setPoisonCD(int newPoisonCD);
    void setBurnCD(int newBurnCD);
    void setTauntCD(int newTauntCD);

    void setIsPoisoned(bool newIsPoisoned);
    void setIsBurnt(bool newIsBurnt);
    void setIsTaunt(bool newIsTaunt);
    void setIsStun(bool newIsStun);

#pragma endregion

};