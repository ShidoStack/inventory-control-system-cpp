# Inventory Control System (C++)

![Language](https://img.shields.io/badge/Language-C++-blue)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![Status](https://img.shields.io/badge/Project-Completed-green)

A console-based **Inventory Control System** developed in C++ that allows users to manage products, track stock levels, record transactions, and generate inventory reports.

The system uses file handling for persistent data storage and demonstrates **Object-Oriented Programming (OOP)** concepts such as classes, encapsulation, and modular design.

This project simulates a basic inventory management environment and is ideal for learning **C++ programming, file handling, and STL usage**.

---

# Table of Contents

- [Project Overview](#project-overview)
- [Project Motivation](#project-motivation)
- [Key Features](#key-features)
- [Technologies Used](#technologies-used)
- [System Architecture](#system-architecture)
- [Program Workflow](#program-workflow)
- [Project Folder Structure](#project-folder-structure)
- [How to Compile and Run](#how-to-compile-and-run)
- [Project Preview](#project-preview)
- [Learning Outcomes](#learning-outcomes)
- [Possible Future Improvements](#possible-future-improvements)
- [Author](#author)

---

# Project Overview

The Inventory Control System is designed to simulate a basic product inventory management system where users can:

- Add new products
- Update stock levels
- Record sales transactions
- Monitor low stock items
- Generate inventory reports
- Store and retrieve inventory data using files

All operations are performed through a **menu-driven console interface**, making the application simple and user-friendly.

The program automatically saves inventory data and transaction history using text files so that information is preserved even after the application is closed.

---

# Project Motivation

This project was developed to practice **Object-Oriented Programming concepts in C++** and understand how real-world inventory management systems operate.

The system demonstrates how product data can be managed using **classes, file handling, and standard template library containers** while maintaining clean and modular code structure.

---

# Key Features

## Product Management

- Add new products to the inventory
- Track product name and quantity
- Display products in a structured table format

## Stock Management

- Increase stock for existing products
- Sell products and reduce quantity automatically
- Prevent sales when stock is insufficient

## Low Stock Detection

The system automatically detects products whose quantity falls below the minimum threshold.

Default minimum stock level:

```
10 units
```

Low stock products are clearly marked with a warning message.

## Transaction Recording

Every stock operation is recorded as a transaction containing:

- Product name
- Transaction type (Purchase or Sale)
- Quantity involved

These transactions can be reviewed in reports.

## Data Persistence

Inventory and transaction data are stored in external files.

Inventory data file

```
inventory.txt
```

Transaction history file

```
transactions.txt
```

These files allow the system to reload saved data when the program starts.

## Report Generation

The system can generate detailed reports including:

- Current inventory status
- Low stock alerts
- Transaction history

---

# Technologies Used

Programming Language

```
C++
```

Libraries Used

```
iostream
fstream
vector
string
iomanip
algorithm
```

Concepts Implemented

- Object Oriented Programming
- Encapsulation
- File Handling
- Dynamic Containers using vector
- Iterators
- Standard Template Library (STL)
- Lambda Expressions
- Menu Driven Interface

---

# System Architecture

The application is organized using three primary classes.

## Product Class

Represents an individual product stored in the inventory.

Responsibilities

- Store product name
- Store product quantity
- Detect low stock levels
- Update stock quantity
- Display product information

Key Functions

```
getName()
getQuantity()
isLowStock()
addStock()
sellStock()
display()
```

---

## Transaction Class

Represents an inventory transaction.

Responsibilities

- Store product name
- Store transaction type
- Store quantity involved
- Display transaction information

Key Functions

```
getProductName()
getType()
getQuantity()
display()
```

---

## InventoryManager Class

Acts as the central controller of the system.

Responsibilities

- Manage product collection
- Record transactions
- Load and save inventory data
- Generate reports
- Handle user interactions

Key Functions

```
loadInventory()
saveInventory()
saveTransactions()
addProduct()
addStock()
sellStock()
displayInventory()
generateReport()
```

---

# Program Workflow

When the program starts:

1. Inventory data is loaded from `inventory.txt`
2. The main menu is displayed
3. The user selects an operation
4. The selected operation modifies inventory or transactions
5. Data is saved automatically

Menu options include:

```
1. Add New Product
2. Add Stock
3. Sell Stock
4. View Inventory
5. Generate Report
6. Exit
```

---

# Project Folder Structure

Example repository structure

```
inventory-control-system-cpp
│
├── main.cpp
├── inventory.txt
├── transactions.txt
├── README.md
```

---

# How to Compile and Run

Compile using a C++ compiler such as **g++**

Compile the program

```
g++ main.cpp -o inventory
```

Run the program

```
./inventory
```

On Windows

```
inventory.exe
```

---

# Project Preview

Example console interface

```
=== INVENTORY CONTROL SYSTEM ===
Welcome! Data will be saved automatically.

MENU

1. Add New Product
2. Add Stock
3. Sell Stock
4. View Inventory
5. Generate Report
6. Exit
```

Example inventory display

```
Product Name        Quantity
===================================
Laptop              15
Mouse               8    *** LOW STOCK ***
Keyboard            20
```

---

# Learning Outcomes

This project helps in understanding several important C++ programming concepts including:

- Designing object-oriented systems
- Managing dynamic collections using vectors
- Implementing search operations with STL algorithms
- Handling persistent data storage using file streams
- Creating interactive console applications

---

# Possible Future Improvements

Possible enhancements include:

- Adding date and time for transactions
- Product price management
- Profit and sales analytics
- Search and filter functionality
- Graphical user interface
- Database integration (SQLite or MySQL)
- Multi-user support

---

# Author

Lokendra Joshi
