#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cmath>
#include "Exceptions.h"
#include "TreeNode.h"

template <typename T>
class AVLTree
{
private:
    Node<T> *root;
    int size;

    bool (*customCompare)(const T &a, const T &b);

public:
    AVLTree(bool (*customCompare)(const T &a, const T &b) = nullptr) : root(nullptr), size(0), customCompare(customCompare)
    {
    }

    void insert(T data, int rank = 0);
    void remove(T data);
    void merge(AVLTree<T> *tree);

    int getSize();
    Node<T> *getRoot() { return root; }

    long long getRank(T data, int *place);

    T find(T object);
    T *getInOrderArray(int amount = 0);
    T getHighest();
    long long getHighestMRankSum(int m);

    ~AVLTree();

private:
    bool compare(T const &node1, T const &node2)
    {
        if (!node1 || !node2)
            return false;
        if (customCompare != nullptr)
        {
            return customCompare(node1, node2);
        }
        return node1 < node2;
    }

    Node<T> *insertAux(T data, Node<T> *current, Node<T> *parent, int rank = 0);
    void removeAux(T toDelete, Node<T> *current, Node<T> *parent);
    void replaceChild(Node<T> *parent, Node<T> *child, Node<T> *newChild);

    void balance(Node<T> *current, Node<T> *parent);
    void inOrderAux(T *array, int *index, Node<T> *current, int amount);
    void trim(Node<T> *current, Node<T> *parent, int *amount);
    T *mergeArrays(T *arr1, T *arr2, int size1, int size2);
    void insertSortedArrayInOrder(Node<T> *current, T **arr, int *index, int size);
    Node<T> *buildEmptyTree(int h);
    void rotateLeft(Node<T> *current, Node<T> *parent);
    void rotateRight(Node<T> *current, Node<T> *parent);
    void setRoot(Node<T> *root);
    void updateRankPostorder(Node<T> *current);

public:
    Node<T> *findNode(T object, Node<T> **prev = nullptr);
};

template <typename T>
int AVLTree<T>::getSize()
{
    return size;
}

template <typename T>
T AVLTree<T>::getHighest()
{
    Node<T> *current = root;
    if (current == nullptr)
    {
        throw EmptyTreeException();
    }

    while (current->getRight() != nullptr)
    {
        current = current->getRight();
    }
    return current->getData();
}

template <typename T>
void AVLTree<T>::insert(T data, int rank)
{
    if (find(data) != nullptr)
        return;

    if (root == nullptr)
    {
        root = new Node<T>(data, rank);
        size++;
        return;
    }
    Node<T> *current = root;
    insertAux(data, current, nullptr, rank);
}

template <typename T>
Node<T> *AVLTree<T>::insertAux(T data, Node<T> *current, Node<T> *parent, int rank)
{
    if (current == nullptr)
    {
        current = new Node<T>(data, rank);
        size++;
        return current;
    }
    if (compare(data, current->getData()))
    {
        Node<T> *newNode = insertAux(data, current->getLeft(), current, rank);
        if (newNode != nullptr)
            current->setLeft(newNode);
    }
    else if (compare(current->getData(), data))
    {
        Node<T> *newNode = insertAux(data, current->getRight(), current, rank);
        if (newNode != nullptr)
            current->setRight(newNode);
    }
    else
    {
        return nullptr;
    }

    balance(current, parent);

    return nullptr;
}

template <typename T>
void AVLTree<T>::balance(Node<T> *current, Node<T> *parent)
{
    if (current == nullptr || (parent != nullptr && (parent->getRight() != current && parent->getLeft() != current)))
    {
        return;
    }

    current->updateHeight();
    int balanceFactor = current->getBalanceFactor();
    if (balanceFactor > 1)
    {
        if (current->getLeft()->getBalanceFactor() >= 0)
        {
            // Balance LL situation
            rotateRight(current, parent);
        }
        else
        {
            // Balance LR situation
            rotateLeft(current->getLeft(), current);
            rotateRight(current, parent);
        }
    }
    else if (balanceFactor < -1)
    {
        if (current->getRight()->getBalanceFactor() <= 0)
        {
            // Balance RR situation
            rotateLeft(current, parent);
        }
        else
        {
            // Balance RL situation
            rotateRight(current->getRight(), current);
            rotateLeft(current, parent);
        }
    }
}

