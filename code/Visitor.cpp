class Visitor {
public:
    virtual void visitElementA(ElementA* element);
    virtual void visitElementB(ElementB* element);

    // and so on for other concrete elements
protected:
    Visitor();
};

class Element {
public:
    virtual ~Element();
    virtual void Accept(Visitor&) = 0;
protected:
    Element();
};

class ElementA : public Element {
public:
    ElementA();
    virtual void Accept(Visitor& v){
        v.visitElementA(this);
    }
};

class ElementB : public Element {
public:
    ElementB();
    virtual void Accept(Visitor& v){
        v.visitElementB(this);
    }
};

class CompositeElement : public Element {
public:
    virtual void Accept(Visitor& v);
private:
    List<Element*>* _children;
};

void CompositeElement::Accept(Visitor& v){
    ListIterator<Element*> i(_children);

    for(i.First(); !i.IsDone(); i.Next()){
        i.CurrentItem()->Accept(v);
    }
    v.VisitCompositeElement(this);
}
        