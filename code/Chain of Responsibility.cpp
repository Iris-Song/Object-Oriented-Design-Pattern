//1. Implementing the sucssor chain

// 2.connecting successors
class HelpHandler {
public:
    HelpHandler(HelpHandler* s): _successor(s) {}
    virtual void HandleHelp();
private:
    HelpHandler* _successor;
};

void HelpHandler::HandleHelp() {
    if (_successor != 0) {
        _successor->HandleHelp();
    }
}

// 3.representing the results
// subclass can extend the dispatch by overriding the HandleRequest 
void Handler::HandleRequest(Request* theRequest) {
    switch (theRequest->GetRequest()) {
    {
    case Help:
        // cast argument to the appropriate type
        HandleHelp((HelpRequest*) theRequest);
        break;

    case Print:
        HandlePrint((PrintRequest*) theRequest);
        // ...
        break;
    }

    default:
        // ...
        break;
    }
}

class ExtendedHandler: public Handler {
public:
    virtual void HandleRequest(Request* theRequest);
    // ...
};

void ExtendedHandler::HandleRequest(Request* theRequest) {
    switch (theRequest->GetKind()) {
    {
    case Preview:
        //handle preview request
        break;
    
    default:
        // let Handler handle other request
        Handler::HandleRequest(theRequest);
    }
}

//4. automatically forwarding in Smalltalk