#pragma once
#include "VendingMachine.h"
#include <ctime>
#include <iostream>

int main(){
	VendingMachine sodaMachine;

	for (int i = 0; i < 10; i++){
		std::cout << sodaMachine.getSoda(i) << ": " << sodaMachine.getInInventory(i) << std::endl;
	}

	return 0;
}
