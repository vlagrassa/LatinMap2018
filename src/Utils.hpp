#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

template <class T> class Node {
public:
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * The data of type T stored in the Node.
     */
    T data;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * A pointer to the Node following the current Node.
     */
    Node* next;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default constructor method. Initializes data & next to 0.
     */
    Node<T>() : data(0), next(0) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Initializes data, sets next to 0.
     * 
     * @param data The data to store in Node
     */
    Node<T>(T data) : data(data), next(0) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Copy constructor method. Copies data and next directly
     * from the original Node.
     * 
     * @return The original Node to copy from
     */
    Node<T>(const Node& orig) : data(orig.data), next(orig.next) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default destructor. Currently deletes nothing.
     */
    virtual ~Node<T>() {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Check whether `next` value points to a Node. Note it will
     * point to 0x0 if no subsequent Node exists. Equivalent to:
     * 
     *   return next != 0;
     * 
     * @return Whether there is a next Node
     */
    bool hasNext() const {
        return next != 0;
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Resets `next` value to not point to any Node. Equivalent
     * to:
     * 
     *   next = 0;
     */
    void clearNext() {
        next = 0;
    }
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const Node<T> &n) {
        strm << &n << ": [" << n.data << "] -> " << n.next << "\n";
        return strm;
    };
    
};

template <class T> class Stack {
public:
    Node<T>* top;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default constructor method.
     */
    Stack<T>() {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Takes a Node which becomes the first
     * entry into the Stack. Note that the type of the Node must
     * match the type of the Stack.
     * 
     * @param top The first Node
     */
    Stack<T>(Node<T>& top) : top(&top) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Takes a pointer to a Node to be the
     * first entry into the Stack. Note that the Node's type and
     * the Stack's type must match.
     * 
     * @param top Pointer to the first Node
     */
    Stack<T>(Node<T>* top) : top(top) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Copy constructor method. Sets top of the new Stack to the
     * same Node as the previous stack. Does not currently make
     * a duplicate of any Node.
     */
    Stack<T>(const Stack<T>& orig) : top(orig.top) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default destructor method. Does not delete anything.
     */
    virtual ~Stack<T>() {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Add a given Node to the top of the Stack.
     * 
     * @param next The Node to be added
     */
    void push(Node<T>& next) {
        next.next = top;
        top = &next;
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Add a Node with the given data to the top of the Stack.
     * Equivalent to:
     * 
     *   push(*(new Node<T>(data)));
     * 
     * @param data The data to be added
     */
    void push(T data) {
        push(*(new Node<T>(data)));
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Remove and return the top value from the Stack. Note that
     * this method returns the Node itself.
     * 
     * @return The top Node
     */
    Node<T> popNode() {
        if (isEmpty()) {
            return 0;
        }
        Node<T> temp = *top;
        top = top->next;
        return temp;
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Remove and return the top value from the Stack. Note that
     * this method returns the data not contained in a Node.
     * 
     * @return The data of the top Node
     */
    T pop() {
        return popNode().data;
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Check whether the Stack contains any data.
     * 
     * @return Whether Stack is empty
     */
    bool isEmpty() const {
        return top == 0;
    }
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const Stack<T> &s) {
        strm << "Stack " << &s << ":\n";
        for (Node<T>* n = s.top; n != 0; n = n->next) {
            strm << "  " << *n;
        }
        return strm;
    };
};

template <class T> class Queue {
public:
    Node<T>* head;
    Node<T>* tail;
    
    Queue<T>() : head(0), tail(0) {};
    Queue<T>(Node<T>& start) : head(&start), tail(&start) {};
    Queue<T>(Node<T>* start) : head(start), tail(start) {};
    
    Queue<T>(const Stack<T>& s) {
        if (s.isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            for (Node<T>* n = s.top; n != 0; n = n->next) {
                enqueue(*n);
            }
        }
    };
    
    Queue<T>(const Queue<T>& orig) {
        if (orig.isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            for (Node<T>* n = orig.head; n != 0; n = n->next) {
                enqueue(n);
            }
        }
    };
    
    void enqueue(Node<T>& next) {
        if (isEmpty()) {
            head = &next;
            tail = &next;
        } else {
            tail->next = &next;
            tail = &next;
        }
    };
    
    void enqueue(T data) {
        enqueue(*(new Node<T>(data)));
    }
    
    Node<T> dequeueNode() {
        if (isEmpty()) {
            return 0;
        }
        Node<T> temp = *head;
        
        if (head == tail) {
            head = 0;
            tail = 0;
        } else {
            head = head->next;
        }
        
        return temp;
    }
    
    T dequeue() {
        return dequeueNode().data;
    }
    
    bool isEmpty() {
        return ((head == 0) && (tail == 0));
    }
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const Queue<T> &q) {
        strm << "Queue " << &q << ":\n";
        for (Node<T>* n = q.head; n != 0; n = n->next) {
            strm << "  " << *n;
        }
        return strm;
    };
};
    
#endif /* UTILS_H */