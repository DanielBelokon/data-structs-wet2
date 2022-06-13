#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "DynamicArray.h"

template <class T>
class UnionFind
{
private:
    int *size;
    int *parent;
    int *current_index;
    T *objects;
    long double *value;

public:
    UnionFind(int initial = 0);
    void makeSet(T element, int id);
    T find(int id);
    void merge(int, int, double factor = 1);
    bool isEmpty(int id);
    T findObject(int id);
    long double getValue(int id);

    ~UnionFind();

private:
    int compressRecoursive(int id);
};

template <class T>
UnionFind<T>::UnionFind(int initial)
{
    size = new int[initial];
    value = new long double[initial];
    parent = new int[initial];
    current_index = new int[initial];
    for (int i = 0; i < initial; i++)
    {
        size[i] = 0;
        value[i] = i;
        parent[i] = i;
        current_index[i] = i;
    }

    objects = new T[initial];
}

template <class T>
void UnionFind<T>::makeSet(T element, int id)
{
    objects[id] = element;
    parent[id] = id;
    value[id] = id;
    current_index[id] = id;
    size[id] = 1;
}

template <class T>
T UnionFind<T>::find(int id)
{
    int rootId = compressRecoursive(id);
    return objects[current_index[rootId]];
}

template <class T>
int UnionFind<T>::compressRecoursive(int id)
{
    if (parent[id] == id)
    {
        return id;
    }

    int root_id = compressRecoursive(parent[id]);
    value[id] += root_id == parent[id] ? 0 : value[parent[id]];
    parent[id] = root_id;

    return parent[id]; // root of the set.
}

template <class T>
void UnionFind<T>::merge(int set1, int set2, double factor)
{
    int root1 = compressRecoursive(set1); // the index of the oopsite root
    int root2 = compressRecoursive(set2);
    long double new_value = value[root2] * factor;
    if (size[root1] >= size[root2])
    {
        value[root1] += new_value;
        value[root2] -= value[root1];
        parent[root2] = root1;
        size[root1] += size[root2];
        current_index[root2] = current_index[root1];
    }
    else
    {
        // b buy a - but B pointing to A because size(B)<size(A)
        // r(b)new = value[root1] + newvalue - value[root2]
        value[root1] = value[root1] + new_value - value[root2];
        current_index[root2] = current_index[root1];
        parent[root1] = root2;
        size[root2] += size[root1];
    }
}

template <class T>
bool UnionFind<T>::isEmpty(int id)
{
    return (size[id] == 0);
}

template <class T>
T UnionFind<T>::findObject(int id)
{
    return objects[id];
}

template <class T>
long double UnionFind<T>::getValue(int id)
{
    int root = compressRecoursive(id);
    return root == id ? value[root] : value[root] + value[id];
}

template <class T>
UnionFind<T>::~UnionFind()
{
    delete[] size;
    delete[] parent;
    delete[] objects;
    // delete[] value;
}

#endif /* UNIONFIND_H */