#pragma once
#include "VendingMachine.h"
#include <iostream>
#include <vector>
#include <typeinfo>

int main(){
	VendingMachine sodaMachine;

	int selection;

	std::vector<std::string> snackList = { "Potato Chips", "Cheesey Poofs", "Uberitos" };
	VendingMachine snackMachine(snackList);

	system("CLS");

	std::cout << "Select Machine:\n1: Soda Machine\n2: Snack Machine" << std::flush;
	

	try {
		std::cin >> selection;
		if (typeid(selection).name() != typeid(1).name()){
			throw 1;
		}
		else if (selection < 1 || selection > 2){
			throw 2;
		}
		else {
			switch (selection){
				case 1:
					break;
				case 2:
					s
			}
		}
	}
	catch (int er){
		switch (er){
			case 1:
				std::cout << "Bad selection. Must input a number." << std::endl;
				break;
			case 2:
				std::cout << "Selection does not exist!" << std::endl;
		}
		system("PAUSE");
	}
	


	return 0;
}
