#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Exceptions.h"

#define DEFAULT_CAPACITY 8

template <class T>
class DynamicArray
{

private:
    int cur_size;
    int capacity;
    T *array;

public:
    DynamicArray(int capacity = DEFAULT_CAPACITY);
    void insert(int index, T value);
    void remove(int index);
    void resize();
    ~DynamicArray();
    T &operator[](int id);
    T &operator[](int id) const;
};

template <class T>
DynamicArray<T>::DynamicArray(int capacity)
{
    this->capacity = capacity;
    this->cur_size = 0;
    this->array = new T[capacity];
}

template <class T>
void DynamicArray<T>::insert(int index, T value)
{
    if (index > 2 * capacity || index < 0)
    {
        throw InvalidInputException();
        // return; // TODO: Throw exception
    }

    if (cur_size >= capacity)
    {
        resize();
    }

    array[index] = value;
}

template <class T>
void DynamicArray<T>::remove(int index)
{
    if (index > 2 * capacity || index < 0)
    {
        return; // TODO: Throw exception
    }

    array[index] = nullptr;
}

template <class T>
void DynamicArray<T>::resize()
{
    capacity *= 2;
    T *new_array = new T[capacity];
    for (int i = 0; i < capacity; i++)
    {
        new_array[i] = array[i];
    }
    delete[] array;
    *array = *new_array;
}

template <class T>
T &DynamicArray<T>::operator[](int id)
{
    return array[id];
}

template <class T>
T &DynamicArray<T>::operator[](int id) const
{
    return array[id];
}
// DESTRUCTOR
template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] array;
}

#endif /* DYNAMICARRAY_H */