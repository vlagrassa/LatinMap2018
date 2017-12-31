#ifndef NODE_H
#define NODE_H

template <class T> class Node {
public:
    Node();
    Node(T data);
    Node(const Node& orig);
    virtual ~Node();
    
    bool hasNext();
    
    T data;
    Node* next;
};

#endif /* NODE_H */