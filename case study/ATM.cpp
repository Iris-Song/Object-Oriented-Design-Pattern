// http://borg.csueastbay.edu/~bhecker/CS-401/Examples/ATM%20Example/
#include <string>
#include <iostream>

enum TransactionType
{
    BALANCE_INQUIRY,
    DEPOSIT_CASH,
    DEPOSIT_CHECK,
    WITHDRAW,
    TRANSFER
};

enum TransactionStatus
{
    SUCCESS,
    FAILURE,
    BLOCKED,
    FULL,
    PARTIAL,
    NONE
};

class Card
{
private:
    std::string card_number;
    std::string customer_name;
    std::string card_expiry;
    int pin;

public:
    Card(const std::string &number, const std::string &name, const std::string &expiry, int p)
        : card_number(number), customer_name(name), card_expiry(expiry), pin(p) {}

    std::string getBillingAddress() const
    {
        // Placeholder implementation
        return "";
    }
};

class Account
{
protected:
    std::string account_number;
    double total_balance;
    double available_balance;

public:
    Account(const std::string &acc_num)
        : account_number(acc_num), total_balance(0.0), available_balance(0.0) {}

    double getAvailableBalance() const
    {
        return available_balance;
    }
};

class SavingAccount : public Account
{
private:
    double withdraw_limit;

public:
    SavingAccount(const std::string &acc_num, double limit)
        : Account(acc_num), withdraw_limit(limit) {}
};

class CheckingAccount : public Account
{
private:
    std::string debit_card_number;

public:
    CheckingAccount(const std::string &acc_num, const std::string &card_num)
        : Account(acc_num), debit_card_number(card_num) {}
};

class Customer
{
private:
    std::string name;
    std::string address;
    std::string email;
    std::string phone;
    std::string status;
    Card *card;
    Account *account;

public:
    Customer(const std::string &customer_name, const std::string &customer_address,
             const std::string &customer_email, const std::string &customer_phone,
             const std::string &customer_status)
        : name(customer_name), address(customer_address), email(customer_email),
          phone(customer_phone), status(customer_status), card(nullptr), account(nullptr) {}

    void makeTransaction(const std::string &transaction)
    {
        // Placeholder implementation
    }

    std::string getBillingAddress() const
    {
        // Placeholder implementation
        return "";
    }

    void setCard(Card *c)
    {
        card = c;
    }

    void setAccount(Account *acc)
    {
        account = acc;
    }
};

class DepositSlot
{
protected:
    double total_amount;

public:
    DepositSlot() : total_amount(0.0) {}

    double getTotalAmount() const
    {
        return total_amount;
    }

    virtual ~DepositSlot() {}
};

class CheckDepositSlot : public DepositSlot
{
public:
    double getCheckAmount() const
    {
        // Placeholder implementation
        return 0.0;
    }
};

class CashDepositSlot : public DepositSlot
{
public:
    void receiveDollarBill()
    {
        // Placeholder implementation
    }
};

class CashDispenser
{
private:
    int total_five_dollar_bills;
    int total_twenty_dollar_bills;

public:
    CashDispenser() : total_five_dollar_bills(0), total_twenty_dollar_bills(0) {}

    void dispenseCash(int amount)
    {
        // Placeholder implementation
    }

    bool canDispenseCash() const
    {
        // Placeholder implementation
        return false;
    }
};

class Keypad
{
public:
    std::string getInput() const
    {
        // Placeholder implementation
        return "";
    }
};

class Screen
{
public:
    void showMessage(const std::string &message) const
    {
        std::cout << message << std::endl;
    }

    std::string getInput() const
    {
        // Placeholder implementation
        return "";
    }
};

class Printer
{
public:
    void printReceipt(const std::string &transaction) const
    {
        // Placeholder implementation
    }
};

class CheckDeposit
{
public:
    CheckDeposit()
    {
        // Placeholder implementation
    }
};

class CashDeposit
{
public:
    CashDeposit()
    {
        // Placeholder implementation
    }
};

class Bank
{
private:
    std::string name;
    int bank_code;

public:
    Bank(const std::string &name, const int bank_code)
        : name(name), bank_code(bank_code) {}

    int GetBankCode()
    {
        return bank_code;
    }

    void addATM() {}
};

class ATM
{
private:
    int atm_id;
    std::string location;

    CashDispenser cash_dispenser;
    Keypad keypad;
    Screen screen;
    Printer printer;
    CashDeposit cash_deposit;
    CheckDeposit check_deposit;

public:
    ATM(const int id, const std::string &loc)
        : atm_id(id), location(loc), cash_dispenser(), keypad(), screen(), printer(), check_deposit(), cash_deposit() {}

    bool authenticateUser()
    {
        // Placeholder implementation
        return false;
    }

    void makeTransaction(const std::string &customer, Transaction transaction)
    {
        // Placeholder implementation
    }
};

class Transaction
{
protected:
    int id;
    time_t create_time;
    TransactionStatus status;

public:
    Transaction(const int id, const time_t create_time, TransactionStatus status)
        : id(id), create_time(create_time), status(status) {}

    virtual void makeTransaction() {}; // Pure virtual function making this an abstract class

    virtual ~Transaction() {} // Virtual destructor
};

class BalanceInquiry : public Transaction
{
private:
    std::string account_id;

public:
    BalanceInquiry(const int id, const time_t date, TransactionStatus stat, const std::string &acc_id)
        : Transaction(id, date, stat), account_id(acc_id) {}

    std::string getAccountId() const
    {
        return account_id;
    }
};

class Deposit : public Transaction
{
protected:
    double amount;

public:
    Deposit(const int id, const time_t date, const TransactionStatus stat, double amt)
        : Transaction(id, date, stat), amount(amt) {}

    double getAmount() const
    {
        return amount;
    }
};

class CheckDeposit : public Deposit {
private:
    std::string check_number;
    std::string bank_code;

public:
    CheckDeposit(const int id, const time_t date, const TransactionStatus stat, double amt,
                 const std::string& check_num, const std::string& bank)
        : Deposit(id, date, stat, amt), check_number(check_num), bank_code(bank) {}

    std::string getCheckNumber() const {
        return check_number;
    }
};

class CashDeposit : public Deposit {
private:
    double cash_deposit_limit;

public:
    CashDeposit(const int id, const time_t date, const TransactionStatus stat, double amt, double limit)
        : Deposit(id, date, stat, amt), cash_deposit_limit(limit) {}

    double getCashDepositLimit() const {
        return cash_deposit_limit;
    }
};

class Withdraw : public Transaction {
private:
    double amount;

public:
    Withdraw(const int id, const time_t date, const TransactionStatus stat, double amt)
        : Transaction(id, date, stat), amount(amt) {}

    double getAmount() const {
        return amount;
    }
};

class Transfer : public Transaction {
private:
    std::string destination_account_number;

public:
    Transfer(const int id, const time_t date, const TransactionStatus stat, const std::string& dest_acc_num)
        : Transaction(id, date, stat), destination_account_number(dest_acc_num) {}

    std::string getDestinationAccount() const {
        return destination_account_number;
    }
};