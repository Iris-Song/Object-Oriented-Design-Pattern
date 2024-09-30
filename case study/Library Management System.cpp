#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <map>
#include <algorithm>

enum BookFormat
{
    EBOOK,
    AUDIOBOOK,
    HARDCOVER
};

enum BookStatus
{
    AVAILABLE,
    RESERVED,
    LOANED,
    LOST
};

enum ReservationStatus
{
    PENDING,
    CANCELED,
    COMPLETED
};

enum AccountStatus
{
    ACTIVE,
    CLOSED,
    CANCELED,
    BLACKLISTED,
    NONE
};

enum FineStatus
{
    PENDING,
    CANCELED,
    PAID
};

const int MAX_BOOKS_ISSUED_TO_A_USER = 5;
const int MAX_LENDING_DAYS = 10;

class Book
{
protected:
    std::string ISBN;
    std::string title;
    std::string subject;
    std::string publisher;
    std::vector<std::string> author;
    int pages;

public:
    Book(const std::string &ISBN, const std::string &title, const std::string &subject, const std::string &publisher,
         const std::vector<std::string> &author, const int pages)
        : ISBN(ISBN), title(title), subject(subject), publisher(publisher),
          author(author), pages(pages) {}

    virtual ~Book() = default;
};

class BookItem : public Book
{
private:
    std::string barcode;
    bool isReferenceOnly;
    std::tm dueDate;
    double price;
    BookFormat format;
    BookStatus status;

public:
    BookItem(const std::string &ISBN, const std::string &title, const std::string &subject, const std::string &publisher,
             const std::vector<std::string> &author, const int pages, const std::string &barcode, bool isReferenceOnly,
             double price, BookFormat format, BookStatus status = BookStatus::AVAILABLE)
        : Book(ISBN, title, subject, publisher, author, pages), barcode(barcode), isReferenceOnly(isReferenceOnly),
          dueDate(), price(price), format(format), status(status) {}

    std::string GetBarcode()
    {
        return barcode;
    }

    bool checkout(const std::string &memberID)
    {
        if (isReferenceOnly)
        {
            std::cout << "The book is Reference only and can't be issued" << std::endl;
            return false;
        }
        if (!LoanRecord::loanBook(GetBarcode(), memberID))
            return false;
        updateBookItemStatus(BookStatus::LOANED);
        return true;
    }

    void returnBook()
    {
        updateBookItemStatus(BookStatus::AVAILABLE);
    }

    void updateBookItemStatus(BookStatus status)
    {
        this->status = status;
    }

    void updateDueDate()
    {   
        std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now() + std::chrono::hours(24 * MAX_LENDING_DAYS);
        std::time_t timeT = std::chrono::system_clock::to_time_t(timePoint);

        // Convert the time_t to a std::tm structure
        std::tm* tmStruct = std::localtime(&timeT);
        dueDate = *tmStruct;
    }
};

class LoanRecordDB
{
private:
    static std::unordered_map<std::string, LoanRecord *> db;

public:
    static LoanRecord *fetchLoanDetails(std::string book_barcode)
    {
        // find record in DB
        if (db.find(book_barcode) == db.end())
            return nullptr;
        LoanRecord *ptr = db[book_barcode];
        return ptr;
    }

    static bool Insert(LoanRecord *br)
    {
        if (!br || db.find(br->GetBarcode()) != db.end())
        {
            return false;
        }
        db[br->GetBarcode()] = br;
        return true;
    }
};

class LoanRecord
{
private:
    std::tm createDate;
    std::tm dueDate;
    std::tm returnDate;
    std::string book_barcode;
    std::string member_id;

public:
    LoanRecord(int loanDay, std::string book_barcode, std::string member_id)
        : returnDate(), book_barcode(book_barcode), member_id(member_id)
    {
        if (loanDay >= MAX_LENDING_DAYS)
        {
            std::cout << "cannot loan more than " << MAX_LENDING_DAYS << " days!\n";
            return; // exit(-1) or some error
        }
        time_t t = time(0);
        createDate = *localtime(&t);

        // Calculate dueDate using std::chrono
        std::time_t dueTime = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now() + std::chrono::hours(24 * loanDay));

        // Convert back to std::tm
        dueDate = *std::localtime(&dueTime);
    }

    std::tm GetDueDate()
    {
        return dueDate;
    }

    std::string GetBarcode()
    {
        return book_barcode;
    }

    static bool loanBook(std::string book_barcode, std::string member_id)
    {
        // change xx
        return true;
    }

    void fetchLoanDetails()
    {
        // std::cout<<...
    }
};

