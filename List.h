#include <bits/stdc++.h>
using namespace std;

class ListNode
{
friend class List;
private:
    pair<int, int> data;
    ListNode* next;
public:
    ListNode(pair<int, int> _data);
    ~ListNode();
};

ListNode::ListNode(pair<int, int> _data)
{
    this->data = _data;
}

ListNode::~ListNode()
{
    if (this->next)
        delete this->next; // Free the whole List.
    cout << "The node is deleted la~\n";
}

class List
{
private:
    ListNode* head;
    ListNode* first;
public:
class iterator
    {
    private:
        ListNode *current;

    public:
        iterator(ListNode *node)
        {
            this->current = node;
        }
        bool is_end()
        {
            return !this->current;
        }
        iterator operator++(int) // the (int) inplies that it is the postfix ++
        {
            iterator tmp = *this;
            this->current = this->current->next;
            return tmp;
        }
        iterator &operator++() // this is the prefix ++
        {
            this->current = this->current->next;
            return *this;
        }
        pair<int, int> &operator*() // Notice that * is a prefix operator
        {
            return (this->current->data);
        }
        pair<int, int> *operator->()
        {
            return &(this->current->data);
        }
    };
    List();
    ~List();
    void push_front(pair<int, int> data);
    iterator begin();
};

List::List()
{
    this->head = new ListNode({0, 0});
    this->first = NULL;
    this->head->next = this->first;
}

List::~List()
{
    //delete this->head;
}

void List::push_front(pair<int, int> _data)
{
    ListNode* tmp = new ListNode(_data);
    tmp->next = this->first;
    this->first = tmp;
    this->head->next = this->first;
}

List::iterator List::begin()
{
    return iterator(this->first);
}

