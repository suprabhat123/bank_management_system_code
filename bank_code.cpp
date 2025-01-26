#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;
    vector<string> transactionHistory;

public:
    // Parameterized constructor
    Account(int accNo, const string& accHolder, double initialBalance)
        : accountNumber(accNo), accountHolder(accHolder), balance(initialBalance) {
        transactionHistory.push_back("Account created with balance: " + to_string(initialBalance));
    }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive." << endl;
            return;
        }
        balance += amount;
        transactionHistory.push_back("Deposited: " + to_string(amount));
        cout << "Deposit successful. Current balance: " << balance << endl;
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive." << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return;
        }
        balance -= amount;
        transactionHistory.push_back("Withdrawn: " + to_string(amount));
        cout << "Withdrawal successful. Current balance: " << balance << endl;
    }

    // Display balance
    void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }

    // Display transaction history
    void displayTransactionHistory() const {
        cout << "Transaction history for account " << accountNumber << ":" << endl;
        for (const string& record : transactionHistory) {
            cout << "  - " << record << endl;
        }
    }
};

class Bank {
private:
    map<int, Account> accounts;
    int nextAccountNumber;

public:
    Bank() : nextAccountNumber(1001) {}

    // Create a new account
    void createAccount(const string& accountHolder, double initialBalance) {
        if (initialBalance < 0) {
            cout << "Initial balance cannot be negative." << endl;
            return;
        }
        accounts.emplace(nextAccountNumber, Account(nextAccountNumber, accountHolder, initialBalance));
        cout << "Account created successfully. Account Number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    // Access an existing account
    void accessAccount(int accountNumber) {
        auto it = accounts.find(accountNumber);
        if (it == accounts.end()) {
            cout << "Account not found." << endl;
            return;
        }

        Account& account = it->second;
        int choice;
        do {
            cout << "\n--- Account Menu ---\n";
            cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Transaction History\n5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amount;
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    account.deposit(amount);
                    break;
                }
                case 2: {
                    double amount;
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    account.withdraw(amount);
                    break;
                }
                case 3:
                    account.checkBalance();
                    break;
                case 4:
                    account.displayTransactionHistory();
                    break;
                case 5:
                    cout << "Exiting account menu." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n2. Access Account\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accountHolder;
                double initialBalance;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, accountHolder);
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                bank.createAccount(accountHolder, initialBalance);
                break;
            }
            case 2: {
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.accessAccount(accountNumber);
                break;
            }
            case 3:
                cout << "Exiting system. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
