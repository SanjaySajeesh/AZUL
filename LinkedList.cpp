#include "LinkedList.h"

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->length = 0;
}

LinkedList::~LinkedList()
{
    clear();
}

int LinkedList::size()
{
    return length;
}

void LinkedList::clear()
{
    while (head != nullptr)
    {
        deleteFront();
    }
}

Tile LinkedList::get(int i)
{
    Node *current = head;
    for (int j = 0; j < i; j++)
    {
        current = current->next;
    }
    return current->data;
}

void LinkedList::addFront(Tile data)
{

    Node *newNode = new Node(data, nullptr);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    ++length;
}

void LinkedList::addBack(Tile data)
{
    Node *newNode = new Node(data, nullptr);
    Node *current = head;
    if (current == nullptr)
    {
        head = newNode;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    ++length;
}

void LinkedList::deleteFront()
{
    if (head != nullptr)
    {
        Node* toDelete = head;
        head = head->next;
        delete toDelete;
        --length;
    }
}

void LinkedList::deleteBack()
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->next != nullptr)
        {
            if (current->next->next == nullptr)
            {
                delete current->next;
                current->next = nullptr;
                --length;
            }
        }
        current = current->next;
    }
}

Node *LinkedList::getHead()
{
    return this->head;
}

void LinkedList::remove(Node *node)
{

    if (head == node)
    {
        deleteFront();
    }
    else
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->next == node)
            {
                current->next = node->next;
                delete node;
                --length;
            }
            current = current->next;
        }
    }
}