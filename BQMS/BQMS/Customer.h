#pragma once

class Customer
{
private:
    int customerId;
    int arrivalTime;
    int waitingTime;
    int serviceTime;
    int leaveTime;
public:
    //constructors
    Customer() {}
    Customer(int customerId, int arrivalTime, int waitingTime, int serviceTime)
    {
        this->customerId = customerId;
        this->arrivalTime = arrivalTime;
        this->waitingTime = waitingTime;
        this->serviceTime = serviceTime;
    }
    //customer Id
    int GetcustomerId()
    {
        return this->customerId;
    }
    // Customer Arrival
    void SetArrivalTime(int time)
    {
        arrivalTime = time;
    }

    // Customer Waiting
    int GetWaitingTime()
    {
        return waitingTime;
    }

    void IncrementWaitingTime()
    {
        waitingTime++;
    }

    void SetWaitingTime(int waitingTime)
    {
        this->waitingTime = waitingTime;
    }
    // Arrival Time
    int GetArrivalTime()
    {
        return this->arrivalTime;
    }
    // Service Time
    int GetserviceTime()
    {
        return this->serviceTime;
    }
    //Leave Time
    void SetleaveTime(int leaveTime)
    {
        this->leaveTime = leaveTime;
    }

    void SetleaveTime()
    {
        this->leaveTime = GetArrivalTime() + GetserviceTime() + GetWaitingTime();
    }
    int GetleaveTime()
    {
        return this->leaveTime;
    }

};

