class State;

class Originator {
public:
    Memeto *CreateMemento();
    void SetMemento(Memento*);
    // ...
private:
    State* _state; // internal data structure
    // ...
};

class Memento {
public:
    // narrow public interface
    virtual ~Memento();
private:
    // private members accessible only to Originator
    friend class Originator;
    Memento();

    void SetState(State*);
    State* GetState();
    // ...
private:
    State* _state;
    // ...
};