#include <iostream>
#include <string>
#include <queue>

struct Item
{
    int quantity;
    float cost;
};

struct Node
{
    Item data;
    Node *next;
    Node *prev;
    Node(Item data) : data(data), next(nullptr), prev(nullptr) {}
};

class SortedItems
{
    Node *head;
    Node *tail;

public:
    SortedItems() : head(nullptr), tail(nullptr) {}
    Node *begin()
    {
        return head;
    }
    Node *end()
    {
        return tail;
    }
    void insert(Item value)
    {
        Node *n = head;
        if (head == nullptr)
        {
            push_back(value);
            return;
        }
        while (n != nullptr)
        {
            if (n->data.quantity * n->data.cost >= value.quantity * value.cost)
            {
                insert_before(n, value);
                return;
            }
            n = n->next;
        }
        push_back(value);
    }

    void push_back(Item value)
    {
        Node *n = new Node(value);
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    void push_front(Item value)
    {
        Node *n = new Node(value);
        if (head == nullptr)
        {
            head = n;
            tail = n;
        }
        else
        {
            head->prev = n;
            n->next = head;
            head = n;
        }
    }
    void insert_before(Node *n, Item value)
    {
        if (n == nullptr)
        {
            push_back(value);
            return;
        }
        if (n == head)
        {
            push_front(value);
            return;
        }
        Node *new_node = new Node(value);
        new_node->next = n;
        new_node->prev = n->prev;
        n->prev->next = new_node;
        n->prev = new_node;
    }

    void print()
    {
        Node *tmp = head;
        while (tmp != nullptr)
        {
            std::cout << tmp->data.quantity << " " << tmp->data.cost << std::endl;
            tmp = tmp->next;
        }
    }
    Item last()
    {
        Item x = tail->data;
        pop_back();
        return x;
    }
    void pop_front()
    {
        if (head == nullptr)
        {
            return;
        }
        if (tail == head)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *n = head;
        head = head->next;
        head->prev = nullptr;
        delete n;
    }
    bool empty()
    {
        return head == nullptr;
    }
    void pop_back()
    {
        if (tail == nullptr)
        {
            return;
        }
        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node *n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete n;
    }
    ~SortedItems()
    {
        clear();
    }
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    SortedItems(const SortedItems &original) : head(nullptr), tail(nullptr)
    {
        Node *tmp = original.head;
        while (tmp != nullptr)
        {
            push_back(tmp->data);
            tmp = tmp->next;
        }
    }
    SortedItems &operator=(const SortedItems &original)
    {
        if (this == &original)
        {
            return *this;
        }
        while (!empty())
        {
            pop_front();
        }
        Node *temp = original.head;
        while (temp != nullptr)
        {
            push_back(temp->data);
            temp = temp->next;
        }
        return *this;
    }
};

int main()
{
    Item c;
    c.cost = 2.1;
    c.quantity = 20;
    SortedItems q;

    Item c4;
    c4.cost = 2.2;
    c4.quantity = 3;

    Item c2;
    c2.cost = 3.4;
    c2.quantity = 1;

    q.insert(c);
    q.insert(c2);
    q.insert(c4);
    q.print();

    SortedItems q2;
    q2 = q;
    q2.print();
}