#ifndef LIST_HPP
#define LIST_HPP

#include <string>
using Type = std::string;

class List
{
private:
    struct Node
    {
        Node(Type data); // 结点的构造函数
        Type _data;
        struct Node *_next;
        struct Node *_prev;
    };
    Node *_head;
    Node *_tail;
    int _size;

public:
    List();
    ~List();
    void push_back(Type e);
    void push_front(Type e);
    void pop_back();
    void pop_front();
    Type back() const;
    Type front() const;
    int size() const;
    bool empty() const;
    void print() const;
    // Type get_element(int i) const;

    class Iterator
    {
    public:
        Iterator(Node *node) : _node(node) {}
        Type &operator*();

        Iterator &operator++();

        bool operator!=(const Iterator &rhs) const;

    private:
        List::Node *_node;
    };

    Iterator begin();

    Iterator end();
};

#endif