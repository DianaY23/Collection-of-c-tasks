#include <iostream>
#include <cstring>
using namespace std;

// ===== ИСКЛЮЧЕНИЯ =====
class AccountException {};
class InsufficientFundsException : public AccountException {};
class TransactionLimitExceededException : public AccountException {};
class InvalidAccountException : public AccountException {};
class NullPointerException : public AccountException {};

// ===== АБСТРАКТНЫЙ КЛАСС Account =====
class Account {
private:
    char* ownerName;
    int accountId;
    double balance;

public:
    Account(const char* name, int id, double bala) : accountId(id), balance(bala) {
        ownerName = new char[strlen(name) + 1];
        strcpy(ownerName, name);
    }

    virtual ~Account() {
        delete[] ownerName;
    }

    double Deposit(double amount) {
        if (amount < 0) throw TransactionLimitExceededException();
        balance += amount;
        return balance;
    }

    virtual void Withdraw(double amount) = 0;

    virtual void TransferTo(Account* target, double amount) {
        if (!target) throw NullPointerException();
        if (amount > balance) throw InsufficientFundsException();
        this->Withdraw(amount);
        target->Deposit(amount);
    }

    virtual void PrintInfo() const {
        cout << "Name: " << ownerName
             << " | ID: " << accountId
             << " | Balance: " << balance << endl;
    }

    const char* getName() const { return ownerName; }
    int getId() const { return accountId; }
    double getBalance() const { return balance; }

protected:
    void changeBalance(double newBalance) {
        balance = newBalance;
    }
};

// ===== SavingsAccount =====
class SavingsAccount : public Account {
public:
    SavingsAccount(const char* name, int id, double bala)
        : Account(name, id, bala) {}

    void Withdraw(double amount) {
        if (amount < 0 || amount > getBalance())
            throw InsufficientFundsException();
        changeBalance(getBalance() - amount);
    }

    void PrintInfo() const{
        cout << "SavingsAccount: ";
        Account::PrintInfo();
    }
};

// ===== CreditAccount =====
class CreditAccount : public Account {
private:
    double creditLimit;

public:
    CreditAccount(const char* name, int id, double bala, double limit)
        : Account(name, id, bala), creditLimit(limit) {}

    void Withdraw(double amount){
        if (amount < 0 || amount > getBalance() + creditLimit)
            throw InsufficientFundsException();
        changeBalance(getBalance() - amount);
    }

    void PrintInfo() const{
        cout << "CreditAccount: ";
        Account::PrintInfo();
        cout << " | Credit Limit: " << creditLimit << endl;
    }
};

// ===== Transaction =====
struct Transaction {
    int fromId;
    int toId;
    double amount;
    char type[20]; // "Deposit", "Withdraw", "Transfer"
};

// ===== TransactionManager =====
class TransactionManager {
private:
    Transaction* logs[1000];
    int count;

public:
    TransactionManager() : count(0) {}

    ~TransactionManager() {
        for (int i = 0; i < count; ++i)
            delete logs[i];
    }

    void Log(const char* type, int from, int to, double amount) {
        if (count >= 1000) return;
        Transaction* t = new Transaction;
        t->fromId = from;
        t->toId = to;
        t->amount = amount;
        strcpy(t->type, type);
        logs[count++] = t;
    }

    void ShowLogs() const {
        cout << "\n--- Transaction Logs ---\n";
        for (int i = 0; i < count; ++i) {
            cout << logs[i]->type << ": From #" << logs[i]->fromId
                 << " To #" << logs[i]->toId
                 << " Amount: " << logs[i]->amount << endl;
        }
        cout << "------------------------\n";
    }
};

// ===== MAIN =====
int main() {
    TransactionManager manager;

    try {
        SavingsAccount a("Alice", 1001, 500);
        CreditAccount b("Bob", 1002, 200, 300);

        a.Deposit(200);
        manager.Log("Deposit", a.getId(), a.getId(), 200);

        a.TransferTo(&b, 600);  // выбросит исключение
        manager.Log("Transfer", a.getId(), b.getId(), 600);

        b.Withdraw(400); // в пределах лимита
        manager.Log("Withdraw", b.getId(), b.getId(), 400);

        a.PrintInfo();
        b.PrintInfo();
    }
    catch (AccountException&) {
        cout << "Ошибка при работе с аккаунтом!" << endl;
    }

    manager.ShowLogs();

    return 0;
}

