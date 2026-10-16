/*
Author:Kobe Ke
Purpose:Make a budget planner to keep track of expenses. Planner allows users to plan their spending by adding transactions, managing categories with set budgets, and calculating balances. (Catagories have to be made before you can add transactions)
    
   Testing Included:
   - Function calls for all major features
   - Test menu displayed in `drawMenu()`
   - User is able to "select" a category during `addTransaction()` simulation
   - All functions print confirmation messages to show that the program flow works

   Remaining Work / Problems:
   - No real data is being stored yet (vectors/structs will be added later)
   - Need to implement actual file I/O, data storage, and calculations
   - Need input validation
   - Unsure whether to use `map`, `struct`, or `class` for categories and transactions � this will depend on complexity

*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Transaction 
{
    string type; // "income" or "expense"
    string category;
    string description;
    double amount;
};

struct CategoryBudget 
{
    string name;
    double budget;
};

vector<Transaction> transactions;
vector<CategoryBudget> categories;

void drawMenu();
void addTransaction();
void viewTransactions();
void calculateBalance();
void manageCategories();
void viewBudgetStatus();
void saveToFile();
void loadFromFile();

int findCategoryIndex(const string& name);

int main() 
{
    loadFromFile();
    int choice;
    do 
    {
        drawMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) 
        {
        case 1: addTransaction(); break;
        case 2: viewTransactions(); break;
        case 3: calculateBalance(); break;
        case 4: manageCategories(); break;
        case 5: viewBudgetStatus(); break;
        case 6: saveToFile(); break;
        case 7: loadFromFile(); break;
        case 8: cout << "Exiting program..." << endl; break;
        default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

void drawMenu() {
    cout << "\n=== Budget Planner Menu ===" << endl;
    cout << "1. Add Transaction" << endl;
    cout << "2. View Transactions" << endl;
    cout << "3. View Balance" << endl;
    cout << "4. Manage Categories & Budgets" << endl;
    cout << "5. View Budget Status" << endl;
    cout << "6. Save to File" << endl;
    cout << "7. Load from File" << endl;
    cout << "8. Exit" << endl;
    cout << "===========================\n" << endl;
}

void addTransaction() 
{
    Transaction t;
    cout << "Enter transaction type (income/expense): ";
    getline(cin, t.type);

    cout << "Enter amount: $";
    cin >> t.amount;
    cin.ignore();

    cout << "Enter description: ";
    getline(cin, t.description);

    if (categories.empty()) 
    {
        cout << "No categories found. Please add one first.\n";
        return;
    }

    cout << "Select a category:" << endl;
    for (size_t i = 0; i < categories.size(); i++)
    {
        cout << i + 1 << ". " << categories[i].name << endl;
    }
    int catChoice;
    cin >> catChoice;
    cin.ignore();

    if (catChoice < 1 || catChoice > categories.size()) 
    {
        cout << "Invalid category. Transaction cancelled.\n";
        return;
    }
    t.category = categories[catChoice - 1].name;

    transactions.push_back(t);
    cout << "Transaction added successfully!\n";
}

void viewTransactions()
{
    if (transactions.empty()) 
    {
        cout << "No transactions to display.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\nAll Transactions:\n";
    for (const auto& t : transactions) 
    {
        cout << t.type << " | $" << t.amount << " | " << t.category << " | " << t.description << endl;
    }
}

void calculateBalance() 
{
    double income = 0, expenses = 0;
    for (const auto& t : transactions) 
    {
        if (t.type == "income") income += t.amount;
        else if (t.type == "expense") expenses += t.amount;
    }
    cout << fixed << setprecision(2);
    cout << "\nTotal Income: $" << income << endl;
    cout << "Total Expenses: $" << expenses << endl;
    cout << "Current Balance: $" << (income - expenses) << endl;
}

void manageCategories()
{
    string name;
    double budget;
    cout << "Enter new category name: ";
    getline(cin, name);

    cout << "Enter monthly budget for " << name << ": $";
    cin >> budget;
    cin.ignore();

    int index = findCategoryIndex(name);
    if (index != -1) {
        categories[index].budget = budget;
        cout << "Updated budget for category.\n";
    }
    else {
        categories.push_back({ name, budget });
        cout << "Category added successfully.\n";
    }
}

void viewBudgetStatus()
{
    if (categories.empty()) 
    {
        cout << "No categories defined.\n";
        return;
    }

    for (const auto& cat : categories) 
    {
        double spent = 0;
        for (const auto& t : transactions)
        {
            if (t.type == "expense" && t.category == cat.name)
            {
                spent += t.amount;
            }
        }
        cout << cat.name << ": $" << spent << " spent / $" << cat.budget << " budget";
        if (spent > cat.budget) cout << " (Over Budget!)";
        cout << endl;
    }
}

void saveToFile() 
{
    ofstream file("transactions.txt");
    for (const auto& t : transactions) 
    {
        file << t.type << "," << t.amount << "," << t.category << "," << t.description << endl;
    }
    file.close();
    cout << "Transactions saved to file.\n";
}

void loadFromFile() 
{
    transactions.clear();
    ifstream file("transactions.txt");
    string type, category, description;
    double amount;
    while (getline(file, type, ',')) 
    {
        file >> amount;
        file.ignore();
        getline(file, category, ',');
        getline(file, description);
        transactions.push_back({ type, category, description, amount });
    }
    file.close();
    cout << "Transactions loaded from file.\n";
}

int findCategoryIndex(const string& name) 
{
    for (size_t i = 0; i < categories.size(); i++) 
    {
        if (categories[i].name == name) return i;
    }
    return -1;
}
