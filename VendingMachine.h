#include <vector>
#include <string>

class VendingMachine{

public:
	VendingMachine();
	VendingMachine(std::vector<std::string> customList, std::string customName);
	~VendingMachine();

	std::string getItem(int listElementIndex) const;		//returns name of item
	int getInInventory(int listElementIndex) const;			//returns count of specific item
	double getCost(int listElementIndex) const;				//returns cost of specific item
	double getCurrentCredit() const;						//returns amount of credit user has input to the machine
	
	int getItemSlots() const;								//determines how many different items machine has capacity for
	std::string getName() const;							//returns the name of the machine
	
	void insertMoney(double insertedAmount);				//allows user to input credit
	bool dispenseItem(int listElementIndex);				//reduces inventory count of item by 1
	double ejectChange();									//returns remaining credit and sets to 0


private:
	struct inventoryStruct{
		std::vector<std::string> item;
		std::vector<double> cost;
		std::vector<int> inInventory;
	};

	std::string name;
	int itemSlots;
	double currentCredit;
	inventoryStruct itemList;
	inventoryStruct change;

	void randomInventoryGenerator(double changeList[], std::vector<std::string> listOfSodas, int maxInventory = 11);
	bool sufficientCreditCheck(int listElementIndex) const;	//checks if the user has sufficient credit to purchase item
};