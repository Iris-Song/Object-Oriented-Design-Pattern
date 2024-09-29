#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

enum VehicleType
{
    MOTORCYCLE,
    CAR,
    TRUCK,
    VAN,
    BUS
};

enum ParkingSpotType
{
    SMALL_PARKING_SPOT,
    MEDIUM_PARKING_SPOT,
    LARGE_PARKING_SPOT,
    SUPER_LARGE_PARKING_SPOT
};

class ParkingTicket
{
public:
    void saveInDB()
    {
        // Mock implementation
        std::cout << "Ticket saved in DB.\n";
    }
    int getTicketNumber() const
    {
        // Return a mock ticket number
        return 1;
    }
};

class Vehicle
{
private:
    std::string license;
    VehicleType vehicleType;
    ParkingTicket ticket;

public:
    std::string GetLicense()
    {
        return license;
    }

    VehicleType GetVehicleType()
    {
        return vehicleType;
    }

    void assignTicket(const ParkingTicket &tkt)
    {
        ticket = tkt;
    }
};

// ParkingSpot: Here is the definition of ParkingSpot and all of its children classes:
class ParkingSpot
{
private:
    int number;
    bool isOccupied;
    std::shared_ptr<Vehicle> vehicle;
    ParkingSpotType parkingSpotType;

public:
    ParkingSpot(int number, ParkingSpotType parkingSpotType)
    {
        this->number = number;
        this->isOccupied = false;
        this->vehicle = nullptr;
        this->parkingSpotType = parkingSpotType;
    }

    int GetNumber()
    {
        return number;
    }

    bool IsOccupied()
    {
        return isOccupied;
    }

    ParkingSpotType GetType()
    {
        return parkingSpotType;
    }

    void SetVehicle(std::shared_ptr<Vehicle> vehicle)
    {
        this->vehicle = vehicle;
        isOccupied = true;
    }

    void RemoveVehicle()
    {
        this->vehicle = nullptr;
        isOccupied = false;
    }

    virtual ~ParkingSpot()
    {
        this->vehicle = nullptr;
    }
};

class SmallParkingSpot : public ParkingSpot
{
public:
    SmallParkingSpot(int number)
        : ParkingSpot(number, SMALL_PARKING_SPOT) {}
};

class MediumParkingSpot : public ParkingSpot
{
public:
    MediumParkingSpot(int number)
        : ParkingSpot(number, MEDIUM_PARKING_SPOT) {}
};

class LargeParkingSpot : public ParkingSpot
{
public:
    LargeParkingSpot(int number)
        : ParkingSpot(number, LARGE_PARKING_SPOT) {}
};

class SuperLargeParkingSpot : public ParkingSpot
{
public:
    SuperLargeParkingSpot(int number)
        : ParkingSpot(number, SUPER_LARGE_PARKING_SPOT) {}
};

// ParkingDisplayBoard: This class encapsulates a parking display board
class ParkingDisplayBoard
{
private:
    std::shared_ptr<SmallParkingSpot> smallParkingSpot;
    std::shared_ptr<MediumParkingSpot> mediumParkingSpot;
    std::shared_ptr<LargeParkingSpot> largeParkingSpot;
    std::shared_ptr<SuperLargeParkingSpot> superLargeParkingSpot;

public:
    ParkingDisplayBoard(std::shared_ptr<SmallParkingSpot> smallSpot,
                        std::shared_ptr<MediumParkingSpot> mediumSpot,
                        std::shared_ptr<LargeParkingSpot> largeSpot,
                        std::shared_ptr<SuperLargeParkingSpot> superLargeSpot)
        : smallParkingSpot(smallSpot), mediumParkingSpot(mediumSpot),
          largeParkingSpot(largeSpot), superLargeParkingSpot(superLargeSpot) {}

    int GetFreeSpotNumber(ParkingSpotType spotType)
    {
        switch (spotType)
        {
        case SMALL_PARKING_SPOT:
            return smallParkingSpot->GetNumber();
        case MEDIUM_PARKING_SPOT:
            return mediumParkingSpot->GetNumber();
        case LARGE_PARKING_SPOT:
            return largeParkingSpot->GetNumber();
        case SUPER_LARGE_PARKING_SPOT:
            return superLargeParkingSpot->GetNumber();
        default:
            std::cout << "Wrong parking spot type!" << std::endl;
            return -1;
        }
    }

    void SetFreeSpotNumber(std::shared_ptr<ParkingSpot> spot)
    {
        switch (spot->GetType())
        {
        case SMALL_PARKING_SPOT:
            smallParkingSpot = std::dynamic_pointer_cast<SmallParkingSpot>(spot);
            break;
        case MEDIUM_PARKING_SPOT:
            mediumParkingSpot = std::dynamic_pointer_cast<MediumParkingSpot>(spot);
            break;
        case LARGE_PARKING_SPOT:
            largeParkingSpot = std::dynamic_pointer_cast<LargeParkingSpot>(spot);
            break;
        case SUPER_LARGE_PARKING_SPOT:
            superLargeParkingSpot = std::dynamic_pointer_cast<SuperLargeParkingSpot>(spot);
            break;
        default:
            std::cout << "Wrong parking spot type!" << std::endl;
            break;
        }
    }

