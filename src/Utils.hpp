#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

template <class T> class Node;
template <class T> class Stack;
template <class T> class Queue;
template <class T> class LinkedList;
template <class T> class ActiveVector;

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
        strm << &n << ": [" << typeid(n.data).name() << " @ " << &n.data << "] -> " << n.next << "\n";
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
     * Copy constructor method. Copies each Node in the original
     * Stack into a new Stack, as opposed to simply copying top.
     */
    Stack<T>(const Stack<T>& orig) {
        top = 0;
        Stack<T> temp;
        for (Node<T>* n = orig.top; n != 0; n = n->next) {
            temp.push(*(new Node<T>(n)));
        }
        for (Node<T>* n = temp.top; n != 0; n = n->next) {
            push(n);
        }
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Copies a Queue into a Stack. Note the
     * type of the Stack and type of the Queue must match.
     * 
     * Maintains the original order of removal, such that values
     * will be popped in the same order they would be dequeued.
     * 
     * Note this creates a copy of each Node.
     * 
     * @param q The Queue to copy
     */
    Stack<T>(const Queue<T>& q) {
        top = 0;
        Stack<T> temp;
        for (Node<T>* n = q.head; n != 0; n = n->next) {
            temp.push(*(new Node<T>(n)));
        }
        for (Node<T>* n = temp.top; n != 0; n = n->next) {
            push(n);
        }
    };
    
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
     * Remove and return the top item from the Stack. Note that
     * this method returns the Node itself.
     * 
     * @return The top Node
     */
    Node<T> popNode() {
        if (isEmpty()) {
            throw std::out_of_range("Trying to remove from empty Stack.");
        }
        Node<T> temp = *top;
        top = top->next;
        return temp;
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Remove and return the top value from the Stack. Note that
     * this method returns the raw data, not contained in a Node.
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
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * The front of the Queue.
     */
    Node<T>* head;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * The back of the Queue.
     */
    Node<T>* tail;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default constructor method. Initializes head & tail to 0.
     */
    Queue<T>() : head(0), tail(0) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Takes a Node which becomes the first
     * entry into the Queue. Note that the type of the Node must
     * match the type of the Queue.
     * 
     * @param start The first Node
     */
    Queue<T>(Node<T>& start) : head(&start), tail(&start) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Takes a pointer to a Node to be the
     * first entry into the Queue. Note that the Node's type and
     * the Queue's type must match.
     * 
     * @param start Pointer to the first Node
     */
    Queue<T>(Node<T>* start) : head(start), tail(start) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Takes a value which becomes the first
     * entry into the Queue. Note that the type must match the
     * type of the Queue.
     * 
     * @param start The first value to enter the Queue
     */
    Queue<T>(T start) : Queue<T>(new Node<T>(start)) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Constructor method. Copies a Stack into a Queue. Note the
     * type of the Stack and type of the Queue must match.
     * 
     * Equivalent to enqueueing each value in the Stack in the
     * order of removal, which means values will be dequeued in
     * the same order they would be popped.
     * 
     * Note this creates a copy of each Node.
     * 
     * @param s The Stack to copy
     */
    Queue<T>(const Stack<T>& s) {
        if (s.isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            for (Node<T>* n = s.top; n != 0; n = n->next) {
                enqueue(*(new Node<T>(*n)));
            }
        }
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Copy constructor method. Copies each Node in the original
     * Queue into a new Queue, as opposed to simply copying head
     * and tail.
     * 
     * @param orig The Queue to be copied
     */
    Queue<T>(const Queue<T>& orig) {
        if (orig.isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            for (Node<T>* n = orig.head; n != 0; n = n->next) {
                enqueue(new Node<T>(n));
            }
        }
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Add a given Node to the end (tail) of the Queue.
     * 
     * @param next The Node to add
     */
    void enqueue(Node<T>& next) {
        if (isEmpty()) {
            head = &next;
            tail = &next;
        } else {
            tail->next = &next;
            tail = &next;
        }
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Add a value to the end (tail) of the Queue. Equivalent to:
     * 
     *   enqueue(*(new Node<T>(data)));
     * 
     * @param data The value to add
     */
    void enqueue(T data) {
        enqueue(*(new Node<T>(data)));
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Remove and return the top item from the Queue. Note that
     * this method returns the Node itself.
     * 
     * @return The top Node
     */
    Node<T> dequeueNode() {
        if (isEmpty()) {
            throw std::out_of_range("Trying to remove from empty Queue.");
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
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Remove and return the top value from the Queue. Note that
     * this method returns the raw data, not contained in a Node.
     * 
     * @return The data of the top Node
     */
    T dequeue() {
        return dequeueNode().data;
    }
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Check whether the Stack contains any data.
     * 
     * @return Whether Stack is empty
     */
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

template <class T> class LinkedList {
public:
    Node<T>* first;
    Node<T>* last;
    unsigned int size;
    
    LinkedList() {};
    LinkedList(const LinkedList& orig) {};
    virtual ~LinkedList();
    
    Node<T> getNode(unsigned int index) {
        Node<T>* temp = first;
        for (unsigned int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }
    
    T get(unsigned int index) {
        return getNode(index).data;
    }
    
    void add(unsigned int index, Node<T> next) {
        if (index > size) {
            throw std::out_of_range("Adding to LinkedList.");
        }
        else if (isEmpty()) {
            first = &next;
            last = &next;
            size++;
        }
        else if (index == 0) {
            addFirst(next);
        }
        else if (index == size) {
            addLast(next);
        }
        else {
            Node<T>* temp = first;
            for (unsigned int i = 0; i < index-1; i++) {
                temp = temp->next;
            }
            next->next = temp->next;
            temp->next = next;
            size++;
        }
    }
    
    void add(unsigned int index, T data) {
        add(*(new Node<T>(data)));
    }
    
    void addFirst(Node<T> next) {
        if (isEmpty()) {
            last = &next;
        }
        next.next = first;
        first = &next;
        size++;
    }
    
    void addFirst(T data) {
        addFirst(*(new Node<T>(data)));
    }
    
    void addLast(Node<T> next) {
        if (isEmpty()) {
            first = &next;
            last = &next;
        } else {
            last->next = &next;
            last = &next;
        }
        size++;
    }
    
    void addLast(T data) {
        addLast(*(new Node<T>(data)));
    }
    
    void add(Node<T> next) {
        addLast(next);
    }
    
    void add(T data) {
        addLast(T);
    }
    
    Node<T> removeNode(unsigned int index) {
        if (index >= size) {
            throw std::out_of_range("Removing from LinkedList.");
        }
        else if (first == last) {
            Node<T> temp = *first;
            first = 0;
            last = 0;
            size--;
            return temp;
        }
        else if (index == 0) {
            return removeFirstNode();
        }
        else if (index == size-1) {
            return removeLastNode();
        }
        else {
            Node<T>* temp = first;
            for (unsigned int i = 0; i < index-1; i++) {
                temp = temp->next;
            }
            Node<T> result = *temp->next;
            temp->next = temp->next->next;
            size--;
            return result;
        }
    }
    
    T remove(unsigned int index) {
        return removeNode(index).data;
    }
    
    Node<T> removeFirstNode() {
        if (isEmpty()) {
            throw std::out_of_range("Trying to remove first from empty LinkedList.");
        }
        Node<T> temp = *first;
        
        if (first == last) {
            first = 0;
            last = 0;
        } else {
            first = first->next;
        }
        size--;
        
        return temp;
    }
    
    T removeFirst() {
        return removeFirstNode().data;
    }
    
    Node<T> removeLastNode() {
        if (isEmpty()) {
            throw std::out_of_range("Trying to remove last from empty LinkedList.");
        }
        
        Node<T> temp = *last;
        for (Node<T>* current = first; current != 0; current = current->next) {
            if (current->next == last) {
                last = current;
                last->next = 0;
                size--;
                return temp;
            }
        }
    }
    
    T removeLast() {
        return removeLastNode().data;
    }
    
    bool isEmpty() {
        return first == 0 && last == 0;
    }
    
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 * 
 * A specialized subclass of std::vector<T> which stores an
 * active index.
 */
template <class T> class ActiveVector : public std::vector<T> {
public:
    unsigned int activeIndex;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default constructor method. Initializes activeIndex to 0.
     */
    ActiveVector() : activeIndex(0) {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Copy constructor method. Copies each item in orig as well
     * as activeIndex. Note this utilizes the copy constructor
     * of class T, which is not guaranteed to work as expected.
     * 
     * @param orig The ActiveVector to copy
     */
    ActiveVector(const ActiveVector& orig) : activeIndex(orig.getActiveIndex()) {
        for (T x : orig) {
            push_back(*(new T(x)));
        }
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Default destructor.
     */
    virtual ~ActiveVector() {};
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Get the item at the active index. Equivalent to:
     * 
     *   return this->at(activeIndex);
     * 
     * @return The active item
     */
    T getActive() const {
        return this->at(activeIndex);
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Get the active index.
     * 
     * @return The active index
     */
    unsigned int getActiveIndex() const {
        return activeIndex;
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * 
     * Set the active index.
     * 
     * @param The new active index
     */
    void setActiveIndex(unsigned int n) {
        if (n > this->size()) {
            throw std::out_of_range(std::string("New activeIndex ") + std::to_string(n) + std::string(" out of range for size ") + std::to_string(this->size()) + std::string(" ActiveVector."));
        } else {
            activeIndex = n;
        }
    };
};

#endif /* UTILS_H */
