#include "Node.hpp"

template <class T> class Stack {
public:
    Node<T>* top;
    
    Stack<T>() {};
    Stack<T>(Node<T>& top) : top(&top) {};
    Stack<T>(Node<T>* top) : top(top) {};
    Stack<T>(const Stack<T>& orig) : top(orig.top) {};
    virtual ~Stack<T>() {};
    
    void push(Node<T> next) {
        next.next = top;
        top = &next;
    }
    
    void push(T data) {
        Node<T> temp(data);
        push(temp);
    }
    
    Node<T>* pop() {
        if (isEmpty()) {
            return 0;
        }
        Node<T>* temp = top;
        top = top->next;
        return temp;
    }
    
    bool isEmpty() {
        return top == 0;
    }
};