    void showEmptySpotNumber()
    {
        std::string message;
        if (smallParkingSpot->IsOccupied())
        {
            message += "small parking spot is full";
        }
        else
        {
            message += "Free small parking spot" + std::to_string(smallParkingSpot->GetNumber());
        }
        message += "\n";

        if (mediumParkingSpot->IsOccupied())
        {
            message += "medium parking spot is full";
        }
        else
        {
            message += "Free medium parking spot" + std::to_string(mediumParkingSpot->GetNumber());
        }
        message += "\n";

        if (largeParkingSpot->IsOccupied())
        {
            message += "large parking spot is full";
        }
        else
        {
            message += "Free large parking spot" + std::to_string(largeParkingSpot->GetNumber());
        }
        message += "\n";

        if (superLargeParkingSpot->IsOccupied())
        {
            message += "super large parking spot is full";
        }
        else
        {
            message += "Free super large parking spot" + std::to_string(superLargeParkingSpot->GetNumber());
        }
        message += "\n";

        std::cout << message;
    }
};

// ParkingFloor: This class encapsulates a parking floor:
class ParkingFloor
{
private:
    std::string name;
    std::unordered_map<int, std::shared_ptr<ParkingSpot> > smallParkingSpots;
    std::unordered_map<int, std::shared_ptr<ParkingSpot> > mediumParkingSpots;
    std::unordered_map<int, std::shared_ptr<ParkingSpot> > largeParkingSpots;
    std::unordered_map<int, std::shared_ptr<ParkingSpot> > suplerLargeParkingSpots;

    int free_small_spot_count;
    int free_medium_spot_count;
    int free_large_spot_count;
    int free_super_large_spot_count;

    ParkingDisplayBoard displayBoard;

public:
    ParkingFloor(const std::string &name, int small_spot_count, int medium_spot_count, int large_spot_count, int super_large_spot_count)
        : name(name),
          free_small_spot_count(small_spot_count),
          free_medium_spot_count(medium_spot_count),
          free_large_spot_count(large_spot_count),
          free_super_large_spot_count(super_large_spot_count),
          displayBoard( // Initialize displayBoard in the initializer list
              std::make_shared<SmallParkingSpot>(0),
              std::make_shared<MediumParkingSpot>(0),
              std::make_shared<LargeParkingSpot>(0),
              std::make_shared<SuperLargeParkingSpot>(0))
    {
    }

    void AddParkingSpot(std::shared_ptr<ParkingSpot> spot)
    {
        switch (spot->GetType())
        {
        case SMALL_PARKING_SPOT:
            smallParkingSpots[spot->GetNumber()] = spot;
            break;
        case MEDIUM_PARKING_SPOT:
            mediumParkingSpots[spot->GetNumber()] = spot;
            break;
        case LARGE_PARKING_SPOT:
            largeParkingSpots[spot->GetNumber()] = spot;
            break;
        case SUPER_LARGE_PARKING_SPOT:
            suplerLargeParkingSpots[spot->GetNumber()] = spot;
            break;
        default:
            std::cout << "Wrong parking spot type!" << std::endl;
            break;
        }
    }

    void assignVeichleSpot(std::shared_ptr<Vehicle> Vehicle, std::shared_ptr<ParkingSpot> spot)
    {
        // suppose assign must be successful
        spot->SetVehicle(Vehicle);
        switch (spot->GetType())
        {
        case SMALL_PARKING_SPOT:
            free_small_spot_count -= 1;
            break;
        case MEDIUM_PARKING_SPOT:
            free_medium_spot_count -= 1;
            break;
        case LARGE_PARKING_SPOT:
            free_large_spot_count -= 1;
            break;
        case SUPER_LARGE_PARKING_SPOT:
            free_super_large_spot_count -= 1;
            break;
        default:
            std::cout << "Wrong parking spot type!" << std::endl;
            break;
        }
        UpdateDisplayBoard(spot);
    }

