#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "DynamicArray.h"

template <class T>
class UnionFind
{
private:
    int *size;
    int *parent;
    T *objects;

public:
    UnionFind(int initial = 0);
    void makeSet(T element, int id);
    T find(int id);
    void merge(int, int);
    bool isEmpty(int id);
    T findObject(int id);

private:
    int compressRecoursive(int id);
};

template <class T>
UnionFind<T>::UnionFind(int initial)
{
    size = new int[initial];
    parent = new int[initial];

    for (int i = 0; i < initial; i++)
    {
        size[i] = 0;
        parent[i] = i;
    }

    objects = new T[initial];
}

template <class T>
void UnionFind<T>::makeSet(T element, int id)
{
    objects[id] = element;
    parent[id] = id;
    size[id] = 1;
}

template <class T>
T UnionFind<T>::find(int id)
{
    int rootId = compressRecoursive(id);
    return objects[rootId];
}

template <class T>
int UnionFind<T>::compressRecoursive(int id)
{
    if (parent[id] == id)
    {
        return id;
    }

    parent[id] = compressRecoursive(parent[id]);
    return parent[id]; // root of the set.
}

template <class T>
void UnionFind<T>::merge(int set1, int set2)
{
    int root1 = compressRecoursive(set1);
    int root2 = compressRecoursive(set2);
    parent[root2] = root1;
    size[root1] += size[root2];

    // if (size[root1] < size[root2])
    // {
    // }
    // else
    // {
    //     parent[root2] = root1;
    //     size[root1] += size[root2];
    // }
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

#endif /* UNIONFIND_H */