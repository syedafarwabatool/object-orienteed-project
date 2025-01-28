#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
// Custom to_string function
template <typename T>
string to_string_custom(T value) {
ostringstream oss;
oss << value;
return oss.str();
}
class SkincareProduct {
private:
string name;
double price;
int quantity;
public:
SkincareProduct() : name(""), price(0.0), quantity(0) {}
SkincareProduct(const string& name, double price, int quantity)
: name(name), price(price), quantity(quantity) {}
string getName() const { return name; }
double getPrice() const { return price; }
int getQuantity() const { return quantity; }
void decreaseQuantity() {
if (quantity > 0) {
quantity--;
}
}
};
class CartItem {
private:
SkincareProduct product;
int quantity;
public:
CartItem() : quantity(0) {}
CartItem(const SkincareProduct& product, int quantity = 1)
: product(product), quantity(quantity) {}
SkincareProduct getProduct() const { return product; }
int getQuantity() const { return quantity; }
void increaseQuantity() { quantity++; }
};
class SkincareStore {
private:
SkincareProduct products[10];
CartItem cart[22];
int cartSize;
public:
SkincareStore() : cartSize(0) {
// Add some sample products
products[0] = SkincareProduct("Cleanser", 1500, 40);
products[1] = SkincareProduct("Moisturizer", 1500, 30);
products[2] = SkincareProduct("Face wash", 1000, 20);
products[3] = SkincareProduct("Sunscreen", 1200, 40);
products[4] = SkincareProduct("Lip balm", 600, 19);
products[5] = SkincareProduct("Vitamin C serum", 1600, 20);
products[6] = SkincareProduct("Vitamin B-3 serum", 1600, 20);
products[7] = SkincareProduct("Lip oil", 400, 20);
}
void displayMenu() const {
cout << "Skincare Product Menu:\n";
cout << "======================\n";
cout << endl;
for (int i = 0; i < 8; ++i) {
cout << i + 1 << ". " << products[i].getName() << " - Rs" << products[i].getPrice()
<< " (Quantity: " << products[i].getQuantity() << ")" << endl;
}
cout << endl;
cout << "======================\n";
}
void addToCart(int choice) {
if (choice > 0 && choice <= 8) {
SkincareProduct selectedProduct = products[choice - 1];
if (selectedProduct.getQuantity() > 0) {
bool found = false;
for (int i = 0; i < cartSize; ++i) {
if (cart[i].getProduct().getName() == selectedProduct.getName()) {
cart[i].increaseQuantity();
found = true;
break;
}
}
if (!found) {
cart[cartSize++] = CartItem(selectedProduct);
}
products[choice - 1].decreaseQuantity(); // update the quantity in the products array
cout << "Added to cart: " << selectedProduct.getName() << endl;
}
else {
cout << "Sorry, the selected product is out of stock." << endl;
}
}
else {
cout << "Invalid choice. Please try again." << endl;
displayMenu();
int newChoice;
cout << "Please enter again: ";
cin >> newChoice;
addToCart(newChoice);
}
}
void displayCart() const {
cout << "Cart:\n";
cout << "======================\n";
for (int i = 0; i < cartSize; ++i) {
CartItem cartItem = cart[i];
SkincareProduct product = cartItem.getProduct();
cout << product.getName() << " - Rs" << product.getPrice() << " (Quantity: " <<
cartItem.getQuantity() << ")" << endl;
}
cout << "======================\n";
}
double calculateTotalBill() const {
double total = 0.0;
for (int i = 0; i < cartSize; ++i) {
CartItem cartItem = cart[i];
SkincareProduct product = cartItem.getProduct();
total += product.getPrice() * cartItem.getQuantity();
}
return total;
}
};
class Customer {
private:
string name;
string address;
string contact;
public:
Customer(const string& name, const string& address, const string& contact)
: name(name), address(address), contact(contact) {}
string getName() const { return name; }
string getAddress() const { return address; }
string getContact() const { return contact; }
// Virtual function for polymorphism
virtual string getDetails() const {
return "Name: " + name + "\nAddress: " + address + "\nContact: " + contact;
}
};
class Order : public Customer {
private:
double totalBill;
public:
Order(const Customer& customer, double totalBill)
: Customer(customer), totalBill(totalBill) {}
double getTotalBill() const { return totalBill; }
// Override the virtual function
string getDetails() const override {
return Customer::getDetails() + "\nTotal Bill: Rs" + to_string_custom(totalBill);
}
void saveToFile() const {
ofstream file;
file.open("order.txt", ios::app);
if (file.is_open()) {
file << getDetails() << endl;
file.close();
}
else {
cout << "Unable to open file." << endl;
}
}
void showAllOrders() const {
ifstream file("order.txt");
if (file.is_open()) {
string line;
while (getline(file, line)) {
cout << line << endl;
}
file.close();
}
else {
cout << "Unable to open file." << endl;
}
}
};
int main() {
SkincareStore store;
int choice;
char continueShopping;
cout << "\t" << "\t" << "\t" << "\t" << "\t" << "***********" << endl;
cout << "\t" << "\t" << "\t" << "\t" << "\t" << " Welcome to the FM skinStore!\n";
cout << "\t" << "\t" << "\t" << "\t" << "\t" << "***********" << endl;
cout << endl;
do {
// system("cls"); // Use this line if you are on Windows to clear the screen
store.displayMenu();
cout << endl;
cout << "Enter your choice: ";
cin >> choice;
store.addToCart(choice);
cout << "Do you want to continue shopping? (y/n): ";
cin >> continueShopping;
} while (continueShopping == 'y' || continueShopping == 'Y');
store.displayCart();
// Get customer information
string name, address, contact;
cout << "Enter your name: ";
cin.ignore();
getline(cin, name);
cout << "Enter your address: ";
getline(cin, address);
cout << "Enter your contact number: ";
getline(cin, contact);
Customer customer(name, address, contact);
double totalBill = store.calculateTotalBill();
Order order(customer, totalBill);
cout << "----------------------\n";
cout << order.getDetails() << endl; // Using polymorphism here
order.saveToFile();
// Show all orders
cout << "\nAll Orders:\n";
order.showAllOrders();
return 0;
}
