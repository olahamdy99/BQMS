#pragma once
#include "Customer.h"

class Teller
{
private:
    bool isFree;
    int serviceTime;
    Customer* currentCustomer;
    int levingTime;

public:
    Teller()
    {
        this->isFree = true;
        this->currentCustomer = nullptr;
        this->serviceTime = 0;
    }

    bool IsFree()
    {
        return isFree;
    }

    void SetBusy()
    {
        isFree = false;
    }

    void SetFree()
    {
        isFree = true;
        serviceTime = 0;
        currentCustomer = nullptr;
    }

    void SetserviceTime(int time)
    {
        serviceTime = time;
    }
    void SetserviceTime()
    {
        if (currentCustomer != nullptr)
            serviceTime = currentCustomer->GetserviceTime();
    }

    void SetCurrentCustomer(Customer& customer)
    {
        currentCustomer = &customer;
        SetserviceTime();
    }

    int GetRemainingserviceTime()
    {
        return this->serviceTime;
    }

    int GetCurrentcustomerId()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetcustomerId();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerArrivalTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetArrivalTime();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerWaitingTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetWaitingTime();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerserviceTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetserviceTime();
        }
        else
        {
            return -1;
        }
    }


    void DecreaseserviceTime()
    {
        if (serviceTime > 0)
        {
            serviceTime--;
        }
    }
    void SetLevingTime()
    {
        levingTime = currentCustomer->GetleaveTime();
    }
    int GetLevingTime()
    {
        return levingTime;
    }

};

class TellerList
{
private:
    int numberOfTellers;
    Teller* tellers;

public:
    //Dynamic Tellers
    TellerList(int numberOfTellers)
    {
        this->numberOfTellers = numberOfTellers;
        tellers = new Teller[numberOfTellers];

    }
    // Free Tellers
    void SetTellerFree(int tellerNum, Customer& currentCustomer)
    {
        if (tellerNum > 0 && tellerNum <= numberOfTellers)
        {
            tellers[tellerNum - 1].SetFree();
        }
    }

    int GetFreeTellers()
    {
        for (int i = 0; i < numberOfTellers; ++i)
        {
            if (tellers[i].IsFree())
            {
                return i + 1;
            }
        }
        return -1;
    }
    //Busy Tellers
    void SetTellerBusy(int tellerNum, Customer& currentCustomer, int serviceTime)
    {
        if (tellerNum > 0 && tellerNum <= numberOfTellers)
        {
            tellers[tellerNum - 1].SetBusy();
            tellers[tellerNum - 1].SetserviceTime(serviceTime);
            tellers[tellerNum - 1].SetCurrentCustomer(currentCustomer);
        }
    }
    void SetTellerBusy(int tellerNum, Customer& currentCustomer)
    {
        if (tellerNum > 0 && tellerNum <= numberOfTellers)
        {
            tellers[tellerNum - 1].SetBusy();
            tellers[tellerNum - 1].SetserviceTime(currentCustomer.GetserviceTime());
            tellers[tellerNum - 1].SetCurrentCustomer(currentCustomer);
        }
    }

    int GetBusyTellers()
    {
        int busyTellers = 0;
        for (int i = 0; i < numberOfTellers; ++i)
        {
            if (!tellers[i].IsFree())
            {
                busyTellers++;
            }
        }
        return busyTellers;
    }

    // Update Tellers
    void UpdateTellers()
    {
        for (int i = 0; i < numberOfTellers; i++)
        {
            Teller& currentTeller = tellers[i];

            if (!currentTeller.IsFree())
            {
                currentTeller.DecreaseserviceTime();
                if (currentTeller.GetRemainingserviceTime() == 0)
                {
                    currentTeller.SetFree();
                }
            }
        }
    }

    Teller GetTeller(int teller)
    {
        return tellers[teller];
    }

    //Destructor
    ~TellerList()
    {
        delete[] tellers;
    }


};

