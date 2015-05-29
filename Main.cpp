#pragma once
#include "VendingMachine.h"
#include <iostream>
#include <vector>
#include <typeinfo>

void display(VendingMachine &machine);																//displays the contents of a machine
void pay(VendingMachine &machine, std::vector<double> currencyList = { .01, .05, .10, .25, 1.00 }); //allows the user to insert credit into a specific machine
void pause();																						//Waits for user to press enter before continuing
int validInput(int maxValue, int minValue = 1);														//forces int inputs
bool inputIsValid(int);																				//checks input for validInput() error flag
std::string formatMoney(double);																	//formats double/float to currency string (ex: $1.25)
bool commenceVending(std::vector<VendingMachine*> VendingMachingList);								//initializes ultra-realistic vending machine simulation

int main(){
	std::vector<std::string> snackList = { "Potato Chips", "Cheesey Poofs", "Uberitos", "Bubba Gum", "Chocolate Bar", "Twinks" }; //a custom list for VendingMachine constructor
	VendingMachine snackMachine(snackList, "Snack Machine");																	  //custom machine
	VendingMachine sodaMachine;																									  //default (soda) machine

	std::vector<VendingMachine*> VendingMachineList = { &snackMachine, &sodaMachine };											  //a vector containing VendingMachine object pointers

	system("CLS");

	bool vending = true;
	while (vending){
		vending = commenceVending(VendingMachineList);
	}

	return 0;
}

void display(VendingMachine &machine){
	for (int i = 0; i < machine.getItemSlots(); i++){
		std::cout << i+1 << ". "<< machine.getItem(i) << ": " << formatMoney(machine.getCost(i)) << ", " << machine.getInInventory(i) << " in stock" << std::endl;
	}
}

void pay(VendingMachine &machine, std::vector<double> currencyList){
	bool paying = true;

	while (paying){
		for (unsigned int i = 0; i < currencyList.size(); i++){
			std::cout << i + 1 << ". " << currencyList[i] << std::endl;
		}

		int selection = validInput(9);
		if (inputIsValid(selection)){
			if (selection == 9){ paying = false; }
			else { machine.insertMoney(currencyList[selection]); }
		}
	}
}

void pause(){
	std::cout << "Press enter to continue..." << std::flush;
	std::cin.get();
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

std::string formatMoney(double amount){
	std::string stringAmount = std::to_string(amount);
	stringAmount = stringAmount.substr(0, stringAmount.find('.') + 3);
	return ("$" + stringAmount);
}

int validInput(int maxValue, int minValue){
	try {
		int selection;
		std::cout << ": " << std::flush;
		if (!(std::cin >> selection)){
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			throw 1;
		}
		else if (selection < minValue || selection > maxValue || selection < -99){
			throw 2;
		}
		else {
			return selection;
		}
	}
	catch (int er){
		switch (er){
		case 1:
			std::cout << "Bad selection. Must input a number." << std::endl;
			break;
		case 2:
			std::cout << "Selection does not exist!" << std::endl;
			break;
		}
		return -100;
		pause();
	}
}

bool inputIsValid(int valueToCheck){
	if (valueToCheck > -100){ return true; }
	else{ return false; }
}

bool commenceVending(std::vector<VendingMachine*> VendingMachineList){
	system("CLS");
	int selection;

	std::cout << "What would you like to do?\n" << std::endl;
	for (unsigned int i = 0; i < VendingMachineList.size(); i++){
		VendingMachine &machine = *VendingMachineList[i];
		std::cout << i + 1 << ". Examine: " << machine.getName() << std::endl;
	}
	selection = validInput(2);
	if (inputIsValid(selection)){
		selection -= 1;
		VendingMachine &machine = *VendingMachineList[selection];
		display(machine);
	} else{ pause(); }

	return true;
}
