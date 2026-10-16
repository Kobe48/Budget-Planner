# Budget Planner

A command-line budget planner written in C++. It lets you set up spending categories with monthly budgets, record income and expenses, check your balance, and see whether you're over budget in any category.

## Features

- **Categories & budgets** – create spending categories (e.g. Food, Rent) and give each one a monthly budget, or update an existing category's budget
- **Transactions** – record income and expenses, each with an amount, a description, and a category
- **Balance** – see total income, total expenses, and your current balance
- **Budget status** – see how much you've spent in each category compared to its budget, with a warning when you go over
- **Save & load** – save transactions to `transactions.txt` and load them back later

## How to Run

### Visual Studio (Windows)

1. Open `budget-planner.sln` in Visual Studio.
2. Press **Ctrl + F5** (or click **Debug → Start Without Debugging**) to build and run.

### Command line (g++)

```bash
g++ budget-planner.cpp -o budget_planner
./budget_planner
```

## Usage

When the program starts, it shows this menu:

```
=== Budget Planner Menu ===
1. Add Transaction
2. View Transactions
3. View Balance
4. Manage Categories & Budgets
5. View Budget Status
6. Save to File
7. Load from File
8. Exit
```

Enter the number of the option you want.

**Create a category before adding transactions.** Use option 4 first, because every transaction has to belong to a category.

When adding a transaction, type the type in lowercase, either `income` or `expense`.

### Example

```
Enter your choice: 4
Enter new category name: Food
Enter monthly budget for Food: $200
Category added successfully.

Enter your choice: 1
Enter transaction type (income/expense): expense
Enter amount: $12.50
Enter description: Lunch
Select a category:
1. Food
1
Transaction added successfully!

Enter your choice: 5
Food: $12.5 spent / $200 budget
```

## Files

| File | Purpose |
|---|---|
| `budget-planner.cpp` | All of the program's source code |
| `budget-planner.sln` / `.vcxproj` | Visual Studio project files |
| `transactions.txt` | Created when you save. Each line is `type,amount,category,description` |

## Author

Kobe Ke