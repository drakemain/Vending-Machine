#include <ctime>

#include "VendingMachine.h"

// TODO refactor: pass vectors by reference to avoid copying

VendingMachine::VendingMachine() {
    this->name = "Soda Machine";
    this->currentCredit = 0.0;

    std::vector<std::string> sodas = {
      "Cola",
      "Cherry Cola",
      "Diet Cola",
      "Root Beer",
      "Lemon Lime",
      "Orange",
      "Grape",
      "Cherry",
      "RoidRage Energy",
      "Water"
    };

    std::vector<double> cost = {
      1.5,
      1.5,
      1.5,
      1.5,
      1.5,
      1.5,
      1.5,
      1.5,
      2.25,
      1.25
    };

    this->itemSlots = sodas.size();

    double changeList[4] = { .01, .05, .1, .25 };

    randomInventoryGenerator(changeList, sodas, cost);
}

VendingMachine::VendingMachine(std::vector<std::string> customList, std::vector<double> cost,
                               std::string newName) {
    this->name = newName;
    this->itemSlots = customList.size();
    this->currentCredit = 0.0;

    double changeList[4] = { .01, .05, .1, .25 };

    randomInventoryGenerator(changeList, customList, cost, itemSlots);
}

VendingMachine::~VendingMachine() {}

void VendingMachine::randomInventoryGenerator(double changeList[], std::vector<std::string> items,
                                              std::vector<double> costList, int maxInventory) {
    srand(time(0));

    for (int i = 0; i < itemSlots; i++) {
        itemList.item.push_back(items[i]);
        itemList.cost.push_back(costList[i]);
        itemList.inInventory.push_back(rand() % maxInventory);
    }

    // TODO bug?
    // does this actually work? usually you pass the array length as an extra parameter,
    // or better yet, pass a vector
    for (int i = 0; i < sizeof(changeList); i++) {
        change.item.push_back(std::to_string(changeList[i]));
        change.inInventory.push_back((rand() % 90) + 10);
    }
}

std::string VendingMachine::getItem(int item) const {
    return this->itemList.item[item];
}

int VendingMachine::getInInventory(int item) const {
    return this->itemList.inInventory[item];
}

double VendingMachine::getCost(int item) const {
    return this->itemList.cost[item];
}

double VendingMachine::getCurrentCredit() const {
    return this->currentCredit;
}

int VendingMachine::getItemSlots() const {
    return this->itemSlots;
}

std::string VendingMachine::getName() const {
    return this->name;
}

void VendingMachine::insertMoney(double insertedAmount) {
    this->currentCredit += insertedAmount;
}

bool VendingMachine::dispenseItem(int item) {
    if (this->itemList.inInventory[item] > 0 && this->sufficientCreditCheck(item)) {
        // TODO refactor: post-decrement
        this->itemList.inInventory[item] -= 1;
        this->currentCredit -= this->itemList.cost[item];

        return true;
    } else {
      return false;
    }
}

double VendingMachine::ejectChange() {
    double changeToDispense = this->currentCredit;
    this->currentCredit = 0.00;

    // TODO refactor: just return currentCredit
    return changeToDispense;
}

bool VendingMachine::sufficientCreditCheck(int item) const {
    // TODO refactor: return expr
    if (this->currentCredit >= this->itemList.cost[item]) {
      return true;
    } else {
      return false;
    }
}
