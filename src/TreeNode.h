

template <class T>
class Node
{
private:
    T data;
    Node<T> *left;
    Node<T> *right;
    int rank;
    int left_rank; // sum of the ranks of all the nodes in the left subtree
    int right_rank;
    int left_size; // number of nodes in the left subtree
    int right_size;
    int height;

public:
    Node(T data, int rank) : data(data)
    {
        left = nullptr;
        right = nullptr;
        height = 0;
        this->rank = rank;
        left_rank = 0;
        right_rank = 0;
        left_size = 0;
        right_size = 0;
    }

    Node()
    {
        left = nullptr;
        right = nullptr;
        height = 0;
        rank = 0;
        left_rank = 0;
        right_rank = 0;
        left_size = 0;
        right_size = 0;
    }

    int getBalanceFactor() { return getHeight(left) - getHeight(right); }
    void setHeight(int height) { this->height = height; }
    int getHeight() { return height; }
    void updateHeight()
    {
        if (left == nullptr && right == nullptr)
        {
            height = 0;
            left_rank = 0;
            right_rank = 0;
            left_size = 0;
            right_size = 0;
        }
        else if (left == nullptr)
        {
            left_size = 0;
            right_size = right->getSize();
            height = 1 + right->getHeight();
            left_rank = 0;
            right_rank = right->getRankSum();
        }
        else if (right == nullptr)
        {
            left_size = left->getSize();
            right_size = 0;
            height = 1 + left->getHeight();
            left_rank = left->getRankSum();
        }
        else
        {
            // take the max of the left and right subtree heights
            if (left->getHeight() > right->getHeight())
            {

                height = 1 + left->getHeight();
            }
            else
            {
                height = 1 + right->getHeight();
            }

            left_size = left->getSize();
            right_size = right->getSize();
            left_rank = left->getRankSum();
            right_rank = right->getRankSum();
        }
    }
    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
            return -1;
        return node->getHeight();
    }
    T getData() { return data; }

    void setRank(int rank) { this->rank = rank; }
    int getRank() { return rank; }
    int getRankSum()
    {
        return rank + left_rank + right_rank;
    }

    int getSize()
    {
        return 1 + left_size + right_size;
    }
    int getLeftSize()
    {
        return left_size;
    }
    int getRightSize()
    {
        return right_size;
    }
    const T getData() const { return data; }

    Node<T> *getLeft() { return left; }

    Node<T> *getRight() { return right; }

    void setData(T data) { this->data = data; }

    void setLeft(Node *node)
    {
        left = node;
        updateHeight();
    }
    
    void setRight(Node *node)
    {
        right = node;
        updateHeight();
    }
    int getRightRank()
    {
        return right_rank;
    }
    int getLeftRank()
    {
        return left_rank;
    }
    ~Node()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};