class BookReservationDB
{
private:
    // using hashtable to implement easy
    static std::unordered_map<std::string, BookReservation *> db;

public:
    static BookReservation *fetchReservationDetails(std::string book_barcode)
    {
        // find record in DB
        if (db.find(book_barcode) == db.end())
            return nullptr;
        BookReservation *ptr = db[book_barcode];
        return ptr;
    }

    static bool Insert(BookReservation *br)
    {
        if (!br || db.find(br->GetBarcode()) != db.end())
        {
            return false;
        }
        db[br->GetBarcode()] = br;
        return true;
    }
};

class BookReservation
{
private:
    std::tm createDate;
    std::string book_barcode;
    std::string member_id;
    ReservationStatus status;

public:
    BookReservation(std::string book_barcode, std::string member_id, ReservationStatus status = ReservationStatus::PENDING)
        : book_barcode(book_barcode), member_id(member_id), status(status)
    {
        time_t t = time(0);
        createDate = *localtime(&t);
    }

    std::string GetMemberID()
    {
        return member_id;
    }

    std::string GetBarcode()
    {
        return book_barcode;
    }

    void updateStatus(ReservationStatus status)
    {
        this->status = status;
    }

    void sendBookAvailableNotification()
    {
        // ...
    }
};

class FineDB
{
private:
    // using hashtable to implement easy
    static std::unordered_map<std::string, Fine *> db;

public:
    static void collectFine(std::string barcode, int duedate)
    {
        //...
    }
};

class Fine
{
private:
    std::tm createDate;
    std::string book_barcode;
    std::string member_id;
    FineStatus status;

public:
    Fine(std::string book_barcode, std::string member_id, FineStatus status = FineStatus::PENDING)
        : book_barcode(book_barcode), member_id(member_id), status(status)
    {
        time_t t = time(0);
        createDate = *localtime(&t);
    }
};

// abstarct Person class
class Person
{
protected:
    std::string name;
    std::string email;
    std::string phone;

public:
    Person(const std::string &name, const std::string &email, const std::string &phone)
        : name(name), email(email), phone(phone) {}

    virtual ~Person() {}
};

// abstarct Account class
class Account
{
protected:
    std::string id;
    std::string password;
    AccountStatus accountStatus;
    Person *person;

public:
    Account(const std::string &id, const std::string &password, Person *person, AccountStatus status = AccountStatus::ACTIVE)
        : id(id), password(password), accountStatus(status), person(person) {}

    virtual ~Account() = default;

    void virtual resetPassword() {}

    std::string GetID()
    {
        return id;
    }
};

// Librarian class inheriting from Account
class Librarian : public Account
{
public:
    Librarian(const std::string &id, const std::string &password, Person *person, AccountStatus status = AccountStatus::ACTIVE)
        : Account(id, password, person, status) {}

    void addBookItem(BookItem *book_item)
    {
        // Logic for adding book item
    }

    void blockMember(Account *member)
    {
        // Logic for blocking member
    }

    void unblockMember(Account *member)
    {
        // Logic for unblocking member
    }
};

class Member : public Account
{
private:
    std::tm date_of_membership;
    int total_books_checkout;

public:
    Member(const std::string &id, const std::string &password, Person *person, AccountStatus status = AccountStatus::ACTIVE)
        : Account(id, password, person, status), total_books_checkout(0)
    {
        time_t t = time(0);
        date_of_membership = *localtime(&t);
    }

    const int getTotalBooksCheckedOut()
    {
        return total_books_checkout;
    }

    bool reserveBookItem(BookItem *book_item)
    {
        // Logic for reserving book
        BookReservation *br = new BookReservation(book_item->GetBarcode(), id);
        return BookReservationDB::Insert(br);
    }

    bool checkoutBookItem(BookItem *book_item)
    {
        if (total_books_checkout >= MAX_BOOKS_ISSUED_TO_A_USER)
        {
            std::cout << "The user has already checked out the maximum number of books\n";
            return false;
        }

        auto book_reservation = BookReservationDB::fetchReservationDetails(book_item->GetBarcode());

        if (book_reservation != nullptr && book_reservation->GetMemberID() != this->id)
        {
            std::cout << "This book is reserved by another member\n";
            return false;
        }
        else if (book_reservation != nullptr)
        {
            book_reservation->updateStatus(ReservationStatus::COMPLETED);
        }
        if (!book_item->checkout(this->GetID()))
            return false;

        incrementTotalBooksCheckedOut();
        return true;
    }

