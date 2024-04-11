# Behavioral Pattern

## Chain of Responsibility
### Intent
Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.
### Applicability
+ more than one object may handle a request, and the handler isn't known a priori. The handler should be ascertained automatically.
+ you want to issue a request to one of several objects without specifying the receiver explicitly.
+ the set of objects that can handle a request should be specified dynamically.
### Structure
![](./img/Chain%20of%20Responsibility.png)
### Participants
+ Handler (HelpHandler)
    - defines an interface for handling requests.
    - (optional)implements the successor link
+ ConcreteHandler (PrintButton, PrintDialog)
    - handles requests it is responsible for.
    - can access its successor.
    - if the ConcreteHandler can handle the request, it does so; otherwise it forwards the request to its successor.
+ Client
    - initiates the request to a ConcreteHandler object on the chain.
### [Sample Code](./code/Chain%20of%20Responsibility.cpp)

## Command (Action,Transaction)
### Intent
Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.
### Applicability
+ parameterize objects by an action to perform, as MenuItem objects did above. You can express such parameterization in a procedural language with a callback function, that is, a function that's registered somewhere to be called at a later point. Commands are an object-oriented replacement for callbacks.
+ specify, queue, and execute requests at different times. A Command object can have a lifetime independent of the original request. If the receiver of a request can be represented in an address space-independent way, then you can transfer a command object for the request to a different process and fulfill the request there.
+ support undo. ThecCommand's Execute operation can store state for reversing its effects in the command itself. The Command interface must have an added Unexecute operation that reverses the effects of a previous call to Execute. Executed commands are stored in a history list.Unlimited-level undo and redo is achieved by traversing this list backwards and forwards calling Unexecute and Execute,respectively.
+ support logging changes so that they can be reapplied in case of a system crash. By augmenting the Command interface with load and store operations, you can keep a persistent log of changes. Recovering from a crash involves reloading logged commands from disk and reexecuting them with the Execute operation.
+ structure a system around high-level operations built on primitives operations. Such a structure is common in informationsystems that support transactions. A transaction encapsulates a set of changes to data. The Command pattern offers a way to model transactions. Commands have a common interface, letting you invoke all transactions the same way. The pattern also makes it easy to extend the system with new transactions.
### Structure
![](./img/Command.png)
### Participants
+ Command
    - declares an interface for executing an operation.
+ ConcreteCommand (PasteCommand, OpenCommand)
    - defines a binding between a Receiver object and an action.
    - implements Execute by invoking the corresponding operation(s) on Receiver.
+ Client (Application)
    - creates a ConcreteCommand object and sets its receiver.
+ Invoker (Menultem)
    - asks the command to carry out the request
+ Receiver (Document, Application)
    - knows how to perform the operations associated with carrying out a request. Any class may serve as a Receiver.
### [Sample Code](./code/Command.cpp)

## Interpreter
### Intent
Given a language, define a represention forits grammar along with an interpreter that uses the representation to interpret sentences in the language.
### Applicability
Use the Interpreter pattern when there is a language to interpret, and you can represent statements in the language as abstract syntax trees. The Interpreter pattern works best when
• the grammar is simple. They can interpret expressions without building abstract syntax trees, which can save space and possibly time.
• efficiency is not a critical concern. The most efficient interpreters are usually not implemented by interpreting parse trees directly but by first translating them into another form. 
### Structure
![](./img/Interpreter.png)
### Participants
+ AbstractExpression (RegularExpression)
    - declares an abstract Interpret operation that is common to all nodes in the abstract syntax tree.
+ TerminalExpression (LiteralExpression)
    - implements an Interpret operation associated with terminal symbols in the grammar.
    - an instance is required for every terminal symbol in a sentence.
+ NonterminalExpression (AlternationExpression, RepetitionExpression, SequenceExpressions)
    - one such class is required for every rule R ::= R1R2...Rn in the grammar.
    - maintains instance variables of type AbstractExpression for each of the symbols R1 through Rn.
    - implements an Interpret operation for nonterminal symbols in the grammar. Interpret typically calls itself recursively on the variables representing R1 through Rn.
+ Context
    - contains information that's global to the interpreter.
+ Client
    - builds (or is given) an abstract syntax tree representing a particular sentence in the language that the grammar defines. The abstract syntax tree is assembled from instances of the NonterminalExpression and TerminalExpression classes.
    - invokes the Interpret operation
### [Sample Code](./code/Interpreter.cpp)

## Iterator (Cursor)
### Intent
Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
### Applicability
+ to access an aggregate object's contents without exposing its internal representation.
+ to support multiple traversals of aggregateobjects.
+ to provide a uniform interface for traversing different aggregate structures(that is, to support polymorphic iteration).
### Structure
![](./img/Iterator.png)
### Participants
+ Iterator
    - defines an interface for accessing and traversing elements.
+ Concretelterator
    - implements theIterator interface.
    - keeps track of the current position in the traversal of the aggregate.
+ Aggregate
    - defines an interface for creating an Iterator object.
+ ConcreteAggregate
    - implements the Iterator creation interface to return an instance of the proper Concretelterator.
### [Sample Code](./code/Iterator.cpp)

## Mediator
### Intent
Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.
### Applicability
+ a set of objects communicatein well-defined but complexways.The resulting interdependencies are unstructured and difficult to understand.
+ reusing an object is difficult because itrefers to and communicates with many other objects.
+ a behavior that's distributed between several classes should be customizable without a lot of subclassing.
### Structure
![](./img/Mediator.png)
### Participants
+ Mediator (DialogDirector)
    - defines an interface for communicating with Colleague objects.
+ ConcreteMediator (FontDialogDirector)
    - implements cooperative behavior bycoordinating Colleague objects.
    - knows andmaintains itscolleagues.
+ Colleague classes (ListBox, EntryField)
    - each Colleague class knows itsMediator object.
    - each colleague communicates with its mediator whenever it would have otherwise communicated with another colleague.
### [Sample Code](./code/Mediator.cpp)

## Memento (Token)
### Intent
Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.
### Applicability
+ snapshot of (some portion of) an object's state must be saved so that it can be restored to that state later, and
+ a direct interface to obtaining the state would expose implementation details and break the object's encapsulation.
### Structure
![](./img/Memento.png)
### Participants
+ Memento (SolverState)
    - stores internal state of the Originator object. The memento may store as much or as little of the originator's internal state as necessary at its originator's discretion.
    - protects against access by objects other than the originator. Mementos have effectively two interfaces. Caretaker sees a narrow interface to the Memento—it can only pass the memento to other objects. Originator, in contrast, sees a wide interface, one that lets it access all the data necessary to restore itself to its previous state. Ideally, only the originator that produced the memento would be permitted to access the memento's internal state.
+ Originator (ConstraintSolver)
    - creates a memento containing a snapshot of its current internal state.
    - uses the memento to restore its internal state.
+ Caretaker (undo mechanism)
    - is responsible for the memento's safekeeping.
    - never operates on or examines the contents of a memento.
### [Sample Code](./code/Memento.cpp)