template <typename T>
void AVLTree<T>::removeAux(T toDelete, Node<T> *current, Node<T> *parent)
{
    // Find
    if (current == nullptr)
        return;

    if (compare(toDelete, current->getData()))
    {
        removeAux(toDelete, current->getLeft(), current);
    }
    else if (compare(current->getData(), toDelete))
    {
        removeAux(toDelete, current->getRight(), current);
    }
    else if (current->getRight() == nullptr && current->getLeft() == nullptr)
    {
        replaceChild(parent, current, nullptr);
        delete current;
        current = nullptr;
        size--;
        return;
    }
    else if (current->getRight() == nullptr && current->getLeft() != nullptr)
    {
        Node<T> *temp = current->getLeft();
        replaceChild(parent, current, temp);
        current->setLeft(nullptr);
        delete current;
        current = nullptr;
        size--;

        return;
    }
    else if (current->getRight() != nullptr && current->getLeft() == nullptr)
    {
        Node<T> *temp = current->getRight();
        replaceChild(parent, current, temp);
        current->setRight(nullptr);
        delete current;
        current = nullptr;
        size--;

        return;
    }
    else
    {
        Node<T> *temp = current->getRight();
        while (temp->getLeft() != nullptr)
        {
            temp = temp->getLeft();
        }
        T tempData = temp->getData();
        int tempRank = temp->getRank();

        removeAux(tempData, root, nullptr);

        current->setData(tempData);
        current->setRank(tempRank);
    }

    if (current != nullptr)
    {
        balance(current, parent);
    }
}

