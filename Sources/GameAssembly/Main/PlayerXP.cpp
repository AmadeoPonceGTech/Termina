
#include "PlayerXP.h"

#include "../../ThirdParty/ImGui/imgui.h"

PlayerXP::PlayerXP() {
    upgradeState = EUpgradeState::CHECKINGXP;
    choosing = false;

    XPNeededForLvl2 = 100;
    finalXPNeeded = 100000;
    currentXP = 100;
    XPNeeded = XPNeededForLvl2;

    commonBonusesVector.push_back("Heal 10 Percent of Max HP of everyone");
    commonBonusesVector.push_back("Heal 50 Percent of Max HP to one selected character");
    commonBonusesVector.push_back("AP + 2 Percent to one selected character");
    commonBonusesVector.push_back("AD + 2 Percent to one selected character");
    commonBonusesVector.push_back("Armor + 2 Percent to one selected character");
    commonBonusesVector.push_back("Magic Resistance + 2 Percent to one selected character");
    commonBonusesVector.push_back("Speed + 3 Percent to one selected character");
    commonBonusesVector.push_back("Stats + 2 Percent for one class");
    commonBonusesVector.push_back("+ 5 Percent chance to have better upgrades next level up");

    rareBonusesVector.push_back("Heal 15 Percent of Max HP of everyone");
    rareBonusesVector.push_back("Heal 65 Percent of Max HP to one selected character");
    rareBonusesVector.push_back("AP + 5 Percent to one selected character");
    rareBonusesVector.push_back("AD + 5 Percent to one selected character");
    rareBonusesVector.push_back("Armor + 5 Percent to one selected character");
    rareBonusesVector.push_back("Magic Resistance + 5 Percent to one selected character");
    rareBonusesVector.push_back("Speed + 6 Percent to one selected character");
    rareBonusesVector.push_back("Stats + 4 Percent for one class");
    rareBonusesVector.push_back("+ 10 Percent chance to have better upgrades next level up");

    epicBonusesVector.push_back("Heal 20 Percent of Max HP of everyone");
    epicBonusesVector.push_back("Heal 75 Percent of Max HP to one selected character");
    epicBonusesVector.push_back("AP + 7.5 Percent to one selected character");
    epicBonusesVector.push_back("AD + 7.5 Percent to one selected character");
    epicBonusesVector.push_back("Armor + 10 Percent to one selected character");
    epicBonusesVector.push_back("Magic Resistance + 10 Percent to one selected character");
    epicBonusesVector.push_back("Speed + 12 Percent to one selected character");
    epicBonusesVector.push_back("Stats + 8 Percent for one class");
    epicBonusesVector.push_back("+ 15 Percent chance to have better upgrades next level up");

    legendaryBonusesVector.push_back("Heal 30 Percent of Max HP of everyone");
    legendaryBonusesVector.push_back("Heal 100 Percent of Max HP to one selected character");
    legendaryBonusesVector.push_back("AP + 10 Percent to one selected character");
    legendaryBonusesVector.push_back("AD + 10 Percent to one selected character");
    legendaryBonusesVector.push_back("Armor + 15 Percent to one selected character");
    legendaryBonusesVector.push_back("Magic Resistance + 15 Percent to one selected character");
    legendaryBonusesVector.push_back("Speed + 20 Percent to one selected character");
    legendaryBonusesVector.push_back("Stats + 10 Percent for one class");
    legendaryBonusesVector.push_back("+ 20 Percent chance to have better upgrades next level up");
}

bool PlayerXP::levelUp(int level)
{
    if (currentXP >= XPNeeded)
    {
        currentXP -= XPNeeded;
        XPNeeded = XPNeededForLvl2 + (finalXPNeeded - XPNeededForLvl2) * ((level - 1) / (9999 - 1));
        return true;
    }
    return false;
}

void PlayerXP::upgradeSystem(int level)
{
    static std::mt19937 rng(rd());

    switch (upgradeState) {
        case EUpgradeState::CHECKINGXP : {
            if (levelUp(level))
            {
                choosing = true;
                upgradeState = EUpgradeState::GENERATEUPGRADE;
            }
            else choosing = false;
            break;
        }

        case EUpgradeState::GENERATEUPGRADE : {
            bonusChoices.clear();

            std::uniform_int_distribution<int> rarity(1, 100);
            std::uniform_int_distribution<int> bonus(0, 8);

            for (int i = 0; i < 3; i++)
            {
                int rarityPercent = rarity(rng);
                int randomBonus = bonus(rng);

                if (rarityPercent <= 5) { bonusChoices.push_back({legendaryBonusesVector[randomBonus], 4}); }
                else if (rarityPercent <= 15) { bonusChoices.push_back({epicBonusesVector[randomBonus], 3}); }
                else if (rarityPercent <= 30) { bonusChoices.push_back({rareBonusesVector[randomBonus], 2}); }
                else if (rarityPercent <= 100) { bonusChoices.push_back({commonBonusesVector[randomBonus], 1}); }

            }

            upgradeState = EUpgradeState::CHOOSINGUPGRADE;

            break;
        }

        case EUpgradeState::CHOOSINGUPGRADE : {

            ImGui::Begin("Choose an upgrade");
            ImGui::Columns(3, nullptr, true);

            for (int i = 0; i < bonusChoices.size(); i++) {
                auto& choice = bonusChoices[i];
                std::string label = "Choice" + std::to_string(i + 1);
                ImGui::BeginChild(label.c_str(), ImVec2(0, 600), true);

                ImGui::Dummy(ImVec2(0, 250));

                float textWidth = ImGui::CalcTextSize(choice.name.c_str()).x;
                float avail = ImGui::GetContentRegionAvail().x;
                ImGui::SetCursorPosX((avail - textWidth) * 0.5f);
                ImGui::Text("%s", choice.name.c_str());

                ImGui::Dummy(ImVec2(0, 200));

                float buttonWidth = 120.0f;
                ImGui::SetCursorPosX((avail - buttonWidth) * 0.5f);

                std::string labelB = "Choose##" + std::to_string(i);
                if (ImGui::Button(labelB.c_str(), ImVec2(buttonWidth, 0))) {
                    bonusChose = std::make_unique<Bonus>(choice);
                    upgradeState = EUpgradeState::APPLYUPGRADE;
                }

                ImGui::EndChild();

                if ((i + 1) % 3 != 0)
                    ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::End();
            break;
        }

        case EUpgradeState::APPLYUPGRADE : {

            upgradeState = EUpgradeState::CHECKINGXP;

            break;
        }
    }
}

bool PlayerXP::getChoosing() const { return choosing; }

void PlayerXP::addCurrentXP(int xpToAdd) { currentXP += xpToAdd; }
