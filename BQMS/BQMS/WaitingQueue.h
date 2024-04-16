#pragma once
#include "Queue.h"
#include"Customer.h"
using namespace std;

class WaitingQueue :public Queue<Customer>
{
public:
    WaitingQueue(int size) :Queue<Customer>(size) {}

    void UpdateWaitingQueue()
    {
        Customer dummyCustomer;
        dummyCustomer.SetWaitingTime(-1);
        int wTime = 0;
        Add(dummyCustomer);
        while (wTime != -1)
        {
            Customer deletedCustomer = Delete();
            wTime = deletedCustomer.GetWaitingTime();
            if (wTime == -1)
                break;
            deletedCustomer.IncrementWaitingTime();
            Add(deletedCustomer);
        }
        SortQueue();
    }
    // Bubble sort based on arrival time
    void SortQueue()
    {
        for (int i = 0; i < this->GetCurrentSize(); ++i)
        {
            for (int j = 0; j < this->GetCurrentSize() - 1; ++j)
            {
                if (this->arr[j].GetArrivalTime() > this->arr[j + 1].GetArrivalTime())
                {
                    // Swap customers
                    Customer temp = this->arr[j];
                    this->arr[j] = this->arr[j + 1];
                    this->arr[j + 1] = temp;
                }
            }
        }
    }

};
