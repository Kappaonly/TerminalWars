#pragma once

class Village {
private:
    int resources;
    int soldiers;

    int barracksLevel;
    int farmLevel;

public:
    Village() : resources(0), soldiers(0), barracksLevel(1), farmLevel(1) {};

    bool AdvanceDay();
    void UpgradeBarracks();
    void UpgradeFarm();
    void TrainSoldiers(int amount);
    bool Attack(int enemySoldiers);
    void PrintState();
    bool SendRaidParty(int soldierAmount);
    void ReturnParty(int soldierAmount);
    int GetBarracksUpgradeCost();
    int GetFarmUpgradeCost();
};
