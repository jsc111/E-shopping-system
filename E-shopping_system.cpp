  #include <iostream>
#include <string>
#include <vector>
using namespace std;
class Inventory {
protected:
 string itemName;
 double itemPrice;
 int itemQuantity;
public:
 Inventory(string name, double price, int quantity)
 : itemName(name), itemPrice(price), itemQuantity(quantity) {}
 virtual ~Inventory() {}
 string getName() const { return itemName; }
 double getPrice() const { return itemPrice; }
 int getQuantity() const { return itemQuantity; }
 virtual void printItem() const {
 cout << itemName << " (Rs. " << itemPrice << " each)" << endl;
 }
};
class Shop : public Inventory {
public:
 Shop(string name, double price, int quantity)
 : Inventory(name, price, quantity) {}
};
class Bill : public Shop {
private:
 int purchasedQuantity;
 double totalCost;
public:
 Bill(string name, double price, int quantity)
 : Shop(name, price, quantity), purchasedQuantity(0), totalCost(0) {}
 void purchase(int quantity) {
 purchasedQuantity = quantity;
 totalCost = purchasedQuantity * itemPrice;
 itemQuantity -= purchasedQuantity;
 }
 double getTotal() const { return totalCost; }
 int getQuantity() const { return purchasedQuantity; }
 void printBill() const {
 if (purchasedQuantity > 0) {
 cout << itemName << " (" << purchasedQuantity << " @ Rs. " << itemPrice
 << " each): Rs. " << totalCost << endl;
 }
 }
};
int main() {
 // initialize inventory
 vector<Inventory *> inventory;
 inventory.push_back(
 new Inventory("Apple iPhone 14 pro max ultra giga", 150000, 0));
 inventory.push_back(new Inventory("MIT admission Btech", 325000, 0));
 inventory.push_back(new Inventory("Boat Earphones", 3000, 0));
 inventory.push_back(new Inventory("Drake concert tickets", 2.50, 0));
 inventory.push_back(new Inventory("Milk", 30.00, 0));
 // display inventory
 cout << "Welcome to our shop!" << endl << endl;
 cout << "We have the following items in stock:" << endl;
 for (int i = 0; i < inventory.size(); i++) {
 inventory[i]->printItem();
 }
 // get user purchases
 vector<Bill *> bills;
 string item;
 while (true) {
 cout << endl
 << "Please enter the items you would like to purchase and their "
 "quantities."
 << endl;
 cout << "Type 'done' when you are finished." << endl << endl;
 cout << "Enter item name: ";
 getline(cin, item);
 if (item == "done") {
 break;
 }
 bool found = false;
 for (int i = 0; i < inventory.size(); i++) {
 if (inventory[i]->getName() == item) {
 found = true;
 double price = inventory[i]->getPrice();
 int quantity = inventory[i]->getQuantity();
 bills.push_back(new Bill(item, price, quantity));
 cout << "Enter quantity: ";
 int qty;
 cin >> qty;
 cin.ignore();
 bills.back()->purchase(qty);
 break;
 }
 }
 if (!found) {
 cout << item << " not found in shop" << endl;
 }
 }
 cout << "************************************************************"
 << endl;
 cout << " BILL "
 << endl;
 cout << "************************************************************"
 << endl;
 // print bills
 double subtotal = 0;
 for (int i = 0; i < bills.size(); i++) {
 bills[i]->printBill();
 subtotal += bills[i]->getTotal();
 }
 // calculate total with tax
 double tax = subtotal * 0.05;
 double total = subtotal + tax;
 // display total
 cout << endl << "Subtotal: Rs. " << subtotal << endl;
 cout << "Tax (5%): Rs. " << tax << endl;
 cout << "Total: Rs. " << total << endl;
 cout << "************************************************************"
 << endl;
 cout << "\nSelect Payment Method:" << endl;
 cout << "1. Cash" << endl;
 cout << "2. Card" << endl;
 cout << "3. UPI" << endl;
 int option;
 cin >> option;
 switch (option) {
 case 1:
 cout << "\nPayment by Cash." << endl;
 break;
 case 2:
 cout << "\nPayment by Card." << endl;
 break;
 case 3:
 cout << "\nPayment by UPI. Pay to ID : rachitpatekar777@okaxis ";
 break;
default:
 cout << "\nInvalid option. Payment Failed." << endl;
 break;
 // cleanup
 for (int i = 0; i < inventory.size(); i++) {
 delete inventory[i];
 }
 for (int i = 0; i < bills.size(); i++) {
 delete bills[i];
 }
 return 0;
 }
}
