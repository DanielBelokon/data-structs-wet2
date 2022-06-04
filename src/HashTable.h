#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include "DynamicArray.h"

#define BETA 0.356
#define RESIZE_THRESHOLD 0.75
#define INITIAL_CAPACITY 30

template <typename T>
class HashTable
{
private:
    class HashNode
    {
    private:
        T data = NULL;
        int id = -1;
        bool is_deleted;

    public:
        HashNode() : data(), is_deleted(false) {}
        T getData() { return data; }
        void setData(T data) { this->data = data; }
        int getId() { return id; }
        void setId(int id) { this->id = id; }
        bool isDeleted() { return is_deleted; }
        void setDeleted(bool is_deleted) { this->is_deleted = is_deleted; }
    };

    int *(customHash)(int);
    int capacity;
    int size;
    HashNode *table;

public:
    class iterator
    {
    private:
        int capacity;
        HashNode *array;
        HashTable *table;
        int current;

    public:
        iterator(int capacity, HashNode *array, HashTable *table, int current)
            : capacity(capacity), array(array), table(table), current(current)
        {
        }
        iterator &operator++()
        {
            current++;
            return *this;
        }
        bool operator!=(const iterator &other) const
        {
            return current != other.current;
        }
        T operator*()
        {
            return array[current].getData();
        }
    };

    HashTable()
    {
        table = new HashNode[INITIAL_CAPACITY];
        capacity = INITIAL_CAPACITY;
    }

    iterator begin()
    {
        return iterator(capacity, table, this, 0);
    }

    iterator end()
    {
        return iterator(capacity, table, this, capacity);
    }

    void insert(int id, T value);
    void remove(int id);
    T search(int id);
    int hash(int id);
    bool isEmpty(int id);
    int getCapacity() { return capacity; }

    T operator[](int id);
    T operator[](int id) const;
    void merge(HashTable<T> *other);

    ~HashTable();

private:
    bool isDeleted(int id);
    int getId(int key);
    void resize();
};

template <typename T>
void HashTable<T>::insert(int id, T value)
{
    if (size > RESIZE_THRESHOLD * capacity)
    {
        resize();
    }

    int key = hash(id);
    size++;
    table[key].setData(value);
    table[key].setId(id);
    table[key].setDeleted(false);
}

template <typename T>
void HashTable<T>::remove(int id)
{
    int key = hash(id);
    table[key].setData(NULL);
    table[key].setDeleted(true);
}

template <typename T>
T HashTable<T>::search(int id)
{
    int key = hash(id);
    for (int i = 0; i < capacity; i++)
    {
        if (!table[key].isDeleted())
        {
            if (table[key].getId() == id)
            {
                return (table[key].getData());
            }
            else if (table[key].getId() == -1)
            {
                return nullptr;
            }
        }
        key = (key + 1) % capacity;
    }

    return nullptr;
}

template <typename T>
int HashTable<T>::hash(int id)
{
    double tmp;
    int key = (int)(modf(id * BETA, &tmp) * capacity);
    // Linear Probing
    while (!isDeleted(key) && table[key].getId() != id)
    {
        key = (key + 1) % capacity;
    };
    return key;
}

template <typename T>
void HashTable<T>::merge(HashTable<T> *other)
{
    for (int i = 0; i < other->getCapacity(); i++)
    {
        if (other->getId(i) != -1 && !other->isDeleted(i))
        {
            insert(other->getId(i), (*other)[i]);
        }
    }
}

template <typename T>
bool HashTable<T>::isDeleted(int id)
{
    return (table[id].getId() == -1 || table[id].isDeleted());
}

template <typename T>
void HashTable<T>::resize()
{
    capacity *= 2;
    HashNode *new_array = new HashNode[capacity];
    for (int i = 0; i < capacity; i++)
    {
        new_array[hash(table[i].getId())] = table[i];
    }
    delete[] table;
    table = new_array;
}

template <typename T>
T HashTable<T>::operator[](int id)
{
    return search(id);
}

template <typename T>
T HashTable<T>::operator[](int id) const
{
    return search(id);
}

template <typename T>
int HashTable<T>::getId(int key)
{
    return table[key].getId();
}

template <typename T>
bool HashTable<T>::isEmpty(int id)
{
    return (table[hash(id)].getId() == -1);
}

template <typename T>
HashTable<T>::~HashTable()
{
    delete[] table;
}

#endif /* HASHTABLE_H */