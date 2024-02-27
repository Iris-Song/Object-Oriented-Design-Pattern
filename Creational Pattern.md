# Creational Pattern
abstract instantiation process


## Abstract Factory (Kit)
### Intent
provide an interface for creating families of related or dependent objects without specifying their concrete classes.
### Applicability
+ a system should be independent of how its products are created, composed, and represented
+ a system should be configured with one of multiple families of product
+ a family of related product objects is designed to be used together, and you need to enforce this constraint
+ you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations
### Structure
![](./img/Abstract%20Factory.png)
### Participants
+ AbstractFactory
+ ConcreteFactory
+ AbstractProduct
+ ConcreteProduct
+ Client
### [Sample Code](https://github.com/Iris-Song/Object-Oriented-Design-Pattern/blob/main/code/Abstract%20Factory.cpp)

## Builder
### Intent
seperate the construction of a complex object from its representation so that the same construction process can create different representations. 
### Applicability
+ the algorithm for creating a complex object should be independent of the parts that make up the object and how they are assembled.
+ the construction process must allow different representations for the object that's constructed.
### Structure
![](./img/Builder.png)
### Participants
+ Builder (TextConverter)
+ ConcreteBuilder (ASCIIConverter, TeXConverter, TextWidgetConverter)
+ Director (RTFReader)
+ Product (ASCIIText, TeXText, TextWidget)
### Collaborations
![](./img/Builder%20Co.png)
### [Sample Code](./code/Builder.cpp)
