#include <iostream>   // For input/output (cin, cout)
#include <fstream>    // For file handling (ifstream, ofstream)
#include <vector>     // For dynamic array storage
#include <string>     // For string operations
#include <iomanip>    // For formatted output (setw, left)
#include <algorithm>  // For STL algorithms (find_if, count_if)

using namespace std;


/* ==========================================================
   PRODUCT CLASS
   Represents a single product with name and quantity.
   Includes stock management functions.
   ========================================================== */
class Product
{
private:
    string name;          // Stores product name
    int quantity;         // Stores current stock quantity
    const int MIN_STOCK = 10;   // Minimum stock threshold

public:

    // Constructor using initialization list
    Product(string n = "", int q = 0) : name(n), quantity(q) {}

    // Getter functions (const ensures data is not modified)
    string getName() const { return name; }
    int getQuantity() const { return quantity; }

    // Check if product quantity is below minimum threshold
    bool isLowStock() const { return quantity <= MIN_STOCK; }

    // Increase stock quantity
    void addStock(int amount)
    {
        if (amount > 0)
            quantity += amount;
    }

    // Sell stock if enough quantity is available
    bool sellStock(int amount)
    {
        if (amount > 0 && amount <= quantity)
        {
            quantity -= amount;
            return true;
        }
        return false;
    }

    // Display product details using formatted output
    void display() const
    {
        cout << left << setw(20) << name << setw(10) << quantity;

        if (isLowStock())  // Check low stock condition
            cout << " *** LOW STOCK ***";

        cout << endl;
    }
};


/* ==========================================================
   TRANSACTION CLASS
   Stores inventory activity records like purchase or sale.
   Demonstrates object-oriented transaction tracking.
   ========================================================== */
class Transaction
{
private:
    string productName;   // Product involved in transaction
    string type;          // Type of transaction (SALE/PURCHASE)
    int quantity;         // Quantity involved
    string timestamp;     // Date of transaction

public:

    // Constructor initializes transaction details
    Transaction(string name, string t, int q)
        : productName(name), type(t), quantity(q)
    {
        timestamp = "2026-03-10";  // Static timestamp for simplicity
    }

    // Getter functions
    string getProductName() const { return productName; }
    string getType() const { return type; }
    int getQuantity() const { return quantity; }

    // Display transaction information
    void display() const
    {
        cout << left << setw(20) << productName
             << setw(10) << type
             << setw(10) << quantity << endl;
    }
};


/* ==========================================================
   INVENTORY MANAGER CLASS
   Central controller of the inventory system.
   Manages products, transactions, and file storage.
   ========================================================== */
class InventoryManager
{
private:

    // Vector containers used to store products and transactions
    vector<Product> products;
    vector<Transaction> transactions;

    // File names used for persistent data storage
    const string DATA_FILE = "inventory.txt";
    const string TRANS_FILE = "transactions.txt";

public:

    /* -------------------------------------------------------
       Load inventory data from file using file input stream
       ------------------------------------------------------- */
    void loadInventory()
    {
        ifstream file(DATA_FILE);

        // If file does not exist, exit function
        if (!file.is_open())
            return;

        string name;
        int qty;

        // Read product name and quantity until end of file
        while (file >> name >> qty)
        {
            products.emplace_back(name, qty); // Add product to vector
        }

        file.close();

        cout << "Inventory loaded from file." << endl;
    }


    /* -------------------------------------------------------
       Save inventory data to file using file output stream
       ------------------------------------------------------- */
    void saveInventory()
    {
        ofstream file(DATA_FILE);

        // Write each product to file
        for (const auto &p : products)
        {
            file << p.getName() << " " << p.getQuantity() << endl;
        }

        file.close();
    }


    /* -------------------------------------------------------
       Save transaction history to file
       ------------------------------------------------------- */
    void saveTransactions()
    {
        ofstream file(TRANS_FILE);

        for (const auto &t : transactions)
        {
            file << t.getProductName() << " "
                 << t.getType() << " "
                 << t.getQuantity() << endl;
        }

        file.close();
    }


    /* -------------------------------------------------------
       Add new product to inventory
       Demonstrates object creation and vector insertion
       ------------------------------------------------------- */
    void addProduct()
    {
        string name;
        int qty;

        cout << "Enter Product Name: ";
        getline(cin, name); // getline used for full name input

        cout << "Enter Quantity: ";
        cin >> qty;

        // Create new product object and add to vector
        products.emplace_back(name, qty);

        // Record transaction as purchase
        transactions.emplace_back(name, "PURCHASE", qty);

        saveInventory();

        cout << "Product added successfully!" << endl;
    }


    /* -------------------------------------------------------
       Increase stock of an existing product
       Uses STL algorithm find_if
       ------------------------------------------------------- */
    void addStock()
    {
        string name;
        int qty;

        cout << "Enter Product Name: ";
        getline(cin, name);

        auto it = findProduct(name); // search product

        if (it != products.end())
        {
            cout << "Current Quantity: " << it->getQuantity() << endl;

            cout << "Enter Quantity to Add: ";
            cin >> qty;

            it->addStock(qty); // update stock

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


    /* -------------------------------------------------------
       Sell stock from inventory
       Demonstrates validation logic
       ------------------------------------------------------- */
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

            if (it->sellStock(qty))  // Attempt sale
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


    /* -------------------------------------------------------
       Display current inventory in table format
       Uses formatted output
       ------------------------------------------------------- */
    void displayInventory()
    {
        if (products.empty())
        {
            cout << "No products in inventory." << endl;
            return;
        }

        cout << "\n=== CURRENT INVENTORY ===" << endl;

        cout << left << setw(20) << "Product Name"
             << setw(10) << "Quantity" << endl;

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


    /* -------------------------------------------------------
       Generate full report (inventory + transactions)
       ------------------------------------------------------- */
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
            cout << left << setw(20) << "Product"
                 << setw(10) << "Type"
                 << setw(10) << "Quantity" << endl;

            cout << string(45, '=') << endl;

            for (const auto &t : transactions)
            {
                t.display();
            }
        }
    }


private:

    /* -------------------------------------------------------
       Find product using STL find_if algorithm
       Lambda function used for comparison
       ------------------------------------------------------- */
    vector<Product>::iterator findProduct(const string &name)
    {
        return find_if(products.begin(), products.end(),
                       [&](const Product &p)
                       { return p.getName() == name; });
    }


    /* -------------------------------------------------------
       Count low stock products using count_if algorithm
       ------------------------------------------------------- */
    int countLowStock()
    {
        return count_if(products.begin(), products.end(),
                        [](const Product &p)
                        { return p.isLowStock(); });
    }
};


/* ==========================================================
   MAIN FUNCTION
   Menu-driven interface for interacting with the system
   ========================================================== */
int main()
{
    cout << ".      OUTPUT : " << endl;
    cout << "__________________________________________________________________________________________________" << endl;
    cout << endl << endl;

    InventoryManager manager;

    manager.loadInventory(); // Load saved data

    cout << "=== INVENTORY CONTROL SYSTEM ===" << endl;
    cout << "Welcome! Data will be saved automatically." << endl;

    int choice;

    // Menu loop
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

        cin.ignore(); // clear input buffer

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