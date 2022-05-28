#ifndef UNIONFIND_H
#define UNIONFIND_H

#include "DynamicArray.h"

template <class T>
class UnionFind
{
private:
    DynamicArray<int> size;
    DynamicArray<int> parent;
    DynamicArray<T> objects;

public:
    UnionFind(int initial = 0);
    ~UnionFind();
    T makeSet(T element, int id);
    T find(int id);
    void merge(int, int);

private:
    int compressRecoursive(int id);
};

template <class T>
UnionFind<T>::UnionFind(int initial)
{
    size = DynamicArray<int>(initial);
    parent = DynamicArray<int>(initial);
    objects = DynamicArray<T>(initial);
}

template <class T>
T UnionFind<T>::makeSet(T element, int id)
{
    objects[id] = element;
    size[id] = id;
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

    if (size[root1] < size[root2])
    {
        parent[root1] = root2;
        size[root2] += size[root1];
    }
    else
    {
        parent[root2] = root1;
        size[root1] += size[root2];
    }
}

#endif /* UNIONFIND_H */