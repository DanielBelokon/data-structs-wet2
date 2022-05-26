#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include "DynamicArray.h"

#define BETA 0.356
#define RESIZE_THRESHOLD 0.75
#define INITIAL_CAPACITY 30

template <class T>
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
        HashNode() : is_deleted(false) {}
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
    HashTable(int *custom_hash(int) = void) : customHash(custom_hash)
    {
        table = new HashNode[INITIAL_CAPACITY];
    }
    void insert(int id, T value);
    void remove(int id);
    T search(int id);
    int hash(int id);
    ~HashTable();

    T &operator[](int id);
    T &operator[](int id) const;

private:
    bool isDeleted(int id);
    void resize();
};

template <class T>
void HashTable<T>::insert(int id, T value)
{
    if (size > RESIZE_THRESHOLD * capacity)
    {
        resize();
    }

    int key = hash(key);
    table[key].setData(data);
    table[key].setId(id);
}

template <class T>
void HashTable<T>::remove(int id)
{
    int key = hash(key);
    table[key].setData(NULL);
    table[key].setDeleted(true);
}

template <class T>
T HashTable<T>::search(int id)
{
    int key = hash(id);
    for (int i = 0; i < table.getCapacity(); i++)
    {
        if (!table[key].isDeleted() && (table[key].getId() == id || table[key].getId() == -1))
        {
            return table[key].getData();
        }
        key = (key + 1) % table.getCapacity();
    }

    return table[key].getData();
}

template <class T>
int HashTable<T>::hash(int id)
{
    int key = (int)(modf(id * BETA) * table.getCapacity());
    // Linear Probing
    while (!isDeleted(key))
    {
        key = (key + 1) % table.getCapacity();
    };
    return key;
}

template <class T>
bool HashTable<T>::isDeleted(int id)
{
    return (table[key] == nullptr || table[key].isDeleted());
}

template <class T>
void HashTable<T>::resize()
{
    capacity *= 2;
    T *new_array = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        new_array[hash(array[i].getId())] = array[i];
    }
    delete[] table;
    table = new_array;
}

#endif /* HASHTABLE_H */