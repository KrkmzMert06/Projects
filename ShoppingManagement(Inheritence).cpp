#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Base {
    string name;
    int quantity;
    double price;
public:
    Base() : name(""), quantity(0), price(0.0) {}
    Base(string name, int qntty, double price) : name(name), quantity(qntty), price(price) {}
    virtual ~Base() {}
    string getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }
    void setName(string name) { this->name = name; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(double price) { this->price = price; }
    virtual double calculateCost() { return quantity * price; }
    virtual void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price: " << price << endl;
        cout << "Total cost: " << calculateCost() << endl;
    }
};

class Food : public Base {
public:
    virtual void displayDetails() override {
        cout << "Food: " << getName() << endl;
        cout << "Quantity: " << getQuantity() << endl;
        cout << "Price per Unit: " << getPrice() << endl;
        cout << "Total cost: " << calculateCost() << endl;
    }
};

class Electronics : public Base {
    string brand;
public:
    Electronics() : Base(), brand("") {}
    Electronics(string name, int quantity, double price, string brand) : Base(name, quantity, price), brand(brand) {}
    ~Electronics() {}
    string getBrand() { return brand; }
    void setBrand(string brand) { this->brand = brand; }
    virtual void displayDetails() override {
        cout << "Electronics: " << getName() << " (" << brand << ")" << endl;
        cout << "Quantity: " << getQuantity() << endl;
        cout << "Price per Unit: " << getPrice() << endl;
        cout << "Total cost: " << calculateCost() << endl;
    }
};

class Clothing : public Base {
    int size;
public:
    Clothing() : Base(), size(0) {}
    Clothing(string name, int quantity, double price, int size) : Base(name, quantity, price), size(size) {}
    int getSize() { return size; }
    void setSize(int size) { this->size = size; }
    virtual void displayDetails() override {
        cout << "Clothing: " << getName() << " (Size: " << size << ")" << endl;
        cout << "Quantity: " << getQuantity() << endl;
        cout << "Price: " << getPrice() << endl;
        cout << "Total cost: " << calculateCost() << endl;
    }
};

class ShoppingList {
    vector<Food> foods;
    vector<Electronics> electronics;
    vector<Clothing> clothings;
public:
    void addItem(Food& newProduct) { foods.push_back(newProduct); }
    void addItem(Electronics& newProduct) { electronics.push_back(newProduct); }
    void addItem(Clothing& newProduct) { clothings.push_back(newProduct); }

    void removeItem(string& name) {
        for (int i = 0; i < foods.size(); i++) {
            if (name == foods[i].getName()) {
                foods.erase(foods.begin() + i);
                break;
            }
        }
        for (int i = 0; i < electronics.size(); i++) {
            if (name == electronics[i].getName()) {
                electronics.erase(electronics.begin() + i);
                break;
            }
        }
        for (int i = 0; i < clothings.size(); i++) {
            if (name == clothings[i].getName()) {
                clothings.erase(clothings.begin() + i);
                break;
            }
        }
    }

    void displayAll() {
        cout << "Foods:" << endl;
        for (auto& food : foods) food.displayDetails();
        cout << "Electronics:" << endl;
        for (auto& elec : electronics) elec.displayDetails();
        cout << "Clothings:" << endl;
        for (auto& cloth : clothings) cloth.displayDetails();
    }

    void computeAllCategories() {
        double totalFoods = 0.0, totalElectronics = 0.0, totalClothings = 0.0;
        for (auto& food : foods) totalFoods += food.calculateCost();
        for (auto& elec : electronics) totalElectronics += elec.calculateCost();
        for (auto& cloth : clothings) totalClothings += cloth.calculateCost();

        cout << "Total cost of Foods: " << totalFoods << endl;
        cout << "Total cost of Electronics: " << totalElectronics << endl;
        cout << "Total cost of Clothings: " << totalClothings << endl;
    }

    void clearList() {
        foods.clear();
        electronics.clear();
        clothings.clear();
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file for saving.\n";
            return;
        }
        for (auto& food : foods)
            file << "Food," << food.getName() << "," << food.getQuantity() << "," << food.getPrice() << endl;
        for (auto& elec : electronics)
            file << "Electronics," << elec.getName() << "," << elec.getQuantity() << "," << elec.getPrice() << "," << elec.getBrand() << endl;
        for (auto& cloth : clothings)
            file << "Clothing," << cloth.getName() << "," << cloth.getQuantity() << "," << cloth.getPrice() << "," << cloth.getSize() << endl;
        file.close();
        cout << "Shopping list saved to " << filename << ".\n";
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "No existing shopping list found. Starting fresh.\n";
            return;
        }

        string type, name, brandOrSize;
        int quantity, size;
        double price;

        while (file.good()) {
            getline(file, type, ',');
            if (type.empty()) break;
            getline(file, name, ',');
            file >> quantity;
            file.ignore(1, ',');
            file >> price;
            file.ignore(1, ',');

            if (type == "Food") {
                foods.push_back(Food(name, quantity, price));
            }
            else if (type == "Electronics") {
                getline(file, brandOrSize);
                electronics.push_back(Electronics(name, quantity, price, brandOrSize));
            }
            else if (type == "Clothing") {
                size = stoi(brandOrSize);
                clothings.push_back(Clothing(name, quantity, price, size));
            }
        }
        file.close();
    }
};

void printMenü() {
    cout << "1- Add items to the shopping list." << endl;
    cout << "2- View the shopping list." << endl;
    cout << "3- Clear the shopping list." << endl;
    cout << "4- Save the shopping list to a file." << endl;
    cout << "5- Exit the program." << endl;
}

int main() {
    ShoppingList mylist;
    mylist.loadFromFile("shoppinglist.txt");

    int option;
    do {
        printMenü();
        cin >> option;

        switch (option) {
        case 1:
            int pick;
            string name;
            int qntty;
            double price;
            cout << "Please pick the list you want to add" << endl;
            cout << "1-Foods  2-Electronics  3-Clothings" << endl;
            cin >> pick;
            if (pick == 1) {
                cout << "Enter the informations (Name of food, Quantity, price)" << endl;
                cin >> name >> qntty >> price;
                Food newFood(name, qntty, price);
                mylist.addItem(newFood);
            }
            else if (pick == 2) {
                cout << "Enter the informations (Name, Quantity, price, brand)" << endl;
                cin >> name >> qntty >> price;
                string brand;
                cin >> brand;
                Electronics newElec(name, qntty, price, brand);
                mylist.addItem(newElec);
            }
            else if (pick == 3) {
                cout << "Enter the informations (Name, Quantity, price, size)" << endl;
                cin >> name >> qntty >> price;
                int size;
                cin >> size;
                Clothing newCloth(name, qntty, price, size);
                mylist.addItem(newCloth);
            }
            break;

        case 2:
            mylist.displayAll();
            break;

        case 3:
            mylist.clearList();
            break;

        case 4:
            mylist.saveToFile("shoppinglist.txt");
            break;

        case 5:
            break;
        }
    } while (option != 5);

    return 0;
}
