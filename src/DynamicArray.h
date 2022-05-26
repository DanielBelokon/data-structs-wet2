#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define DEFAULT_CAPACITY 30

template <class T>
class DynamicArray
{

private:
    int cur_size;
    int capacity;
    T *array;
    int *(customHash)(int);

public:
    DynamicArray(int capacity = DEFAULT_CAPACITY, int *customHash(int) = void);
    void insert(int index, T value);
    void remove(int index);
    void resize();

    T &operator[](int id);
    T &operator[](int id) const;
};

template <class T>
DynamicArray<T>::DynamicArray(int capacity, int *customHash(int))
{
    this->capacity = capacity;
    this->customHash = customHash;
    this->cur_size = 0;
    this->array = new T[capacity];
}

template <class T>
void DynamicArray<T>::insert(int index, T value)
{
    if (index > cur_size || index < 0)
    {
        return; // TODO: Throw exception
    }

    if (size == capacity)
    {
        resize();
    }

    array[index] = value;
}

template <class T>
void DynamicArray<T>::remove(int index)
{
    if (index > cur_size || index < 0)
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
    for (int i = 0; i < size; i++)
    {
        new_array[customHash(i)] = array[i];
    }
    delete[] array;
    array = new_array;
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

#endif /* DYNAMICARRAY_H */