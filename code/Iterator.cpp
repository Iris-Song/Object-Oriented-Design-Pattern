// traverse list front to back
// List and Iterator interfaces
template <class Item>
class List{
public:
    List(long size = DEFAULT_LIST_CAPACITY);

    long Count() const;
    Item& Get(long index) const;
    // ...
};

template <class Item>
class Iterator{
public:
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
protected:
    Iterator();
};

// Iterator subclass implementations
template <class Item>
class ListIterator : public Iterator<Item>{
public:
    ListIterator(const List<Item>* aList);
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
    virtual Item CurrentItem() const;

private:
    const List<Item>* _list;
    long _current;
};

template <class Item>
ListIterator<Item>::ListIterator(
    const List<Item>* aList
) : _list(aList), _current(0){
}

template <class Item>
void ListIterator<Item>::First(){
    _current = 0;
}

template <class Item>
void ListIterator<Item>::Next(){
    _current++;
}

template <class Item>
bool ListIterator<Item>::IsDone() const{
    return _current >= _list->Count();
}

template <class Item>
Item ListIterator<Item>::CurrentItem() const{
    if(IsDone()){
        throw "IteratorOutOfBounds";
    }
    return _list->Get(_current);
}

// Using the iterators
void PrintEmployees(List<Employee*>& i){
    for(i.First(); !i.IsDone(); i.Next()){
        i.CurrentItem()->Print();
    }
}

// Since we have iteratorsfor both back-to-front and front-to-back traversals,
// we can reuse this operation to print the employees in both orders.
List<Employee*> employees;
// ...
ListIterator<Employee*> forward(employees);
ReverseListIterator<Employee*> backward(employees);

PrintEmployees(forward);
PrintEmployees(backward);

// a SkipList subclass of List
SkipList<Employee*>* employees;
// ...
SkipListIterator<Employee*> iterator(employees);
PrintEmployees(iterator);

//introduce AbstractList class, List and SkipList become subclass of AbstractList
template <class Item>
class AbstractList{
public:
    virtual Iterator<Item>* CreateIterator() const = 0;
    // ...
};

// List overrides CreateIterator to return a ListIterator
template <class Item>
Iterator<Item>* List<Item>::CreateIterator() const{
    return new ListIterator<Item>(this);
}

// we know that we have an AbstractList
AbstractList<Employee*>* employees;
// ...

Iterator<Employee*>* iterator = employees->CreateIterator();
PrintEmployees(iterator);
delete iterator;

// IteratorPtr act as a proxy for an Iterator
// It take care of cleaning up the Iterator when it goes out of scope
template <class Item>
class IteratorPtr{
public:
    IteratorPtr(Iterator<Item>* i) : _i(i) { }
    ~IteratorPtr() { delete _i; }
    Iterator<Item>* operator->() { return _i; }
    Iterator<Item>& operator*() { return *_i; }
private:
    // disallow copy and assignment to avoid 
    // multiple deletion of the same Iterator

    IteratorPtr(const IteratorPtr&);
    IteratorPtr& operator=(const IteratorPtr&);
private:
    Iterator<Item>* _i;
};

AbstractList<Employee*>* employees;
// ...
IteratorPtr<Employee*> iterator(employees->CreateIterator());
PrintEmployees(iterator);

// An internal iterator
template <class Item>
class ListTraverser{
public:
    ListTraverser(List<Item>& aList) : _list(aList);
    bool Traverse();
protected:
    virtual bool ProcessItem(const Item&) = 0;
private:
    ListIterator<Item> _iterator;  
};

template <class Item>
ListTraverser<Item>::ListTraverser(
    List<Item>& aList) : _iterator(aList){ }

template <class Item>
bool ListTraverser<Item>::Traverse(){
    bool result = false;

    for(
        _iterator.First(); 
        !_iterator.IsDone();
        _iterator.Next()){
            result = ProcessItem(_iterator.CurrentItem());
        
            if(result == false){
                break;
            }
    }
    return result;
}

class PrintEmployee : public ListTraverser<Employee*>{
public:
    PrintEmployee(List<Employee*>& aList) : 
        ListTraverser<Employee*>(aList),
        _total(n), _count(0){ }
protected:
    bool ProcessItem(Employee* const&);
private:
    int _total;
    int _count;
};

bool PrintEmployee::ProcessItem(Employee* const& e){
    _count++;
    e->Print();
    return _count < _total;
}

// prints the first 10 employees
PrintEmployees pa(employees, 10);
pa.Traverse();