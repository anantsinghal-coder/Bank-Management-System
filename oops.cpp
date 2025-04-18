#include <iostream>
#include <vector>
using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    Account(string accNum, string accHolder, double bal) {
        accountNumber = accNum;
        accountHolder = accHolder;
        balance = bal;
    }   

    virtual void deposit(double amount) = 0; 
    virtual void withdraw(double amount) = 0; 

    void displayBalance() {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Current Balance: $" << balance << endl;
    }

    string getAccountNumber() { return accountNumber; }
};
class SavingsAccount : public Account {
private:
    double interestRate = 2.5; 

public:
    SavingsAccount(string accNum, string accHolder, double bal)
        : Account(accNum, accHolder, bal) {}

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Insufficient balance or invalid withdrawal amount!" << endl;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit = 500; 

public:
    CurrentAccount(string accNum, string accHolder, double bal)
        : Account(accNum, accHolder, bal) {}

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && amount <= (balance + overdraftLimit)) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Overdraft limit exceeded or invalid withdrawal amount!" << endl;
        }
    }
};

class Bank {
private:
    vector<Account*> accounts;

public:
    void createAccount() {
        string accNum, accHolder;
        double balance;
        int choice;

        cout << "\nEnter Account Number: ";
        cin >> accNum;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, accHolder);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "Select Account Type (1: Savings, 2: Current): ";
        cin >> choice;

        if (choice == 1) {
            accounts.push_back(new SavingsAccount(accNum, accHolder, balance));
            cout << "Savings Account Created Successfully!" << endl;
        } else if (choice == 2) {
            accounts.push_back(new CurrentAccount(accNum, accHolder, balance));
            cout << "Current Account Created Successfully!" << endl;
        } else {
            cout << "Invalid account type!" << endl;
        }
    }

    void depositMoney() {
        string accNum;
        double amount;
        cout << "\nEnter Account Number: ";
        cin >> accNum;

        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                acc->deposit(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void withdrawMoney() {
        string accNum;
        double amount;
        cout << "\nEnter Account Number: ";
        cin >> accNum;

        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                acc->withdraw(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void checkBalance() {
        string accNum;
        cout << "\nEnter Account Number: ";
        cin >> accNum;

        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNum) {
                acc->displayBalance();
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void exitSystem() {
        for (auto acc : accounts) {
            delete acc;
        }
        accounts.clear();
        cout << "Thank you for using the Bank Management System!" << endl;
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositMoney();
                break;
            case 3:
                bank.withdrawMoney();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.exitSystem();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
