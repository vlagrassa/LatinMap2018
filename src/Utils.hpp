#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

template <class T> class Node {
public:
    T data;
    Node* next;
    
    Node<T>() : next(0) {};
    Node<T>(T data) : data(data), next(0) {};
    Node<T>(const Node& orig) : data(orig.data), next(orig.next) {};
    virtual ~Node<T>() {};
    
    bool hasNext() {
        return next != 0;
    };
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const Node<T> &n) {
        strm << &n << ": [" << n.data << "] -> " << n.next << "\n";
        return strm;
    };
    
};

template <class T> class Stack {
public:
    Node<T>* top;
    
    Stack<T>() {};
    Stack<T>(Node<T>& top) : top(&top) {};
    Stack<T>(Node<T>* top) : top(top) {};
    Stack<T>(const Stack<T>& orig) : top(orig.top) {};
    virtual ~Stack<T>() {};
    
    void push(Node<T>& next) {
        next.next = top;
        top = &next;
    }
    
    void push(T data) {
        push(*(new Node<T>(data)));
    }
    
    Node<T> popNode() {
        if (isEmpty()) {
            return 0;
        }
        Node<T> temp = *top;
        top = top->next;
        return temp;
    }
    
    T popData() {
        if (isEmpty()) {
            return 0;
        }
        Node<T> temp = *top;
        top = top->next;
        return temp.data;
    }
    
    bool isEmpty() {
        return top == 0;
    }
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const Stack<T> &s) {
        for (Node<T>* n = s.top; n->hasNext(); n = n->next) {
            strm << *n;
        }
        return strm;
    };
};


#endif /* UTILS_H */