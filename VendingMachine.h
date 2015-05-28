#include <vector>
#include <string>

class VendingMachine{

public:
	VendingMachine();
	VendingMachine(std::vector<std::string> customList);
	~VendingMachine();

	std::string getItem(int listElementIndex) const;
	int getInInventory(int listElementIndex) const;
	double getCurrentCredit() const;
	int getItemSlots() const;
	void insertMoney(double insertedAmount);
	void dispenseItem(int listElementIndex);
	double ejectChange(double amountToEject);

private:
	struct inventoryStruct{
		std::vector<std::string> item;
		std::vector<int> inInventory;
	};

	int itemSlots;
	double currentCredit;
	inventoryStruct itemList;
	inventoryStruct change;

	void randomInventoryGenerator(double changeList[], std::vector<std::string> listOfSodas, int maxInventory = 11);
	
	
};