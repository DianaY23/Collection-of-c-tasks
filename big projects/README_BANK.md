# 🏦 BankSim — Мини-банковская система на C++ (без STL)

## 📋 Условие задачи

Реализовать учебную банковскую систему **на чистом C++**, демонстрирующую принципы **объектно-ориентированного программирования** и **ручное управление памятью**. Все структуры данных и строки реализуются вручную — **без использования STL**.

---

## 🔧 Основные требования

### 1. Абстрактный базовый класс `Account`
- Поля:
  - `char* ownerName`
  - `int accountId`
  - `double balance`
- Методы:
  - `Deposit(double amount)`
  - `Withdraw(double amount)` — чисто виртуальный
  - `TransferTo(Account* target, double amount)`
  - `PrintInfo() const`

---

### 2. Наследники
- `SavingsAccount` — сберегательный счёт, не допускает перерасход
- `CreditAccount` — допускает перерасход в пределах кредитного лимита
- *(опционально)* `InvestmentAccount` — инвестиционный счёт с доходностью

---

### 3. Обработка ошибок через исключения

```cpp
class AccountException {};
class InsufficientFundsException : public AccountException {};
class TransactionLimitExceededException : public AccountException {};
class InvalidAccountException : public AccountException {};
class NullPointerException : public AccountException {};

