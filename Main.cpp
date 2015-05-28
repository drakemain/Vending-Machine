#pragma once
#include "VendingMachine.h"
#include <iostream>
#include <vector>

int main(){
	VendingMachine sodaMachine;

	std::vector<std::string> snackList = { "Potato Chips", "Cheesey Poofs", "Uberitos" };
	VendingMachine snackMachine(snackList);

	for (int i = 0; i < sodaMachine.getItemSlots(); i++){
		std::cout << sodaMachine.getItem(i) << ": " << sodaMachine.getInInventory(i) << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < snackMachine.getItemSlots(); i++){
		std::cout << snackMachine.getItem(i) << ": " << snackMachine.getInInventory(i) << std::endl;
	}

	return 0;
}