    void checkoutFine(std::string barcode)
    {
        LoanRecord *lr = LoanRecordDB::fetchLoanDetails(barcode);
        if (!lr)
        {
            std::cout << "No loan record has been found!" << std::endl;
            return;
        }

        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        auto due_time_t = std::mktime(&lr->GetDueDate());
        if (due_time_t < now_time_t)
        {
            int diff_days = (std::difftime(now_time_t, due_time_t) / (60 * 60 * 24));
            FineDB::collectFine(this->id, diff_days);
        }
        else
        {
            std::cout << "Before due date, no need to pay fine!" << std::endl;
            return;
        }
    }

    void returnBookItem(BookItem *book_item)
    {
        checkoutFine(book_item->GetBarcode());

        auto book_reservation = BookReservationDB::fetchReservationDetails(book_item->GetBarcode());

        if (book_reservation != nullptr)
        {
            book_item->updateBookItemStatus(BookStatus::RESERVED);
            book_reservation->sendBookAvailableNotification();
        }
        else
        {
            book_item->updateBookItemStatus(BookStatus::AVAILABLE);
        }

        decrementTotalBooksCheckedOut();
    }

    bool renewBookItem(BookItem* book_item) {
        checkoutFine(book_item->GetBarcode());

        auto book_reservation = BookReservationDB::fetchReservationDetails(book_item->GetBarcode());

        if (book_reservation != nullptr && book_reservation->GetMemberID() != this->id) {
            std::cout << "This book is reserved by another member\n";
            decrementTotalBooksCheckedOut();
            book_item->updateBookItemStatus(BookStatus::RESERVED);
            book_reservation->sendBookAvailableNotification();
            return false;
        } else if (book_reservation != nullptr) {
            book_reservation->updateStatus(ReservationStatus::COMPLETED);
        }

        if (!LoanRecord::loanBook(book_item->GetBarcode(), this->id)){
            return false;
        };
        book_item->updateDueDate();

        return true;
    }

private:
    void incrementTotalBooksCheckedOut()
    {
        total_books_checkout++;
    }

    void decrementTotalBooksCheckedOut()
    {
        total_books_checkout--;
    }
};

// Abstract base class Search
class Search {
public:
    virtual std::vector<std::string> searchByTitle(const std::string& title) = 0;
    virtual std::vector<std::string> searchByAuthor(const std::string& author) = 0;
    virtual std::vector<std::string> searchBySubject(const std::string& subject) = 0;
    virtual std::vector<std::string> searchByPubDate(const std::string& publish_date) = 0;
    virtual ~Search() {}
};

// Catalog class that implements Search
class Catalog : public Search {
private:
    std::map<std::string, std::vector<std::string>> bookTitles;  // key: title, value: list of book IDs
    std::map<std::string, std::vector<std::string>> bookAuthors; // key: author, value: list of book IDs
    std::map<std::string, std::vector<std::string>> bookSubjects; // key: subject, value: list of book IDs
    std::map<std::string, std::vector<std::string>> bookPublicationDates; // key: publication date, value: list of book IDs

public:
    // Constructor
    Catalog() {}

    // Add books to the catalog (for demonstration purposes)
    void addBook(const std::string& bookID, const std::string& title, const std::string& author, const std::string& subject, const std::string& pubDate) {
        bookTitles[title].push_back(bookID);
        bookAuthors[author].push_back(bookID);
        bookSubjects[subject].push_back(bookID);
        bookPublicationDates[pubDate].push_back(bookID);
    }

    // Search by title
    std::vector<std::string> searchByTitle(const std::string& query) override {
        return bookTitles.count(query) ? bookTitles[query] : std::vector<std::string>();
    }

    // Search by author
    std::vector<std::string> searchByAuthor(const std::string& query) override {
        return bookAuthors.count(query) ? bookAuthors[query] : std::vector<std::string>();
    }

    // Search by subject
    std::vector<std::string> searchBySubject(const std::string& query) override {
        return bookSubjects.count(query) ? bookSubjects[query] : std::vector<std::string>();
    }

    // Search by publication date
    std::vector<std::string> searchByPubDate(const std::string& query) override {
        return bookPublicationDates.count(query) ? bookPublicationDates[query] : std::vector<std::string>();
    }
};