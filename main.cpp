#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <sstream>
#include <cmath>

using namespace std;


class Income
{
private:
    int incomeID;
    double amount;
    string source;
    string description;
    string date;

public:

    // Default constructor
    Income()
    {
        incomeID = 0;
        amount = 0.0;
        source = "";
        description = "";
        date = "";
    }

    // Parameterized constructor
    Income(int id, double amt, string src, string desc, string dt)
    {
        incomeID = id;
        amount = amt;
        source = src;
        description = desc;
        date = dt;
    }

    // Getter functions
    int getIncomeID() const
    {
        return incomeID;
    }

    double getAmount() const
    {
        return amount;
    }

    string getSource() const
    {
        return source;
    }

    string getDescription() const
    {
        return description;
    }

    string getDate() const
    {
        return date;
    }

    // Display income details
    void displayIncome() const
    {
        cout << "\nIncome ID   : " << incomeID;
        cout << "\nAmount      : Rs. " << fixed << setprecision(2) << amount;
        cout << "\nSource      : " << source;
        cout << "\nDescription : " << description;
        cout << "\nDate        : " << date << endl;
    }
};


class Expense
{
private:
    int expenseID;
    double amount;
    string category;
    string description;
    string date;

public:

    // Default constructor
    Expense()
    {
        expenseID = 0;
        amount = 0.0;
        category = "";
        description = "";
        date = "";
    }

    // Parameterized constructor
    Expense(int id, double amt, string cat,
            string desc, string dt)
    {
        expenseID = id;
        amount = amt;
        category = cat;
        description = desc;
        date = dt;
    }

    // Getter functions
    int getExpenseID() const
    {
        return expenseID;
    }

    double getAmount() const
    {
        return amount;
    }

    string getCategory() const
    {
        return category;
    }

    string getDescription() const
    {
        return description;
    }

    string getDate() const
    {
        return date;
    }

    // Display expense details
    void displayExpense() const
    {
        cout << "\nExpense ID  : " << expenseID;
        cout << "\nAmount      : Rs. " << fixed << setprecision(2) << amount;
        cout << "\nCategory    : " << category;
        cout << "\nDescription : " << description;
        cout << "\nDate        : " << date << endl;
    }
};



class ExpenseTracker
{
private:
    vector<Income> incomes;
    vector<Expense> expenses;

    int nextIncomeID;
    int nextExpenseID;

    // Safely read integer input
    bool readInt(const string& prompt, int& value)
    {
        string input;

        while (true)
        {
            cout << prompt;

            if (!getline(cin, input))
            {
                return false;
            }

            stringstream inputStream(input);
            char extra;

            if (inputStream >> value && !(inputStream >> extra))
            {
                return true;
            }

            cout << "Invalid input! Please enter a valid integer.\n";
        }
    }

    // Safely read decimal input
    bool readDouble(const string& prompt, double& value)
    {
        string input;

        while (true)
        {
            cout << prompt;

            if (!getline(cin, input))
            {
                return false;
            }

            stringstream inputStream(input);
            char extra;

            if (inputStream >> value &&
                !(inputStream >> extra) &&
                isfinite(value))
            {
                return true;
            }

            cout << "Invalid input! Please enter a valid number.\n";
        }
    }


    bool readNonEmptyString(const string& prompt, string& value)
    {
        while (true)
        {
            cout << prompt;

            if (!getline(cin, value))
            {
                return false;
            }

            if (!value.empty() &&
                value.find_first_not_of(" \t") != string::npos)
            {
                return true;
            }

            cout << "Input cannot be empty! Please try again.\n";
        }
    }


    bool isValidDate(const string& date)
    {
        // Check the required date format
        if (date.length() != 10 ||
            date[2] != '-' ||
            date[5] != '-')
        {
            return false;
        }

        // Check that all other characters are digits
        for (int i = 0; i < 10; i++)
        {
            if (i == 2 || i == 5)
                continue;

            if (date[i] < '0' || date[i] > '9')
                return false;
        }

        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));

        if (year < 1 || month < 1 || month > 12)
            return false;

        int daysInMonth[] =
        {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };

        // Check for leap year
        bool leapYear =
            (year % 400 == 0) ||
            (year % 4 == 0 && year % 100 != 0);

        if (leapYear)
        {
            daysInMonth[1] = 29;
        }

        if (day < 1 || day > daysInMonth[month - 1])
            return false;

        return true;
    }


    bool readDate(const string& prompt, string& date)
    {
        while (true)
        {
            cout << prompt;

            if (!getline(cin, date))
            {
                return false;
            }

            if (isValidDate(date))
            {
                return true;
            }

            cout << "Invalid date! Please enter a valid date "
                << "in DD-MM-YYYY format.\n";
        }
    }

