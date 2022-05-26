

template <class T>
class Node
{
private:
    T data;
    Node<T> *left;
    Node<T> *right;

    int height;

public:
    Node(T data) : data(data)
    {
        left = nullptr;
        right = nullptr;
        height = 0;
    }

    Node()
    {
        left = nullptr;
        right = nullptr;
        height = 0;
    }

    int getBalanceFactor() { return getHeight(left) - getHeight(right); }
    void setHeight(int height) { this->height = height; }
    int getHeight() { return height; }
    void updateHeight()
    {
        if (left == nullptr && right == nullptr)
        {
            height = 0;
        }
        else if (left == nullptr)
        {
            height = 1 + right->getHeight();
        }
        else if (right == nullptr)
        {
            height = 1 + left->getHeight();
        }
        else
        {
            if (left->getHeight() > right->getHeight())
            {
                height = 1 + left->getHeight();
            }
            else
            {
                height = 1 + right->getHeight();
            }
        }
    }
    int getHeight(Node<T> *node)
    {
        if (node == nullptr)
            return -1;
        return node->getHeight();
    }
    T getData() { return data; }

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

    ~Node()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};
