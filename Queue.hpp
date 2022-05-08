#include <iostream>
#include <exception>


template <typename T>
struct Data {
    T data;
    size_t priority;
};


template <typename T>
class MyQueue
{
    Data<T> *data;
    size_t capacity;
    size_t size;
    size_t maxPriority;

    size_t get;
    size_t put;

    void resize();

    void copyFrom(const MyQueue<T>& other);
    void free();
public:
    MyQueue();

    MyQueue(const size_t maxPriority);


    MyQueue(const MyQueue<T>& other);
    MyQueue<T>& operator=(const MyQueue<T>& other);

    void push(const T& obj, size_t priority);
    void push(T&& obj, size_t priority);
    void pop();

    const T& peek() const;
    bool isEmpty() const;

    ~MyQueue();

};

template <typename T>
MyQueue<T>::MyQueue()
{
    maxPriority = 0;
    capacity = 4;
    data = new T[capacity];
    size = 0;
    get = put = 0;
}

template <typename T>
MyQueue<T>::MyQueue(size_t maxPriority)
{
    this->maxPriority = maxPriority;
    capacity = 4;
    data = new Data<T>[capacity];
    size = 0;
    get = put = 0;
}

template <typename T>
void MyQueue<T>::push(const T& obj, size_t priority)
{
    if (size == capacity)
        resize();

    if (priority > maxPriority)
        throw std::logic_error("Priority is too high");

    data[put].data = obj;
    data[put].priority = priority;
    if(data[put].priority > data[get].priority)
        get = put;

    (++put) %= capacity;
    size++;
}

template <typename T>
void MyQueue<T>::push(T&& obj, size_t priority)
{
    if (size == capacity)
        resize();

    data[put].data = std::move(obj); //move operator =
    data[put].priority = priority;

    if(data[put].priority > data[get].priority)
        get = put;

    (++put) %= capacity;
    size++;
}

template <typename T>
bool MyQueue<T>::isEmpty() const
{
    return size == 0;
}


template <typename T>
const T& MyQueue<T>::peek() const
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");

    return data[get].data;
}

template <typename T>
void MyQueue<T>::pop()
{
    if (isEmpty())
        throw std::logic_error("Empty queue!");
    data[get].priority = 0;
    (++get) %= capacity;

    for(size_t i = get + 1; i != get; (++i) %= capacity) {
        if(data[i].priority > data[get].priority)
            get = i;
    }
    size--;
}

template <typename T>
void MyQueue<T>::resize()
{
    Data<T>* resizedData = new Data<T>[capacity * 2];
    for (size_t i = 0; i < size; i++)
    {
        resizedData[i] = data[get];
        (++get) %= capacity;
    }
    capacity *= 2;
    delete[] data;
    data = resizedData;
    get = 0;
    put = size;
}


template <typename T>
void MyQueue<T>::copyFrom(const MyQueue<T>& other)
{
    data = new T[other.capacity];
    for (int i = 0; i < other.capacity; i++)
        data[i] = other.data[i];

    get = other.get;
    put = other.put;

    size = other.size;
    capacity = other.capacity;

}

template <typename T>
void MyQueue<T>::free()
{
    delete[] data;
}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other)
{
    copyFrom(other);

}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
MyQueue<T>::~MyQueue()
{
    free();
}