#ifndef NODE_H
#define NODE_H

template <class T> class Node {
public:
    Node<T>() {};
    Node<T>(T data) : data(data) {};
    Node<T>(const Node& orig) : data(orig.data), next(orig.next) {};
    //virtual ~Node<T>();
    
    bool hasNext() {
        return next != 0;
    };
    
    T data;
    Node* next;
};

#endif /* NODE_H */