#include <string>
#include <vector>
using namespace std;

enum ReservationStatus
{
    REQUESTED,
    PENDING,
    CONFIRMED,
    CHECKED_IN,
    CANCELED,
    ABANDONED
};

enum SeatType
{
    REGULAR,
    KID,
    ACCESSIBLE,
    OTHER
};

enum OrderStatus
{
    RECEIVED,
    PREPARING,
    COMPLETED,
    CANCELED,
    NONE
};

enum TableStatus
{
    FREE,
    RESERVED,
    OCCUPIED,
    OTHER
};

enum AccountStatus
{
    ACTIVE,
    CLOSED,
    CANCELED,
    BLACKLISTED,
    BLOCKED
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

// Person
class Person
{
protected:
    string name;
    string phone;

public:
    Person(const string &name, const string &phone)
        : name(name), phone(phone) {}
};

class Employee : public Person
{
protected:
    int employee_id;
    time_t date_join;

public:
    Employee(const string &name, const string &phone, const int id, time_t date)
        : Person(name, phone), employee_id(id), date_join(date) {}
};

class Receptionist : public Employee
{
public:
    Receptionist(const string &name, const string &phone, const int id, time_t date)
        : Employee(name, phone, id, date) {}

    void searchCustomer(string name)
    {
        //
    }

    void createReservation()
    {
        //
    }
};

class Manager : public Employee
{
public:
    Manager(const string &name, const string &phone, const int id, time_t date)
        : Employee(name, phone, id, date) {}

    void addEmployee(Employee e)
    {
        //
    }
};

class Chef : public Employee
{
public:
    Chef(const string &name, const string &phone, const int id, time_t date)
        : Employee(name, phone, id, date) {}

    void takeOrder(Order o)
    {
        //
    }
};

class Customer : public Person{
private:
    int customer_id;
public:
    Customer(const string &name, const string &phone, const int id, time_t date)
        : Person(name, phone), customer_id(id) {}
};

class TableSeat
{
private:
    int table_seat_number;
    SeatType type;

public:
    TableSeat(const int table_seat_number)
        : table_seat_number(table_seat_number), type(SeatType::REGULAR) {}
    void updateSeatType(SeatType seat_type)
    {
        type = seat_type;
    }
};

class Table
{
private:
    int table_id;
    int max_capacity;
    std::string location_identifier;
    TableStatus status = TableStatus::FREE;
    std::vector<TableSeat> seats;

public:
    Table(int id, int max_capacity, const std::string &location_identifier, TableStatus status = TableStatus::FREE)
        : table_id(id), max_capacity(max_capacity), location_identifier(location_identifier), status(status) {}

    bool isTableFree() const
    {
        return status == TableStatus::FREE;
    }

    void addReservation()
    {
        // Implementation for adding a reservation
    }

    std::vector<Table> search(int capacity, const std::time_t &start_time)
    {
        std::vector<Table> available_tables;
        // Logic to search tables by capacity and availability
        return available_tables;
    }
};

class Reservation
{
private:
    int reservation_id;
    int people_count;
    std::string notes;
    ReservationStatus status = ReservationStatus::REQUESTED;
    std::time_t time_of_reservation;
    std::time_t checkin_time;
    std::string customer;
    std::vector<Table> tables;
    std::vector<std::string> notifications;

public:
    Reservation(int id, int people_count, const std::string &notes, const std::string &customer)
        : reservation_id(id), people_count(people_count), notes(notes), customer(customer)
    {
        time_of_reservation = std::time(nullptr);
        checkin_time = std::time(nullptr);
    }

    void updatePeopleCount(int count)
    {
        people_count = count;
    }
};


class MealItem {
private:
    int meal_item_id;
    int quantity;

public:
    MealItem(int id, int quantity) 
        : meal_item_id(id), quantity(quantity) {}

    void updateQuantity(int new_quantity) {
        quantity = new_quantity;
    }
};

class Meal {
private:
    int meal_id;
    int seat;
    std::vector<MealItem> meal_items;

public:
    Meal(int id, int seat) : meal_id(id), seat(seat) {}

    void addMealItem(const MealItem& meal_item) {
        meal_items.push_back(meal_item);
    }
};

class Check {
public:
    Check() {
        // Check initialization
    }
};

class Order {
private:
    int order_id;
    OrderStatus order_status;
    std::time_t creation_time;
    std::vector<Meal> meals;
    int table;
    std::string waiter;
    std::string chef;
    Check check;

public:
    Order(int id, OrderStatus status, int table, const std::string& waiter, const std::string& chef)
        : order_id(id), order_status(status), table(table), waiter(waiter), chef(chef) {
        creation_time = std::time(nullptr); // Current time
    }

    void addMeal(const Meal& meal) {
        meals.push_back(meal);
    }

    void removeMeal(const Meal& meal) {
        // Logic to remove a meal from the list
        // Could use an identifier for `meal` to find and remove it
    }

    OrderStatus getStatus() const {
        return order_status;
    }

    void setStatus(OrderStatus status) {
        order_status = status;
    }
};
