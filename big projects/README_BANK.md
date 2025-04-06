# 🏦 BankSim — Банковская система на C++ без STL

**BankSim** — это учебный мини-проект на чистом C++, моделирующий работу банковской системы с поддержкой различных типов счетов, транзакций и исключений. Все структуры данных реализованы вручную — **без использования STL**.

---

## 🚀 Цель проекта

- Продемонстрировать объектно-ориентированное программирование в C++:
  - **Абстрактные классы**
  - **Наследование**
  - **Полиморфизм**
  - **Иерархия исключений**
- Укрепить навыки **работы с указателями**, динамической памятью (`new/delete`) и строками (`char*`)
- Избежать использования стандартной библиотеки STL: никаких `vector`, `string`, `map` и т.д.

---

## 🧱 Архитектура проекта

             Account (абстрактный)
            /        |           \
  SavingsAccount  CreditAccount  InvestmentAccount
     
           ↑                   ↑
     Поведение при:        Комиссии, лимиты,
   пополнении/снятии       проценты, штрафы

           TransactionManager
           |     Хранит лог операций
      Transaction* logs[1000];
---

## 🔐 Основные классы

### `Account` (абстрактный)
```cpp
class Account {
public:
    virtual void Deposit(double amount);
    virtual void Withdraw(double amount) = 0;
    virtual void TransferTo(Account* target, double amount);
    virtual void PrintInfo() const;
    virtual ~Account();
};

### `Account` (абстрактный)
class AccountException {};
class InsufficientFundsException : public AccountException {};
class TransactionLimitExceededException : public AccountException {};
class InvalidAccountException : public AccountException {};
class NullPointerException : public AccountException {};

int main() {
    try {
        SavingsAccount a("Alice", 1001, 500);
        CreditAccount b("Bob", 1002, 200, 300);

        a.Deposit(200);
        a.TransferTo(&b, 600);  // выбросит исключение

        b.Withdraw(400); // в пределах лимита
    }
    catch (AccountException& ex) {
        std::cout << "Ошибка при работе с аккаунтом!\n";
    }

    return 0;
}

