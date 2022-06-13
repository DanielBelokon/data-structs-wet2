#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>

#define BETA 0.356
#define RESIZE_THRESHOLD 0.75
#define INITIAL_CAPACITY 29

template <typename T>
class HashNode
{
private:
    T data = T{};
    int id = -1;
    bool is_deleted;

public:
    HashNode() : data(T{}), id(-1), is_deleted(false) {}

    T getData() { return data; }
    void setData(T data) { this->data = data; }
    int getId() { return id; }
    void setId(int id) { this->id = id; }
    bool isDeleted() { return is_deleted; }

    void setDeleted(bool is_deleted) { this->is_deleted = is_deleted; }
};

template <typename T>
class HashTable
{
private:
    int capacity;
    int size;
    HashNode<T> *table;

public:
    class iterator
    {
    private:
        int capacity;
        HashNode<T> *array;
        HashTable *table;
        int current;

    public:
        iterator(int capacity, HashNode<T> *array, HashTable *table, int current)
            : capacity(capacity), array(array), table(table), current(current)
        {
        }
        iterator &operator++()
        {
            if (current == capacity)
                return *this;
            current++;
            return *this;
        }
        bool operator!=(const iterator &other) const
        {
            return this->current != other.current;
        }
        T operator*()
        {
            if (current >= table->capacity)
                return T{};
            return table->table[current].getData();
        }
    };

    HashTable()
    {
        table = new HashNode<T>[INITIAL_CAPACITY];
        capacity = INITIAL_CAPACITY;
        size = 0;
    }

    HashTable<T> &operator=(const HashTable &other)
    {
        if (this == &other)
            return *this;
        this->capacity = other.capacity;
        this->size = other.size;
        this->table = new HashNode<T>[capacity];
        for (int i = 0; i < capacity; i++)
        {
            this->table[i] = other.table[i];
        }
        return *this;
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

    // T operator[](int id);
    // T operator[](int id) const;
    T getDataAt(int key);
    void merge(HashTable<T> *other);

    ~HashTable();

private:
    bool isDeleted(int key);
    int getId(int key);
    void resize(bool downsize = false);
};

template <typename T>
void HashTable<T>::insert(int id, T value)
{
    if (size > RESIZE_THRESHOLD * capacity)
    {
        resize(false);
    }

    int key = hash(id);
    if (key >= capacity || key < 0)
        throw;
    if (isDeleted(key))
        size++;
    // else
    //     throw std::invalid_argument("Key already exists");
    table[key].setData(value);
    table[key].setId(id);
    table[key].setDeleted(false);
}

template <typename T>
void HashTable<T>::remove(int id)
{
    int key = hash(id);
    if (key >= capacity || key < 0)
        throw;
    for (int i = 0; i < capacity; i++)
    {
        if (key >= capacity || key < 0)
            throw;
        if (!table[key].isDeleted())
        {
            if (table[key].getId() == id)
            {
                break;
            }
            else if (table[key].getId() == -1)
            {
                return;
            }
        }
        key = (key + 1) % capacity;
    }

    size--;
    table[key].setId(-1);
    table[key].setData({});
    table[key].setDeleted(true);
    if (size < RESIZE_THRESHOLD * capacity / 2 && capacity > INITIAL_CAPACITY)
        resize(true);
}

template <typename T>
T HashTable<T>::search(int id)
{
    int key = hash(id);
    for (int i = 0; i < capacity; i++)
    {
        if (key >= capacity || key < 0)
            throw;
        if (!table[key].isDeleted())
        {
            if (table[key].getId() == id)
            {
                return (table[key].getData());
            }
            else if (table[key].getId() == -1)
            {
                return T{};
            }
        }
        key = (key + 1) % capacity;
    }

    return T{};
}

template <typename T>
int HashTable<T>::hash(int id)
{
    if (id < 0)
        throw;
    double tmp;
    int key = (int)(modf(id * BETA, &tmp) * capacity);
    // Linear Probing
    while (!isDeleted(key) && table[key].getId() != id)
    {
        key = (key + 1) % capacity;
    }
    if (key >= capacity || key < 0)
        throw;
    return key;
}

template <typename T>
void HashTable<T>::merge(HashTable<T> *other)
{
    for (int i = 0; i < other->getCapacity(); i++)
    {
        if (other->getDataAt(i) != T{})
        {
            this->insert(other->getId(i), other->getDataAt(i));
            other->remove(other->getId(i));
        }
    }
}

template <typename T>
bool HashTable<T>::isDeleted(int key)
{
    if (key >= capacity || key < 0)
        throw;
    return (table[key].getId() == -1 || table[key].isDeleted());
}

template <typename T>
void HashTable<T>::resize(bool downsize)
{
    int prev_capacity = capacity;
    if (downsize)
        capacity /= 2;
    else
        capacity *= 2;
    HashNode<T> *new_array = new HashNode<T>[capacity];
    HashNode<T> *prev_array = table;
    // int old_size = size;
    size = 0;
    table = new_array;

    for (int i = 0; i < prev_capacity; i++)
    {
        if (prev_array[i].getId() == -1 || prev_array[i].isDeleted())
            continue;
        // int key = hash(prev_array[i].getId());
        // if (key >= capacity || key < 0)
        //     throw std::bad_alloc();
        insert(prev_array[i].getId(), prev_array[i].getData());
        // new_array[key].setData(prev_array[i].getData());
        // new_array[key].setId(prev_array[i].getId());
        // new_size++;
        // new_array[key].setDeleted(table[i].isDeleted());
    }

    delete[] prev_array;
}

// template <typename T>
// T HashTable<T>::operator[](int id)
// {
//     return search(id);
// }

// template <typename T>
// T HashTable<T>::operator[](int id) const
// {
//     return search(id);
// }

template <typename T>
int HashTable<T>::getId(int key)
{
    if (key >= capacity || key < 0)
        return -1;
    return table[key].getId();
}

template <typename T>
T HashTable<T>::getDataAt(int key)
{
    if (key >= capacity || key < 0)
        return T{};
    return table[key].getData();
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