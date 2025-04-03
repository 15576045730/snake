#include "List.hpp"
#include <iostream>

// List::List()
// {
//    _head = nullptr;
//    _tail = nullptr;
//    _size = 0;
// }
List::List() : _head(nullptr), _tail(nullptr), _size(0) {}

List::~List()
{
    while (_head != nullptr)
    {
        Node *temp = _head;
        _head = _head->_next;
        delete temp;
    }
}

void List::push_back(Type e)
{
    // 构造一个新的结点
    Node *p = new Node(e);
    // 插入到链表中
    if (_head == nullptr)
    {
        _head = p;
        _tail = p;
    }
    else
    {
        _tail->_next = p;
        p->_prev = _tail;
        _tail = p;
    }

    ++_size;
}

void List::push_front(Type e)
{
    // 构造一个新的结点
    Node *p = new Node(e);
    // 插入到链表中
    if (_head == nullptr)
    {
        _head = p;
        _tail = p;
    }
    else
    {
        p->_next = _head;
        _head->_prev = p;
        _head = p;
    }

    ++_size;
}

void List::pop_back()
{
    if (_tail == nullptr)
    {
        return;
    }

    Node *old_tail = _tail;
    _tail = _tail->_prev;

    if (_tail == nullptr)
    {
        _head = nullptr; // 如果只剩一个元素，那么现在列表为空
    }
    else
    {
        _tail->_next = nullptr; // 更新新尾节点的 next 指针
    }

    delete old_tail; // 释放旧尾节点的内存
    --_size;
}

void List::pop_front()
{
    if (_head == nullptr)
    {
        return; // 如果链表为空，直接返回
    }

    Node *old_head = _head;
    _head = _head->_next;

    if (_head == nullptr)
    {
        _tail = nullptr; // 如果只剩一个元素，那么现在列表为空
    }
    else
    {
        _head->_prev = nullptr; // 更新新头节点的 prev 指针
    }

    delete old_head; // 释放旧头节点的内存
    --_size;
}

Type List::back() const
{
    if (_tail == nullptr)
    {
        std::cout << "链表为空" << std::endl;
    }
    return _tail->_data;
}

Type List::front() const
{
    if (_head == nullptr)
    {
        std::cout << "链表为空" << std::endl;
    }
    return _head->_data;
}

int List::size() const
{
    return _size;
}

bool List::empty() const
{
    return _size == 0;
}

void List::print() const
{
    if (_head == nullptr)
    {
        std::cout << "空链表" << std::endl;
        return;
    }

    Node *current = _head;
    while (current != nullptr)
    {
        std::cout << current->_data;
        if (current->_next != nullptr)
        {
            std::cout << "->"; // 只有在不是最后一个元素时才添加空格
        }
        current = current->_next;
    }
    std::cout << std::endl;
}

// Type List::get_element(int i) const
// {
//     if (i <= 0 or i > _size)
//     {
//         /* code */
//     }
//     int x = 1;
//     Node *p = _head;
//     while (i != x)
//     {
//         p = p->_next;
//         x++;
//     }
//     return p->_data;
// }

List::Node::Node(Type data)
{
    _data = data;
    _next = nullptr;
    _prev = nullptr;
}

Type &List::Iterator::operator*()
{
    return _node->_data;
}

List::Iterator &List::Iterator::operator++()
{
    _node = _node->_next;
    return *this;
}

bool List::Iterator::operator!=(const Iterator &rhs) const
{
    return this->_node != rhs._node;
}

List::Iterator List::begin()
{
    return Iterator(_head);
}

List::Iterator List::end()
{
    return Iterator(_tail);
}
