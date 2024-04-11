class Composition {
public:
    Composition(Compositor*);
    void repair();
private:
    Compositor* _compositor;
    Component* _components;
    int _componentCount;
    int _lineWidth;
    int* _lineBreaks;

    int _lineCount;
};

class Compositor {
public:
    virtual int compose(
        int natural[], int stretch[], int shrink[],
        int componentCount, int lineWidth, int breaks[]
    ) = 0;
protected:
    Compositor();
};

void Composition::Repair(){
   Coord* natural;
   Coord* stretchability;
   Coord* shrinkability;
   int componentCount;
   int* breaks;

   // prepare the arrays with the desired component sizes
   // ...

   // determine where the breaks are:
   int breakCount;
   breakCount = _compositor->Compose(
       natural, stretchability, shrinkability,
       componentCount, _lineWidth, breaks
   );

   // lay out components according to breaks
   // ...
}

class SimpleCompositor : public Compositor{
public:
    SimpleCompositor();

    virtual int compose(
        int natural[], int stretch[], int shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};

class TeXCompositor : public Compositor{
public:
    TeXCompositor();

    virtual int compose(
        int natural[], int stretch[], int shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};

class ArrayCompositor : public Compositor{
public:
    ArrayCompositor();

    virtual int compose(
        int natural[], int stretch[], int shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};