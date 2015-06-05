#pragma once
#include "VendingMachine.h"
#include <iostream>
#include <vector>
#include <typeinfo>

void display(VendingMachine &machine);                                                                //displays the contents of a machine
void pay(VendingMachine &machine, std::vector<double> currencyList = { .01, .05, .10, .25, 1.00 }); //allows the user to insert credit into a specific machine
void pause();                                                                                        //Waits for user to press enter before continuing
int validInput(int maxValue, int minValue = 1);                                                        //forces int inputs and informs user of bad input
bool inputIsValid(int);                                                                                //checks input for validInput() error flag
std::string formatMoney(double);                                                                    //formats double/float to currency string (ex: $1.25)
bool commenceVending(std::vector<VendingMachine*> VendingMachingList);                                //initializes ultra-realistic vending machine simulation


int main(){
    std::vector<std::string> snackList = { "Potato Chips", "Cheesey Poofs", "Uberitos", "Bubba Gum", "Chocolate Bar", "Twinks" }; //a custom item list for VendingMachine constructor
    std::vector<double> costList = { 1.25, 1.25, 1.25, .75, 1.00, 1.00 };                                                          //a custom cost list for VendingMachine costructor
    VendingMachine snackMachine(snackList, costList, "Snack Machine");                                                                      //custom machine
    VendingMachine sodaMachine;                                                                                                      //default (soda) machine

    std::vector<VendingMachine*> VendingMachineList = { &snackMachine, &sodaMachine };                                              //a vector containing VendingMachine object pointers

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
        system("CLS");
        std::cout << "The machine has a current credit of " << formatMoney(machine.getCurrentCredit()) << std::endl << std::endl;
        for (unsigned int i = 0; i < currencyList.size(); i++){
            std::cout << i + 1 << ". " << formatMoney(currencyList[i]) << std::endl;
        }
        
        std::cout << "\nInsert amount or\n"<< currencyList.size() + 1 << ". Go back" << std::endl;

        int selection = validInput(currencyList.size()+1);
        if (inputIsValid(selection)){
            if (selection == currencyList.size() + 1){ paying = false; }
            else { machine.insertMoney(currencyList[selection - 1]); }
        }
    }
}

void pause(){
    std::cout << "Press enter to continue..." << std::flush;
    std::cin.sync();
    std::cin.ignore(INT_MAX, '\n');
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
        pause();
        return -100;
    }
}

bool inputIsValid(int valueToCheck){
    if (valueToCheck > -100){ return true; }
    else{ return false; }
}

bool commenceVending(std::vector<VendingMachine*> VendingMachineList){
    system("CLS");
    int selection;

    std::cout << "You come across some vending machines. What would you like to do?\n" << std::endl;
    for (unsigned int i = 0; i < VendingMachineList.size(); i++){
        VendingMachine &machine = *VendingMachineList[i];
        std::cout << i + 1 << ". " << machine.getName() << std::endl;
    }
    std::cout << "\nExamine a machine or\n" << VendingMachineList.size() + 1 << ". Go on with your day." << std::endl;
    
    selection = validInput(VendingMachineList.size() + 1);//prompt user for input
    if (inputIsValid(selection)){
        if (selection == VendingMachineList.size() + 1){//user selects exit
            return false;
        }

        selection -= 1;
        VendingMachine &machine = *VendingMachineList[selection];

        int items = machine.getItemSlots();
        bool examiningMachine = true;
        while (examiningMachine){

            system("CLS");
            std::cout << "The contents of the machine are: \n" << std::endl;
            
            display(machine);

            std::cout << "\nCurrent credit: " << formatMoney(machine.getCurrentCredit()) << '\n' << std::endl;

            std::cout << "Select an item to purchase or \n" << items + 1 << ". Insert money\n" << items + 2 << ". Eject change\n" << items + 3 << ". Go back" << std::endl;
            selection = validInput(items + 3);//prompt user to make selection
            system("CLS");
            if (inputIsValid(selection)){

                if (selection == items + 3){//user selects go back
                    examiningMachine = false;
                }

                else if (selection > 0 && selection <= items){//user selects item to purchase
                    selection--;
                    std::cout << "You push the button corresponding to " << machine.getItem(selection) << '.' << std::endl;
                    if (machine.dispenseItem(selection)){
                        std::cout << "The machine dispenses " << machine.getItem(selection) << '.' << std::endl;
                        if (machine.getCurrentCredit() > 0){
                            std::cout << formatMoney(machine.ejectChange()) << " in coins drop into the change port." << std::endl;
                        }
                    }
                    else{
                        std::cout << "You can't purchase that." << std::endl;
                    }
                    pause();
                }

                else if (selection == items + 1){//user selects insert money
                    pay(machine);
                }
                else if (selection == items + 2){//user selects eject change
                    std::cout << "You push the eject change button.\n" << formatMoney(machine.ejectChange()) << " in coins drops into the change port." << std::endl;
                    pause();
                }//user selection logic
            }//valid input check
        }//while loop
    }//vending machine selection valid input check

    return true;
}