public:

    // Constructor
    ExpenseTracker()
    {   
        nextIncomeID = 1;
        nextExpenseID = 1;

        filesystem::create_directories("data");

        loadData();
    }

    void addIncome()
    {
        double amount;
        string source, description, date;

        if (!readDouble("\nEnter income amount: ", amount))
            return;

        if (amount <= 0)
        {
            cout << "\nInvalid amount! Amount must be greater than zero.\n";
            return;
        }

        if (!readNonEmptyString("Enter income source: ", source))
            return;

        if (!readNonEmptyString("Enter description: ", description))
            return;

        if (!readDate("Enter date (DD-MM-YYYY): ", date))
            return;

        Income newIncome(
            nextIncomeID,
            amount,
            source,
            description,
            date
        );

        incomes.push_back(newIncome);
        saveData();

        cout << "\nIncome added successfully!";
        cout << "\nIncome ID: " << nextIncomeID << endl;

        nextIncomeID++;
    }


    void viewIncome()
    {
        if (incomes.empty())
        {
            cout << "\nNo income records found.\n";
            return;
        }

        cout << "\n========== INCOME RECORDS ==========\n";

        for (const Income& income : incomes)
        {
            income.displayIncome();
            cout << "-----------------------------------\n";
        }
    }

    void searchIncome()
    {
        int id;

        if (!readInt("\nEnter Income ID to search: ", id))
            return;

        for (const Income& income : incomes)
        {
            if (income.getIncomeID() == id)
            {
                cout << "\nIncome record found!\n";
                income.displayIncome();
                return;
            }
        }

        cout << "\nIncome record not found.\n";
    }

    void deleteIncome()
    {
        int id;

        if (!readInt("\nEnter Income ID to delete: ", id))
            return;

        for (auto it = incomes.begin(); it != incomes.end(); it++)
        {
            if (it->getIncomeID() == id)
            {
                incomes.erase(it);
                saveData();

                cout << "\nIncome deleted successfully!\n";
                return;
            }
        }

        cout << "\nIncome record not found.\n";
    }


    
    void addExpense()
    {
        double amount;
        string category, description, date;

        if (!readDouble("\nEnter expense amount: ", amount))
            return;

        if (amount <= 0)
        {
            cout << "\nInvalid amount! Amount must be greater than zero.\n";
            return;
        }

        cout << "\nSelect Expense Category:\n";
        cout << "1. Food\n";
        cout << "2. Transportation\n";
        cout << "3. Shopping\n";
        cout << "4. Entertainment\n";
        cout << "5. Education\n";
        cout << "6. Healthcare\n";
        cout << "7. Bills\n";
        cout << "8. Other\n";

        int choice;

        if (!readInt("Enter choice: ", choice))
            return;

        switch (choice)
        {
            case 1: category = "Food"; break;
            case 2: category = "Transportation"; break;
            case 3: category = "Shopping"; break;
            case 4: category = "Entertainment"; break;
            case 5: category = "Education"; break;
            case 6: category = "Healthcare"; break;
            case 7: category = "Bills"; break;
            case 8: category = "Other"; break;

            default:
                cout << "\nInvalid category!\n";
                return;
        }

        if (!readNonEmptyString("Enter description: ", description))
            return;

        if (!readDate("Enter date (DD-MM-YYYY): ", date))
            return;

        Expense newExpense(
            nextExpenseID,
            amount,
            category,
            description,
            date
        );

        expenses.push_back(newExpense);
        saveData();

        cout << "\nExpense added successfully!";
        cout << "\nExpense ID: " << nextExpenseID << endl;

        nextExpenseID++;
    }


    void viewExpenses()
    {
        if (expenses.empty())
        {
            cout << "\nNo expense records found.\n";
            return;
        }

        cout << "\n========== EXPENSE RECORDS ==========\n";

        for (const Expense& expense : expenses)
        {
            expense.displayExpense();
            cout << "-----------------------------------\n";
        }
    }

    void searchExpense()
    {
        int id;

        if (!readInt("\nEnter Expense ID to search: ", id))
            return;

        for (const Expense& expense : expenses)
        {
            if (expense.getExpenseID() == id)
            {
                cout << "\nExpense record found!\n";
                expense.displayExpense();
                return;
            }
        }

        cout << "\nExpense record not found.\n";
    }

    void deleteExpense()
    {
        int id;

        if (!readInt("\nEnter Expense ID to delete: ", id))
            return;

        for (auto it = expenses.begin(); it != expenses.end(); it++)
        {
            if (it->getExpenseID() == id)
            {
                expenses.erase(it);
                saveData();

                cout << "\nExpense deleted successfully!\n";
                return;
            }
        }

        cout << "\nExpense record not found.\n";
    }


    double calculateTotalIncome()
    {
        double total = 0.0;

        for (const Income& income : incomes)
        {
            total += income.getAmount();
        }

        return total;
    }

    double calculateTotalExpenses()
    {
        double total = 0.0;

        for (const Expense& expense : expenses)
        {
            total += expense.getAmount();
        }

        return total;
    }

    double calculateBalance()
    {
        return calculateTotalIncome() - calculateTotalExpenses();
    }

    void displaySummary()
    {
        cout << "\n========== FINANCIAL SUMMARY ==========\n";

        cout << fixed << setprecision(2);

        cout << "Total Income    : Rs. "
            << calculateTotalIncome() << endl;

        cout << "Total Expenses  : Rs. "
            << calculateTotalExpenses() << endl;

        cout << "Current Balance : Rs. "
            << calculateBalance() << endl;

        cout << "=======================================\n";
    }


    void viewAllTransactions()
    {
        if (incomes.empty() && expenses.empty())
        {
            cout << "\nNo transactions found.\n";
            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        cout << "\n---------- INCOME ----------\n";

        for (const Income& income : incomes)
        {
            income.displayIncome();
            cout << "-----------------------------------\n";
        }

        cout << "\n---------- EXPENSES ----------\n";

        for (const Expense& expense : expenses)
        {
            expense.displayExpense();
            cout << "-----------------------------------\n";
        }
    }


    
    void searchTransaction()
    {
        int type, id;

        cout << "\nSearch Transaction\n";
        cout << "1. Search Income\n";
        cout << "2. Search Expense\n";

        if (!readInt("Enter choice: ", type))
            return;

        if (type != 1 && type != 2)
        {
            cout << "\nInvalid choice!\n";
            return;
        }

        if (!readInt("Enter Transaction ID: ", id))
            return;

        if (type == 1)
        {
            for (const Income& income : incomes)
            {
                if (income.getIncomeID() == id)
                {
                    cout << "\nIncome transaction found!\n";
                    income.displayIncome();
                    return;
                }
            }
        }
        else
        {
            for (const Expense& expense : expenses)
            {
                if (expense.getExpenseID() == id)
                {
                    cout << "\nExpense transaction found!\n";
                    expense.displayExpense();
                    return;
                }
            }
        }

        cout << "\nTransaction not found.\n";
    }


    void saveIncomes()
    {
        ofstream outFile("data/incomes.txt");

        for (const Income& income : incomes)
        {
            outFile << income.getIncomeID() << " "
                    << setprecision(17) << income.getAmount() << " "
                    << quoted(income.getSource()) << " "
                    << quoted(income.getDescription()) << " "
                    << quoted(income.getDate()) << endl;
        }

        outFile.close();
    }

    void saveExpenses()
    {
        ofstream outFile("data/expenses.txt");

        for (const Expense& expense : expenses)
        {
            outFile << expense.getExpenseID() << " "
                    << setprecision(17) << expense.getAmount() << " "
                    << quoted(expense.getCategory()) << " "
                    << quoted(expense.getDescription()) << " "
                    << quoted(expense.getDate()) << endl;
        }

        outFile.close();
    }

    void loadIncomes()
    {
        ifstream inFile("data/incomes.txt");

        if (!inFile)
        {
            return;
        }

        int id;
        double amount;
        string source, description, date;

        while (inFile >> id >> amount
                    >> quoted(source)
                    >> quoted(description)
                    >> quoted(date))
        {
            incomes.push_back(
                Income(id, amount, source, description, date)
            );

            if (id >= nextIncomeID)
            {
                nextIncomeID = id + 1;
            }
        }

        inFile.close();
    }

    void loadExpenses()
    {
        ifstream inFile("data/expenses.txt");

        if (!inFile)
        {
            return;
        }

        int id;
        double amount;
        string category, description, date;

        while (inFile >> id >> amount
                    >> quoted(category)
                    >> quoted(description)
                    >> quoted(date))
        {
            expenses.push_back(
                Expense(id, amount, category, description, date)
            );

            if (id >= nextExpenseID)
            {
                nextExpenseID = id + 1;
            }
        }

        inFile.close();
    }

    void saveData()
    {
        saveIncomes();
        saveExpenses();
    }

    void loadData()
    {
        loadIncomes();
        loadExpenses();
    }


    void displayDashboard()
    {
        double totalIncome = calculateTotalIncome();
        double totalExpenses = calculateTotalExpenses();
        double balance = calculateBalance();

        int incomeCount = incomes.size();
        int expenseCount = expenses.size();

        int totalTransactions = incomeCount + expenseCount;

        cout << "\n";
        cout << "============================================\n";
        cout << "             SMARTSPEND DASHBOARD           \n";
        cout << "============================================\n";

        cout << fixed << setprecision(2);

        cout << "\n FINANCIAL OVERVIEW\n";

        cout << "--------------------------------------------\n";

        cout << " Total Income       : Rs. " << totalIncome << endl;
        cout << " Total Expenses     : Rs. " << totalExpenses << endl;
        cout << " Current Balance    : Rs. " << balance << endl;

        cout << "\n TRANSACTION OVERVIEW\n";

        cout << "--------------------------------------------\n";

        cout << " Income Transactions  : " << incomeCount << endl;
        cout << " Expense Transactions : " << expenseCount << endl;
        cout << " Total Transactions   : " << totalTransactions << endl;

        cout << "============================================\n";
    }


    void incomeMenu()
    {
        int choice;

        do
        {
            cout << "\n========== INCOME MANAGEMENT ==========\n";
            cout << "1. Add Income\n";
            cout << "2. View All Income\n";
            cout << "3. Search Income\n";
            cout << "4. Delete Income\n";
            cout << "0. Back to Main Menu\n";

            if (!readInt("\nEnter your choice: ", choice))
                return;

            switch (choice)
            {
                case 1:
                    addIncome();
                    break;

                case 2:
                    viewIncome();
                    break;

                case 3:
                    searchIncome();
                    break;

                case 4:
                    deleteIncome();
                    break;

                case 0:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice!\n";
            }

        } while (choice != 0);
    }


    void expenseMenu()
    {
        int choice;

        do
        {
            cout << "\n========== EXPENSE MANAGEMENT ==========\n";
            cout << "1. Add Expense\n";
            cout << "2. View All Expenses\n";
            cout << "3. Search Expense\n";
            cout << "4. Delete Expense\n";
            cout << "0. Back to Main Menu\n";

            if (!readInt("\nEnter your choice: ", choice))
                return;

            switch (choice)
            {
                case 1:
                    addExpense();
                    break;

                case 2:
                    viewExpenses();
                    break;

                case 3:
                    searchExpense();
                    break;

                case 4:
                    deleteExpense();
                    break;

                case 0:
                    cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice!\n";
            }

        } while (choice != 0);
    }


    void run()
    {
        int choice;

        do
        {
            cout << "\n";
            cout << "============================================\n";
            cout << "              SMARTSPEND                   \n";
            cout << "       PERSONAL EXPENSE TRACKER             \n";
            cout << "============================================\n";

            cout << "\n1. Dashboard\n";
            cout << "2. Income Management\n";
            cout << "3. Expense Management\n";
            cout << "4. View Transaction History\n";
            cout << "5. Search Transaction\n";
            cout << "6. Financial Summary\n";
            cout << "0. Exit Application\n";

            if (!readInt("\nEnter your choice: ", choice))
                return;

            switch (choice)
            {
                case 1:
                    displayDashboard();
                    break;

                case 2:
                    incomeMenu();
                    break;

                case 3:
                    expenseMenu();
                    break;

                case 4:
                    viewAllTransactions();
                    break;

                case 5:
                    searchTransaction();
                    break;

                case 6:
                    displaySummary();
                    break;

                case 0:
                    saveData();
                    cout << "\nThank you for using SmartSpend!\n";
                    cout << "Your data has been saved successfully.\n";
                    break;

                default:
                    cout << "\nInvalid choice! Please try again.\n";
            }

        } while (choice != 0);
    }

};


int main()
{
    ExpenseTracker tracker;

    tracker.run();

    return 0;
}
