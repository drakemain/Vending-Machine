#pragma once
#include "VendingMachine.h"
#include <ctime>
#include <iostream>

VendingMachine::VendingMachine(){
	std::string sodas[10] = { "Cola", "Cherry Cola", "Diet Cola", "Root Beer", "Lemon Lime", "Orange", "Grape", "Cherry", "Roid Energy", "Water" };
	double changeList[4] = { .01, .05, .1, .25 };
	sodaSlots = 10;
	currentCredit = 0.0;
	randomInventoryGenerator(changeList, sodas);
	int i = 0;
}

VendingMachine::~VendingMachine(){}

void VendingMachine::randomInventoryGenerator(double changeList[], std::string sodas[], int maxInventory){
	srand(time(0));
	for (int i = 0; i < sodaSlots; i++){
		sodaList.item.push_back(sodas[i]);
		sodaList.inInventory.push_back(rand() % maxInventory);
		if (i < sizeof(changeList)){
			change.item.push_back(std::to_string(changeList[i]));
			change.inInventory.push_back( ( rand() % 90 ) + 10 );
		}
	}
}

std::string VendingMachine::getSoda(int soda){
	return this->sodaList.item[soda];
}

int VendingMachine::getInInventory(int soda){
	return this->sodaList.inInventory[soda];
}

double VendingMachine::getCurrentCredit(){
	return this->currentCredit;
}

void VendingMachine::insertMoney(double insertedAmount){
	this->currentCredit += insertedAmount;
}