template <typename T>
void AVLTree<T>::rotateLeft(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_root = root->getRight();
    replaceChild(parent, root, new_root);
    root->setRight(new_root->getLeft());
    new_root->setLeft(root);

    new_root->getLeft()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::rotateRight(Node<T> *root, Node<T> *parent)
{
    Node<T> *new_root = root->getLeft();
    replaceChild(parent, root, new_root);
    root->setLeft(new_root->getRight());
    new_root->setRight(root);

    new_root->getRight()->updateHeight();
    new_root->updateHeight();
    if (parent != nullptr)
    {
        parent->updateHeight();
    }
}

template <typename T>
void AVLTree<T>::replaceChild(Node<T> *parent, Node<T> *child, Node<T> *newChild)
{
    if (parent == nullptr)
    {
        root = newChild;
        return;
    }

    if (parent->getLeft() == child)
    {
        parent->setLeft(newChild);
    }
    else
    {
        parent->setRight(newChild);
    }
}

template <typename T>
T AVLTree<T>::find(T object)
{
    Node<T> *result = findNode(object);
    if (result == nullptr)
    {
        return nullptr;
    }
    else
        return result->getData();
}

template <typename T>
Node<T> *AVLTree<T>::findNode(T object, Node<T> **prev)
{
    Node<T> *current = root;
    Node<T> *parent = nullptr;
    while (current != nullptr)
    {
        if (compare(current->getData(), object))
        {
            parent = current;
            current = current->getRight();
        }
        else if (compare(object, current->getData()))
        {
            parent = current;
            current = current->getLeft();
        }
        else
        {
            if (prev != nullptr)
            {
                *prev = parent;
            }
            return current;
        }
    }
    if (prev != nullptr)
    {
        *prev = parent;
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::remove(T object)
{
    removeAux(object, root, nullptr);
}

template <typename T>
void AVLTree<T>::setRoot(Node<T> *root)
{
    this->root = root;
}

template <typename T>
void AVLTree<T>::merge(AVLTree<T> *tree)
{
    // Merge tree with O(n) complexity
    if (tree == nullptr)
        return;
    T *tree1 = getInOrderArray();
    T *tree2 = tree->getInOrderArray();
    T *merged = mergeArrays(tree1, tree2, size, tree->size);
    delete[] tree1;
    delete[] tree2;
    size += tree->size;
    int new_height = std::ceil(std::log2(size + 1)) - 1;
    int to_delete = std::exp2(new_height + 1) - size - 1;

    delete root;
    delete tree->root;
    tree->root = nullptr;
    root = buildEmptyTree(new_height);
    trim(root, nullptr, &to_delete);
    int index = 0;
    insertSortedArrayInOrder(root, &merged, &index, size);
    updateRankPostorder(root);
    delete[] merged;
}

// helper function for merge arrays
template <typename T>
T *AVLTree<T>::mergeArrays(T *arr1, T *arr2, int size1, int size2)
{
    T *merged = new T[size1 + size2];
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2)
    {
        if (compare(arr1[i], arr2[j]))
        {
            merged[k] = arr1[i];
            i++;
        }
        else
        {
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < size1)
    {
        merged[k] = arr1[i];
        i++;
        k++;
    }
    while (j < size2)
    {
        merged[k] = arr2[j];
        j++;
        k++;
    }
    return merged;
}

template <typename T>
void AVLTree<T>::insertSortedArrayInOrder(Node<T> *current, T **arr, int *index, int size)
{
    if (current == nullptr)
        return;
    insertSortedArrayInOrder(current->getLeft(), arr, index, size);
    current->setData((*arr)[(*index)++]);
    insertSortedArrayInOrder(current->getRight(), arr, index, size);
}

// hlper function for cutting the un-necessary node for making the tree "almost full"
template <typename T>
void AVLTree<T>::trim(Node<T> *current, Node<T> *parent, int *amount)
{
    if (current == nullptr || *amount == 0)
        return;
    trim(current->getRight(), current, amount);

    if (current->getRight() == nullptr && current->getLeft() == nullptr)
    {
        replaceChild(parent, current, nullptr);
        delete current;
        (*amount)--;
        if (parent != nullptr)
        {
            parent->updateHeight();
        }
        return;
    }

    trim(current->getLeft(), current, amount);
}

// return the array of the element in order
template <typename T>
T *AVLTree<T>::getInOrderArray(int amount)
{
    if (amount == 0 || size < amount)
    {
        amount = size;
    }

    T *array = new T[amount];
    int index = 0;
    inOrderAux(array, &index, root, amount);
    return array;
}

template <typename T>
void AVLTree<T>::inOrderAux(T *array, int *index, Node<T> *current, int amount)
{
    if (current == nullptr || (*index) >= amount)
    {
        return;
    }

    inOrderAux(array, index, current->getLeft(), amount);
    if ((*index) < amount)
    {
        array[(*index)++] = current->getData();
    }
    inOrderAux(array, index, current->getRight(), amount);
}

// helper function for creating full binary tree with height of -h.
template <typename T>
Node<T> *AVLTree<T>::buildEmptyTree(int h)
{
    if (h < 0)
    {
        return nullptr;
    }
    Node<T> *head = new Node<T>();
    head->setHeight(h);
    head->setLeft(buildEmptyTree(h - 1));
    head->setRight(buildEmptyTree(h - 1));
    return head;
}

template <typename T>
void AVLTree<T>::updateRankPostorder(Node<T> *current)
{
    if (current == nullptr)
        return;
    updateRankPostorder(current->getLeft());
    updateRankPostorder(current->getRight());
    current->setRank(current->getData()->getGrade());
    current->updateHeight();
}

// find the node that have m bigger node than the current node
template <typename T>
long long AVLTree<T>::getHighestMRankSum(int m)
{
    long long cur_bigger_rank = 0;
    int cur_bigger_size = 0;

    Node<T> *cur_node = this->root;

    while (cur_node != nullptr)
    {
        if (cur_bigger_size + cur_node->getRightSize() > m - 1)
        {
            cur_node = cur_node->getRight();
            continue;
        }
        else if (cur_bigger_size + cur_node->getRightSize() < m - 1)
        {
            cur_bigger_rank += cur_node->getRightRank() + cur_node->getRank();
            cur_bigger_size += cur_node->getRightSize() + 1;
            cur_node = cur_node->getLeft();
        }
        else if (cur_bigger_size + cur_node->getRightSize() == m - 1)
        {
            cur_bigger_rank += cur_node->getRightRank() + cur_node->getRank();
            return cur_bigger_rank;
        }
    }

    return cur_bigger_rank;
}

template <typename T>
long long AVLTree<T>::getRank(T object, int *place)
{
    Node<T> *current = root;
    long long rank = 0;
    *place = 0;
    while (current != nullptr)
    {
        if (compare(object, current->getData()))
        {
            current = current->getLeft();
        }
        else if (compare(current->getData(), object))
        {
            rank += current->getLeftRank() + current->getRank();
            (*place) += current->getLeftSize() + 1;

            current = current->getRight();
        }
        else
        {
            (*place) += current->getLeftSize() + 1;
            return rank + current->getLeftRank() + current->getRank();
        }
    }
    return rank;
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    if (root != nullptr)
    {
        delete root;
    }
}

#endif // AVL_TREE_H