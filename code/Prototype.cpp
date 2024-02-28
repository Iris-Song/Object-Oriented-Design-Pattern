enum Direction { North, South, East, West};

class MapSite{
public:
    virtual void Enter() = 0;    
};

class Room : public MapSite {
public:
    Room(int roomNo);

    MapSite* GetSide(Direction) const;
    void SetSide(Direction, MapSite*);

    virtual void Enter();

private:
    MapSite* _sides[4];
    int _roomNumber;
};

class Wall : public MapSite {
public:
    Wall();

    virtual void Enter();
};

class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0);

    virtual void Initialize(Room*, Room*);
    virtual Door* Clone() const;
    virtual void Enter();
    Room* OtherSideFrom(Room*);

private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};

class Maze{
public:
    Maze();

    void AddRoom(Room*);
    Room* RoomNo(int) const;
private:
    // ...
};

void Door::Initialize (Room* rl, Room* r2) {
    _room1 = rl;
    _room2 = r2;
}

Door* Door::Clone () const {
    return new Door(*this);
}

// MazeFactory can create component of maze
class MazeFactory{
public:
    MazeFactory();

    virtual Maze* MakeMaze() const
        {return new Maze;}
    virtual Wall* MakeWall() const
        {return new Wall;}
    virtual Room* MakeRoom(int n) const
        {return new Room(n);}
    virtual Door* MakeDoor(Room* r1, Room* r2) const
        {return new Door(r1,r2);}
};

// MazePrototypeFactory will be initialized with prototypes of the
//objects it will create so that we don't have to subclass it just to change the classes
//of walls or rooms it creates.
class MazePrototypeFactory : public MazeFactory {
public:
    MazePrototypeFactory (Maze*, Wall*, Room*, Door*);

    virtual Maze* MakeMaze() const;
    virtual Room* MakeRoom(int) const;
    virtual Wall* MakeWall() const;
    virtual Door* MakeDoor(Room*, Room*) const;

private:
    Maze* _prototypeMaze;
    Room* _prototypeRoom;
    Wall* _prototypeWall;
    Door* _prototypeDoor;
};

MazePrototypeFactory::MazePrototypeFactory (
Maze* m, Wall* w, Room* r, Door* d
) {
    _prototypeMaze = m;
    _prototypeWall = w;
    _prototypeRoom = r;
    _prototypeDoor = d;
}

Wall* MazePrototypeFactory::MakeWall () const {
    return _prototypeWall->Clone();
}

Door* MazePrototypeFactory::MakeDoor (Room* rl, Room *r2) const {
    Door* door = _prototypeDoor->Clone();
    door->Initialize(rl, r2);
    return door;
}

class BombedWall : public Wall {
public:
    BombedWall();
    BombedWall(const BombedWall&);

    virtual Wall* Clone() const;
    bool HasBomb();
private:
    bool _bomb;
};

BombedWall::BombedWall(const BombedWall& other) : Wall(other) {
    _bomb = other._bomb;
}

Wall* BombedWall::Clone () const {
    return new BombedWall(*this);
}