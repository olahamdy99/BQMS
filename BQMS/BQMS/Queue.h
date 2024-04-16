#pragma once

template<class T>
class Queue
{
private:
    int num;
    int MaxSize;
    int front;
    int last;
public:
    T* arr;
    Queue(int size)
    {
        if (size > 0)
            MaxSize = size;
        else
            MaxSize = 30;
        num = 0;
        front = 0;
        last = MaxSize - 1;
        arr = new T[MaxSize];
    }
    bool IsEmpty()
    {
        return num == 0;
    }
    bool IsFull()
    {
        return num == MaxSize;
    }
    bool Add(T item)
    {
        if (!IsFull())
        {
            num++;
            last = (last + 1) % MaxSize;
            arr[last] = item;
            return true;
        }
        return false;
    }
    T Delete()
    {
        if (!IsEmpty())
        {
            num--;
            T deletedElement = arr[front];
            front = (front + 1) % MaxSize;

            return deletedElement;
        }
        throw std::runtime_error("Qeue is empty");
    }

    T Front()
    {
        return arr[front];
    }
    T Last()const
    {
        return arr[last];
    }
    int GetCurrentSize()
    {
        return num;
    }
    ~Queue()
    {
        delete[]arr;
    }




};

