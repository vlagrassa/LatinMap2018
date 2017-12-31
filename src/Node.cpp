#include "Node.hpp"

template <class T> Node<T>::Node() {}

template <class T> Node<T>::Node(T data) : data(data) {}

template <class T> Node<T>::Node(const Node& orig) : data(orig.data), next(orig.next) {}

template <class T> Node<T>::~Node() {}

template <class T> bool Node<T>::hasNext() {
    return next != 0;
}