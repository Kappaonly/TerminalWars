#include "Village.h"
#include <iostream>
#include "config.h"

bool Village::AdvanceDay() {
    resources += config::ResourcesPerFarmLevel * farmLevel;

    if (soldiers > resources) {
        std::cout << "You ran out of food for your soldiers." << std::endl;
        return false;
    }
    resources -= soldiers;
    return true;
}

int Village::GetBarracksUpgradeCost() {
     return barracksLevel * 100;
}

int Village::GetFarmUpgradeCost() {
     return farmLevel * 100;
}

void Village::UpgradeBarracks() {
    int cost = GetBarracksUpgradeCost();
    if (resources < cost) {
        std::cout << "Not enough resources to upgrade barracks (You need " << cost << ")" << std::endl;
        return;
    }
    resources -= cost;
    barracksLevel++;
}

void Village::UpgradeFarm() {
    int cost = GetFarmUpgradeCost();
    if (resources < cost) {
        std::cout << "Not enough resources to upgrade farm (You need " << cost << ")" << std::endl;
        return;
    }
    resources -= cost;
    farmLevel++;
}

void Village::TrainSoldiers(int amount) {
    int maxSoldierAmount = config::SoldiersPerBarrack * barracksLevel;
    if (soldiers + amount > maxSoldierAmount) {
        std::cout << "Not enough space in barracks. Your space in barracks is " << maxSoldierAmount - soldiers << std::endl;
        return;
    }
    int cost = config::SoldierCost * amount;
    if (resources < cost) {
        std::cout << "Not enough resources to buy soldiers (You need " << cost << ")" << std::endl;
        return;
    }
    resources -= cost;
    soldiers += amount;
}

bool Village::Attack(int enemySoldiers) {
    if (enemySoldiers > soldiers) {
        std::cout << "Enemy had more soldiers than you. You died in battle." << std::endl;
        return false;
    }
    soldiers -= enemySoldiers;
    std::cout << "You won the battle, but you lost " << enemySoldiers << " soldiers." << std::endl;
    return true;
}

void Village::PrintState() {
    std::cout << "Resources: " << resources << std::endl
        << "Soldiers: " << soldiers << std::endl
        << "Barrack Level: " << barracksLevel << std::endl
        << "Farm Level: " << farmLevel << std::endl;
}

bool Village::SendRaidParty(int soldierAmount) {
    if (soldierAmount > soldiers) {
        std::cout << "You don't have enough soldiers to do that." << std::endl;
        return false;
    }

    soldiers -= soldierAmount;
    return true;
}

void Village::ReturnParty(int soldierAmount) {
    int raidResources = soldierAmount * 20;
    std::cout << "Your soldiers have returned from battle with some stolen goods. (" << raidResources << " resources)" << std::endl;
    resources += raidResources;
    soldiers += soldierAmount;
}
