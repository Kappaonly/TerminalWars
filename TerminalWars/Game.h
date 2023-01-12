#pragma once
#include "config.h"
#include "Village.h"
#include "RaidParty.h"
#include <vector>

enum Action {
    UpgradeBarracks,
    UpgradeFarm,
    TrainSoldiers,
    SendRaidParty,
    EndDay,
    ShowState,
};

class Game {
private:
    int daysSinceLastAttack;
    int currentDay;
    Village playerVillage;
    std::vector<RaidParty> raidParties;

public:
    Game() : daysSinceLastAttack(0), currentDay(0), playerVillage() {}
    ~Game() {}
    void RunGame();

private:
    void PrintState();
    void TryRaid();
    void ProcessRaidParties();
    Action GetUserInput();
};
