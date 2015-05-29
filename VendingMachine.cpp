#pragma once
#include "VendingMachine.h"
#include <ctime>

VendingMachine::VendingMachine(){
	this->name = "Soda Machine";
	this->currentCredit = 0.0;
	
	std::vector<std::string> sodas = { "Cola", "Cherry Cola", "Diet Cola", "Root Beer", "Lemon Lime", "Orange", "Grape", "Cherry", "RoidRage Energy", "Water" };
	double changeList[4] = { .01, .05, .1, .25 };
	
	this->itemSlots = sodas.size();
	
	randomInventoryGenerator(changeList, sodas);
}

VendingMachine::VendingMachine(std::vector<std::string> customList, std::string newName){
	this->name = newName;
	this->itemSlots = customList.size();
	this->currentCredit = 0.0;

	double changeList[4] = { .01, .05, .1, .25 };

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

int VendingMachine::getItemSlots() const{
	return this->itemSlots;
}

std::string VendingMachine::getName() const{
	return this->name;
}

void VendingMachine::insertMoney(double insertedAmount){
	this->currentCredit += insertedAmount;
}

bool VendingMachine::dispenseItem(int item){
	if (this->itemList.inInventory[item] > 0 && this->sufficientCreditCheck(item)){
		this->itemList.inInventory[item] -= 1;
		return true;
	} else{ return false; }
}

double VendingMachine::ejectChange(double changeToEject){
	this->currentCredit = 0.00;
	return changeToEject;
}

double VendingMachine::ejectChange(){
	double changeToDispense = this->currentCredit;
	this->currentCredit = 0.00;
	return changeToDispense;
}

bool VendingMachine::sufficientCreditCheck(int item) const{
	if (this->currentCredit >= this->itemList.cost[item]){ return true; }
	else{ return false; }
}