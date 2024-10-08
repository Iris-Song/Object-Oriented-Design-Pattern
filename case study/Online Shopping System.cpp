#include <string>
#include <vector>

using namespace std;

enum OrederStatus
{
    UNSHIPPED,
    PENDING,
    SHIPPED,
    COMPLETED,
    CANCELED,
    REFUND_APPLIED
};

enum AccountStatus
{
    ACTIVE,
    BLOCKED,
    BANNED,
    COMPROMISED,
    ARCHIVED,
    UNKNOWN
};

enum ShipmentStatus
{
    PENDING,
    SHIPPED,
    DELIVERED,
    ON_HOLD
};

enum PaymentStatus
{
    UNPAID,
    PENDING,
    COMPLETED,
    FILLED,
    DECLINED,
    CANCELLED,
    ABANDONED,
    SETTLING,
    SETTLED,
    REFUNDED
};

class ProductCategory
{
private:
    string name;
    string description;

public:
    ProductCategory(string name, string description)
        : name(name), description(description) {}
};

class Product
{
private:
    int ID;
    string name;
    string description;
    double price;
    int available_num;
    Account seller;
    ProductCategory category;

public:
    Product(int ID, string name, string description, double price,
            int available_num, Account seller, ProductCategory category)
        : ID(ID), name(name), description(description), price(price),
          available_num(available_num), seller(seller), category(category) {}

    void updatePrice(double new_price) { price = new_price; }
    int getAvailableNum() { return available_num; }
};

class ProductReview
{
private:
    int rating;
    string review;
    Account reviewer;

public:
    ProductReview(int rating, string review, Account reviewer);
};

class Item
{
private:
    int productID;
    int quantity;
    double price;

public:
    Item(int productID, double price)
        : productID(productID), quantity(1), price(price) {}

    void UpdateQuantity(int new_q) { quantity = new_q; }
};

class ShoppingCart
{
private:
    vector<Item> items;

public:
    ShoppingCart() { items = vector<Item>(); }
    void AddItem(Item it) { items.push_back(it); }
    void RemoveItem(Item it) { /*..*/ }
    void updateItem(Item it) { /*..*/ }
    vector<Item> GetItems() { return items; }
    void checkout() {}
};

class Order
{
    int ID;
    OrederStatus status;
    time_t createTime;
    vector<Item> items;

public:
    Order(int ID)
        : ID(ID), status(OrederStatus::PENDING), createTime(/*nowtime*/) {}
    void sendForShip() { status = OrederStatus::SHIPPED; /*...*/ }
    void makePayment() {}
};

class CreditCard;

class Account
{
protected:
    string username;
    string password;
    string name;
    string email;
    string phone;
    string address;
    AccountStatus status;
    vector<CreditCard> creditCard;

public:
    Account(string username, string password, string name, string email, string phone, string address)
        : username(username), password(password), name(name), email(email), phone(phone), address(address),
          status(ACTIVE) {}

    virtual void addProduct(Product p) {}
    void addProductReview(ProductReview) {}
    void reset_password(string new_password) { password = new_password; }
};

class Customer : public Account
{
protected:
    ShoppingCart cart;
    vector<Order> orders;

public:
    ShoppingCart GetShoppingCart() { return cart; }
    void addProductToCart(Item it) { cart.AddItem(it); }
    void removeProductFromCart(Item it) { cart.RemoveItem(it); }
    void placeOrder() {};
    virtual ~Customer() {};
};

class Guest : public Customer
{
public:
    void registerAccount() {}
};

class Member : public Customer
{
public:
    void placeOrder() {}
};

class Shipment
{
private:
    int shipmentID;
    time_t shipTime;
    time_t estimnateArriveTime;

public:
    Shipment() {}
};

class Notification
{
private:
    int ID;
    std::string content;
    time_t createTime;

public:
    Notification() {}
};
