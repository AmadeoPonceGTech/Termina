#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>

enum class EUpgradeState {
    CHECKINGXP,
    GENERATEUPGRADE,
    CHOOSINGUPGRADE,
    APPLYUPGRADE
};

struct Bonus {
    std::string name;
    int rarity;
};

class PlayerXP {

    float currentXP;
    float XPNeededForLvl2;
    float XPNeeded;
    float finalXPNeeded;

    bool choosing;

    EUpgradeState upgradeState;

    std::random_device rd;

    std::vector<Bonus> bonusChoices;
    std::unique_ptr<Bonus> bonusChose;

    std::vector<std::string> commonBonusesVector;
    std::vector<std::string> rareBonusesVector;
    std::vector<std::string> epicBonusesVector;
    std::vector<std::string> legendaryBonusesVector;

public:
    PlayerXP();

    void upgradeSystem(int level);
    bool levelUp(int level);

    bool getChoosing() const;
    void addCurrentXP(int xpToAdd);
};

