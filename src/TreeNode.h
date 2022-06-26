

template <class T>
class Node
{
private:
    T data;
    unsigned long long value;
    Node<T> *left;
    Node<T> *right;
    unsigned long long left_value; // sum of the ranks of all the nodes in the left subtree
    unsigned long long right_value;
    int left_size; // number of nodes in the left subtree
    int right_size;
    int height;

public:
    Node(T data, int value) : data(data), value(value), left(nullptr), right(nullptr), left_value(0), right_value(0), left_size(0), right_size(0), height(0) {}

    Node() : data(T{}), value(0), left(nullptr), right(nullptr), left_value(0), right_value(0), left_size(0), right_size(0), height(0) {}

    int getBalanceFactor() { return getHeight(left) - getHeight(right); }
    void setHeight(int height) { this->height = height; }
    int getHeight() { return height; }
    void updateParameters()
    {
        left_value = left == nullptr ? 0 : left->getSubtreeValue();
        right_value = right == nullptr ? 0 : right->getSubtreeValue();
        left_size = left == nullptr ? 0 : left->getSize();
        right_size = right == nullptr ? 0 : right->getSize();
        height = 1 + (getHeight(left) > getHeight(right) ? getHeight(left) : getHeight(right));
    }

    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
            return -1;
        return node->getHeight();
    }
    T getData() { return data; }

    void setValue(unsigned long long value) { this->value = value; }
    unsigned long long getNodeValue() { return value; }
    unsigned long long getSubtreeValue()
    {
        return value + left_value + right_value;
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
        updateParameters();
    }
    
    void setRight(Node *node)
    {
        right = node;
        updateParameters();
    }

    unsigned long long getRightValue()
    {
        return right_value;
    }

    unsigned long long getLeftValue()
    {
        return left_value;
    }

    ~Node()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};
