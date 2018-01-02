#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

template <class T> class Node {
public:
    T data;
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
    T popData() {
        if (isEmpty()) {
            return 0;
        }
        Node<T> temp = *top;
        top = top->next;
        return temp.data;
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


#endif /* UTILS_H */