    void freeParkingSpot(std::shared_ptr<ParkingSpot> spot)
    {
        spot->RemoveVehicle();
        switch (spot->GetType())
        {
        case SMALL_PARKING_SPOT:
            free_small_spot_count += 1;
            break;
        case MEDIUM_PARKING_SPOT:
            free_medium_spot_count += 1;
            break;
        case LARGE_PARKING_SPOT:
            free_large_spot_count += 1;
            break;
        case SUPER_LARGE_PARKING_SPOT:
            free_super_large_spot_count += 1;
            break;
        default:
            std::cout << "Wrong parking spot type!" << std::endl;
            break;
        }
    }

private:
    void UpdateDisplayBoard(std::shared_ptr<ParkingSpot> spot)
    {
        if (displayBoard.GetFreeSpotNumber(spot->GetType()) == spot->GetNumber())
        // need to find another free parking spot and assign to display_board
        {
            switch (spot->GetType())
            {
            case SMALL_PARKING_SPOT:
                for (const auto &pair : smallParkingSpots)
                {
                    if (!pair.second->IsOccupied())
                    {
                        displayBoard.SetFreeSpotNumber(pair.second);
                    }
                }
                break;
            case MEDIUM_PARKING_SPOT:
                for (const auto &pair : mediumParkingSpots)
                {
                    if (!pair.second->IsOccupied())
                    {
                        displayBoard.SetFreeSpotNumber(pair.second);
                    }
                }
                break;
            case LARGE_PARKING_SPOT:
                for (const auto &pair : largeParkingSpots)
                {
                    if (!pair.second->IsOccupied())
                    {
                        displayBoard.SetFreeSpotNumber(pair.second);
                    }
                }
                break;
            case SUPER_LARGE_PARKING_SPOT:
                for (const auto &pair : suplerLargeParkingSpots)
                {
                    if (!pair.second->IsOccupied())
                    {
                        displayBoard.SetFreeSpotNumber(pair.second);
                    }
                }
                break;
            default:
                std::cout << "Wrong parking spot type!" << std::endl;
                break;
            }
        }
        displayBoard.showEmptySpotNumber();
    }
};

class ParkingRate
{
public:
    ParkingRate()
    {
        // Initialize rates, mock implementation
    }
};

// ParkingLot: Our system will have only one object of this class. This can be enforced by using the Singleton pattern. In software engineering, the singleton pattern is a software design pattern that restricts the instantiation of a class to only one object.
class ParkingLot
{
private:
    std::string name;
    std::string address;
    ParkingRate parkingRate;
    int floors; // total floors

    int maxSmallSpotCnt;
    int maxMediumSpotCnt;
    int maxLargeSpotCnt;
    int maxSuperLargeSpotCnt;

    int smallSpotCnt;
    int mediumSpotCnt;
    int largeSpotCnt;
    int superLargeSpotCnt;

    std::unordered_map<int, ParkingTicket> activeTickets;

    std::unordered_map<std::string, std::shared_ptr<ParkingLot> > entrancePanels;
    std::unordered_map<std::string, std::shared_ptr<ParkingLot> > exitPanels;

    std::unordered_map<std::string, std::shared_ptr<ParkingFloor> > parkingFloor;

    std::mutex parkingLotMutex;
    static std::shared_ptr<ParkingLot> instance;

public:
    ParkingLot(const std::string &name, const std::string &address)
        : name(name), address(address), maxSmallSpotCnt(0), maxMediumSpotCnt(0),
          maxLargeSpotCnt(0), maxSuperLargeSpotCnt(0), smallSpotCnt(0), mediumSpotCnt(0),
          largeSpotCnt(0), superLargeSpotCnt(0)
    {
        // init each parking floor
        // for (int i = 0; i < floor; i++)
        // {
        //     parkingFloor[i] = new ParkingFloor(, , , );
        // }
    }

    static std::shared_ptr<ParkingLot> getInstance(const std::string &name, const std::string &address)
    {
        if (!instance)
        {
            instance = std::shared_ptr<ParkingLot>(new ParkingLot(name, address));
        }
        return instance;
    }

    bool isFull(VehicleType type) const
    {
        if (type == MOTORCYCLE)
        {
            return smallSpotCnt >= maxSmallSpotCnt;
        }
        else if (type == CAR)
        {
            return mediumSpotCnt >= maxMediumSpotCnt;
        }
        else if (type == VAN)
        {
            return largeSpotCnt >= maxLargeSpotCnt;
        }
        else if (type == BUS)
        {
            return superLargeSpotCnt >= maxSmallSpotCnt;
        }
        return true;
    }

    // Method to get a new parking ticket
    ParkingTicket getNewParkingTicket(const Vehicle &vehicle)
    {
        std::lock_guard<std::mutex> lock(parkingLotMutex); // Ensures thread safety

        if (isFull(vehicle.GetVehicleType()))
        {
            throw std::runtime_error("Parking full!");
        }

        ParkingTicket ticket;
        vehicle.assignTicket(ticket);
        ticket.saveInDB();

        // If the ticket is successfully saved, increment the parking spot count
        incrementSpotCount(vehicle.getType());
        activeTickets[ticket.getTicketNumber()] = ticket;

        return ticket;
    }

    void incrementSpotCount(VehicleType type)
    {
        if (type == MOTORCYCLE)
        {
            smallSpotCnt++;
        }
        else if (type == CAR)
        {
            mediumSpotCnt++;
        }
        else if (type == VAN)
        {
            largeSpotCnt++;
        }
        else if (type == BUS)
        {
            superLargeSpotCnt++;
        }
    }
};
int main()
{
}