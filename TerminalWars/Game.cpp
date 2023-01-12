#include "Game.h"
#include <iostream>
#include "RaidParty.h"
#include "config.h"

void GameOver() {
    std::cout << "Game Over :(" << std::endl;
    exit(0);
}

int GetRandomNumber(int min, int max) {
    return rand() % (max - min) + min;
}

Action Game::GetUserInput() {
    std::cout << "Actions:" << std::endl
        << "  1. Upgrade Barracks (" << playerVillage.GetBarracksUpgradeCost() << " resources)" << std::endl
        << "  2. Upgrade Farm (" << playerVillage.GetFarmUpgradeCost() << " resources)" << std::endl
        << "  3. Train Soldiers (" << config::SoldierCost << " resources per soldier)" << std::endl
        << "  4. Send Raid Party" << std::endl
        << "  5. End Day" << std::endl
        << "  6. Show State" << std::endl;
    int action;
    do {
        std::cout << "Select Action: ";
        std::cin >> action;
    } while (action < 1 || action > 6);
    return Action(action - 1);
}

void Game::RunGame() {
    srand(time(0));
    while (true) {
        currentDay++;
        daysSinceLastAttack++;
        if (!playerVillage.AdvanceDay()) {
            GameOver();
        }
        PrintState();
        ProcessRaidParties();
        TryRaid();
        while (true) {
            Action userInput = GetUserInput();
            if (userInput == EndDay) break;
            else if (userInput == UpgradeBarracks) playerVillage.UpgradeBarracks();
            else if (userInput == UpgradeFarm) playerVillage.UpgradeFarm();
            else if (userInput == TrainSoldiers) {
                int amount;
                std::cout << "Enter number of soldiers to train: ";
                std::cin >> amount;
                playerVillage.TrainSoldiers(amount);
            }
            else if (userInput == SendRaidParty) {
                int amount;
                std::cout << "Enter number of soldiers to send: ";
                std::cin >> amount;
                bool success = playerVillage.SendRaidParty(amount);
                if (success) {
                    RaidParty party;
                    party.daysRemaining = GetRandomNumber(2, 6);
                    party.soldierAmount = amount;
                    raidParties.push_back(party);
                }
            }
            PrintState();
        }
    }
}

void Game::ProcessRaidParties() {
    for (auto it = raidParties.begin(); it != raidParties.end();) {
        RaidParty* party = it.base();
        party->daysRemaining--;
        if (party->daysRemaining == 0) {
            int enemySoldiers = GetRandomNumber(2 + (currentDay / 5) * 10, currentDay * 20);
            if (party->soldierAmount < enemySoldiers) {
                std::cout << "Your raid party has perished in battle" << std::endl;
            } else {
                playerVillage.ReturnParty(party->soldierAmount - enemySoldiers);
            }
            it = raidParties.erase(it);
        } else ++it;
    }
}

void Game::PrintState() {
    std::cout << std::endl << "------------------------------" << std::endl;
    std::cout << "Day " << currentDay << std::endl;
    playerVillage.PrintState();
    std::cout << std::endl;
}

void Game::TryRaid() {
    if (currentDay <= config::GracePeriod) return;

    int raidChance = daysSinceLastAttack * 10;
    if ((rand() % 100) >= raidChance) return;

    daysSinceLastAttack = 0;

    int soldierAmount = GetRandomNumber(2 + (currentDay / 5) * 50, currentDay * 40);
    std::cout << "Your village is being attacked by " << soldierAmount << " soldiers." << std::endl;
    bool survived = playerVillage.Attack(soldierAmount);
    if (!survived) {
        GameOver();
    }
}

