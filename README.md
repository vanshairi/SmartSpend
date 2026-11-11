# SmartSpend – Personal Expense Tracker

SmartSpend is a C++17 console-based personal expense tracking application designed to help users manage their income and expenses, monitor their financial balance, and maintain transaction records.

The project is developed using Object-Oriented Programming concepts in C++ and uses file handling for permanent data storage.

## Features

- **Income Management**

  - Add income records
  - View all income records
  - Search income by ID
  - Delete income records

- **Expense Management**

  - Add expenses
  - Select from predefined expense categories
  - View all expense records
  - Search expenses by ID
  - Delete expense records

- **Transaction History**

  - View income and expense records
  - Search transactions by type and ID

- **Financial Summary**

  - Calculate total income
  - Calculate total expenses
  - Calculate current balance

- **Dashboard**

  - View financial overview
  - View transaction counts
  - Monitor current balance

- **File Storage**

  - Save records in text files
  - Load records when the application starts
  - Preserve records across application restarts
  - Automatically generate transaction IDs

## Technologies Used

- C++
- C++17
- Object-Oriented Programming
- Standard Template Library (STL)
- Vectors
- File Handling (`fstream`)
- Filesystem Library

## Project Structure

```text
SmartSpend/
│
├── main.cpp
├── README.md
├── .gitignore
│
└── data/
    ├── incomes.txt
    └── expenses.txt
```

The `data` directory and transaction files are created locally by the application as needed.

## Prerequisites

- A C++ compiler supporting C++17
- GCC or G++
- Linux, Windows, or another compatible environment

## Installation and Execution

### 1. Clone the repository

```bash
git clone https://github.com/vanshairi/SmartSpend.git
```

### 2. Navigate to the project directory

```bash
cd SmartSpend
```

### 3. Compile the application

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o SmartSpend
```

### 4. Run the application

```bash
./SmartSpend
```

## Expense Categories

SmartSpend currently supports the following predefined categories:

1. Food
2. Transportation
3. Shopping
4. Entertainment
5. Education
6. Healthcare
7. Bills
8. Other

## Data Storage

SmartSpend uses local text files to store transaction records:

- `data/incomes.txt`
- `data/expenses.txt`

Transaction records are loaded when the application starts and saved after successful additions and deletions.

The data directory is excluded from version control to avoid publishing personal financial records.

## Current Version

**Version:** 1.0.0

**Application Type:** Console-based

**Language:** C++17

## Future Improvements

Potential improvements planned for future versions:

- Stronger input validation
- Date validation
- Monthly expense reports
- Custom expense categories
- Budget management
- Budget alerts
- Graphical user interface
- Database integration

## Learning Objectives

This project provides practical experience with:

- Classes and objects
- Encapsulation
- Constructors
- Member functions
- Vectors and STL
- File handling
- Data persistence
- Menu-driven applications

## Author

Developed as a C++ Object-Oriented Programming project.

---

*SmartSpend – Track your money. Understand your spending.*
