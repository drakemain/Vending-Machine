#pragma once
#include "VendingMachine.h"
#include <ctime>

VendingMachine::VendingMachine(){
	std::vector<std::string> sodas = { "Cola", "Cherry Cola", "Diet Cola", "Root Beer", "Lemon Lime", "Orange", "Grape", "Cherry", "RoidRage Energy", "Water" };
	double changeList[4] = { .01, .05, .1, .25 };
	itemSlots = sodas.size();
	currentCredit = 0.0;
	randomInventoryGenerator(changeList, sodas);
}

VendingMachine::VendingMachine(std::vector<std::string> customList){
	double changeList[4] = { .01, .05, .1, .25 };
	itemSlots = customList.size();
	currentCredit = 0.0;
	randomInventoryGenerator(changeList, customList);
}

VendingMachine::~VendingMachine(){}

void VendingMachine::randomInventoryGenerator(double changeList[], std::vector<std::string> items, int maxInventory){
	srand(time(0));
	for (int i = 0; i < itemSlots; i++){
		itemList.item.push_back(items[i]);
		itemList.cost.push_back(1.0);
		itemList.inInventory.push_back(rand() % maxInventory);
	}
	for (int i = 0; i < sizeof(changeList); i++){
		change.item.push_back(std::to_string(changeList[i]));
		change.inInventory.push_back((rand() % 90) + 10);
	}
}

std::string VendingMachine::getItem(int item) const{
	return this->itemList.item[item];
}

int VendingMachine::getInInventory(int item) const{
	return this->itemList.inInventory[item];
}

double VendingMachine::getCost(int item) const{
	return this->itemList.cost[item];
}

double VendingMachine::getCurrentCredit() const{
	return this->currentCredit;
}

bool VendingMachine::sufficientCreditCheck(int item) const{
	if (this->currentCredit > this->itemList.cost[item]){ return true; }
	else{ return false; }
}

int VendingMachine::getItemSlots() const{
	return this->itemSlots;
}

void VendingMachine::insertMoney(double insertedAmount){
	this->currentCredit += insertedAmount;
}

bool VendingMachine::dispenseItem(int item){
	if (itemList.inInventory[item] > 0){
		this->itemList.inInventory[item] -= 1;
		return true;
	} else{ return false; }
}

