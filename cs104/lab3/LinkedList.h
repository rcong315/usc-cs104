#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
    public:
        Node* next;
        int data;
};

class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void add(int data);
        void InsertNth(int index, int data);
        void RemoveDuplicates();
        
        Node* head;

};

#endif