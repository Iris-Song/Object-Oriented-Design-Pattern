class Singelton{
public:
    static void Register(const char* name, Singelton*);
    static Singelton* Instance();
protected:
    static Singelton* Lookup(const char* name);
private:
    static Singelton* _instance;
    static List<NameSingletonPair>* _registry;
};

Singelton* Singelton::Instance(){
    if(_instance == 0){
        const char* singeltonName = getenv("SINGLETON");
        //user or environment supplies at startup

        _instance = Lookup(singeltonName);
        // Lookup returns 0 if there's no instance
    }
    return _instance;
}

MySingleton::MySingleton() {
    // . . .
    Singleton::Register("MySingleton", this);
}