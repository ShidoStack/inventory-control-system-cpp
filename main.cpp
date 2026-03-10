#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

class Product
{
private:
    string name;
    int quantity;
    const int MIN_STOCK = 10;

public:
    Product(string n = "", int q = 0) : name(n), quantity(q) {}

    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    bool isLowStock() const { return quantity <= MIN_STOCK; }

    void addStock(int amount)
    {
        if (amount > 0)
            quantity += amount;
    }

    bool sellStock(int amount)
    {
        if (amount > 0 && amount <= quantity)
        {
            quantity -= amount;
            return true;
        }
        return false;
    }

    void display() const
    {
        cout << left << setw(20) << name << setw(10) << quantity;
        if (isLowStock())
            cout << " *** LOW STOCK ***";
        cout << endl;
    }
};

class Transaction
{
private:
    string productName;
    string type;
    int quantity;
    string timestamp;

public:
    Transaction(string name, string t, int q) : productName(name), type(t), quantity(q)
    {
        timestamp = "2026-03-10";
    }

    string getProductName() const { return productName; }
    string getType() const { return type; }
    int getQuantity() const { return quantity; }

    void display() const
    {
        cout << left << setw(20) << productName
             << setw(10) << type
             << setw(10) << quantity << endl;
    }
};

class InventoryManager
{
private:
    vector<Product> products;
    vector<Transaction> transactions;
    const string DATA_FILE = "inventory.txt";
    const string TRANS_FILE = "transactions.txt";

public:
    void loadInventory()
    {
        ifstream file(DATA_FILE);
        if (!file.is_open())
            return;

        string name;
        int qty;
        while (file >> name >> qty)
        {
            products.emplace_back(name, qty);
        }
        file.close();
        cout << "Inventory loaded from file." << endl;
    }

    void saveInventory()
    {
        ofstream file(DATA_FILE);
        for (const auto &p : products)
        {
            file << p.getName() << " " << p.getQuantity() << endl;
        }
        file.close();
    }

    void saveTransactions()
    {
        ofstream file(TRANS_FILE);
        for (const auto &t : transactions)
        {
            file << t.getProductName() << " " << t.getType() << " "
                 << t.getQuantity() << endl;
        }
        file.close();
    }

    void addProduct()
    {
        string name;
        int qty;
        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> qty;

        products.emplace_back(name, qty);
        transactions.emplace_back(name, "PURCHASE", qty);
        saveInventory();
        cout << "Product added successfully!" << endl;
    }

    void addStock()
    {
        string name;
        int qty;
        cout << "Enter Product Name: ";
        getline(cin, name);

        auto it = findProduct(name);
        if (it != products.end())
        {
            cout << "Current Quantity: " << it->getQuantity() << endl;
            cout << "Enter Quantity to Add: ";
            cin >> qty;

            it->addStock(qty);
            transactions.emplace_back(name, "PURCHASE", qty);
            saveInventory();
            cout << "Stock Updated Successfully!" << endl;
            cout << "Current Quantity: " << it->getQuantity() << endl;
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }

    void sellStock()
    {
        string name;
        int qty;
        cout << "Enter Product Name: ";
        getline(cin, name);

        auto it = findProduct(name);
        if (it != products.end())
        {
            cout << "Current Quantity: " << it->getQuantity() << endl;
            cout << "Enter Quantity to Sell: ";
            cin >> qty;

            if (it->sellStock(qty))
            {
                transactions.emplace_back(name, "SALE", qty);
                saveInventory();
                cout << "Sale completed successfully!" << endl;
                cout << "Remaining Quantity: " << it->getQuantity() << endl;
            }
            else
            {
                cout << "Error: Insufficient stock!" << endl;
            }
        }
        else
        {
            cout << "Product not found!" << endl;
        }
    }

    void displayInventory()
    {
        if (products.empty())
        {
            cout << "No products in inventory." << endl;
            return;
        }

        cout << "\n=== CURRENT INVENTORY ===" << endl;
        cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << endl;
        cout << string(35, '=') << endl;

        for (const auto &p : products)
        {
            p.display();
        }

        cout << "\nTotal Products: " << products.size() << endl;
        int lowStockCount = countLowStock();
        if (lowStockCount > 0)
        {
            cout << lowStockCount << " products need restocking!" << endl;
        }
    }

    void generateReport()
    {
        cout << "\n=== INVENTORY REPORT ===" << endl;
        displayInventory();

        cout << "\n=== RECENT TRANSACTIONS ===" << endl;
        if (transactions.empty())
        {
            cout << "No transactions recorded." << endl;
        }
        else
        {
            cout << left << setw(20) << "Product" << setw(10) << "Type" << setw(10) << "Quantity" << endl;
            cout << string(45, '=') << endl;
            for (const auto &t : transactions)
            {
                t.display();
            }
        }
    }

private:
    vector<Product>::iterator findProduct(const string &name)
    {
        return find_if(products.begin(), products.end(),
                       [&](const Product &p)
                       { return p.getName() == name; });
    }

    int countLowStock()
    {
        return count_if(products.begin(), products.end(),
                        [](const Product &p)
                        { return p.isLowStock(); });
    }
};

int main()
{

    cout << ".      OUTPUT : " << endl;
    cout << "__________________________________________________________________________________________________" << endl;
    cout << endl
         << endl;

    InventoryManager manager;
    manager.loadInventory();

    cout << "=== INVENTORY CONTROL SYSTEM ===" << endl;
    cout << "Welcome! Data will be saved automatically." << endl;

    int choice;
    do
    {
        cout << "\n------------------------------------" << endl;
        cout << "MENU\n";
        cout << "------------------------------------";

        cout << "\n1. Add New Product" << endl;
        cout << "2. Add Stock" << endl;
        cout << "3. Sell Stock" << endl;
        cout << "4. View Inventory" << endl;
        cout << "5. Generate Report" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            manager.addProduct();
            break;
        case 2:
            manager.addStock();
            break;
        case 3:
            manager.sellStock();
            break;
        case 4:
            manager.displayInventory();
            break;
        case 5:
            manager.generateReport();
            manager.saveTransactions();
            break;
        case 6:
            cout << "Saving data and exiting..." << endl;
            manager.saveInventory();
            manager.saveTransactions();
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    cout << "Thank you for using Inventory Control System!" << endl;
    return 0;
}