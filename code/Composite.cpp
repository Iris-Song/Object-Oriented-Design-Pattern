class Composite;

class Component {
public:
    // ...
    virtual Composite *GetComposite() { return 0;}
};

class Composite : public Component {
public:
    void Add(Component *);
    // ...
    virtual Composite *GetComposite() { return this; }
};

class Leaf : public Component {
    // ...
};

Composite* aComposite = new Composite;
Leaf* aLeaf = new Leaf;

Component* aComponent;
Composite* test;

aComponent = aComposite;
if (test = aComponent->GetComposite()) {
    test->Add(new Leaf);
}

aComponent = aLeaf;

if (test = aComponent->GetComposite()) {
    test->Add(new Leaf); // will not add leaf
}
