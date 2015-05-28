#include <vector>
#include <string>

class VendingMachine{

public:
	VendingMachine();
	~VendingMachine();

	std::string getSoda(int listElement);
	int getInInventory(int listElement);
	double getCurrentCredit();
	void insertMoney(double insertedAmount);

private:
	struct inventoryStruct{
		std::vector<std::string> item;
		std::vector<int> inInventory;
	};

	int sodaSlots;
	double currentCredit;
	inventoryStruct sodaList;
	inventoryStruct change;
	void randomInventoryGenerator(double changeList[], std::string listOfSodas[], int maxInventory = 11);
	
	
};