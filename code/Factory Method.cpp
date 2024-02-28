class Product{
    //...
};

class Creator {
public:
    Product* GetProduct();
protected:
    virtual Product* CreateProduct();
private:
    Product* _product;
};

Product* Creator::GetProduct() {
    if (_product == 0 ) {
        _product = CreateProduct();
    }
    return _product;
}

// Using templates to avoid subclassing
template <class TheProduct>
class StandardCreator: public Creator {
public:
    virtual Product* CreateProduct();
};

template <class TheProduct>
Product* StandardCreator<TheProduct>::CreateProduct () {
    return new TheProduct;
}

class MyProduct : public Product {
public:
    MyProduct();
    // . . .
};
StandardCreator<MyProduct> myCreator;