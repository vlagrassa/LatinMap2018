#include "../src/Utils.hpp"

int main() {
    Stack<int> intStack;
    
    intStack.push(*(new Node<int>(0)));
    std::cout << intStack.pop() << "\n";
    
    intStack.push(*(new Node<int>(3)));
    std::cout << intStack << "\n";
    intStack.push(*(new Node<int>(2)));
    std::cout << intStack << "\n";
    intStack.push(*(new Node<int>(1)));
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    
    intStack.push(3);
    intStack.push(2);
    intStack.push(1);
    std::cout << intStack << "\n";
    //std::cout << intStack.popData() << "\n";
    //std::cout << intStack.popData() << "\n";
    //std::cout << intStack.popData() << "\n";
    
    
    Queue<int> intQueue(intStack);
    std::cout << intQueue << "\n";
    
    intQueue.enqueue(*(new Node<int>(4)));
    std::cout << intQueue << "\n";
    intQueue.enqueue(*(new Node<int>(5)));
    std::cout << intQueue << "\n";
    intQueue.enqueue(*(new Node<int>(6)));
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    
    intQueue.enqueue(4);
    intQueue.enqueue(5);
    intQueue.enqueue(6);
    std::cout << intQueue.dequeue() << "\n";
    std::cout << intQueue.dequeue() << "\n";
    std::cout << intQueue.dequeue() << "\n";
    
    std::cout << intStack << "\n";
    
    LinkedList<int> testList;
    std::cout << testList << "\n";
    testList.add(1);
    testList.add(2);
    testList.add(0, 3);
    testList.add(3, 4);
    std::cout << testList << "\n";
    for (Node<int>* n = testList.first; n != 0; n = n->next) {
        std::cout << n->data << "\n";
    }
    std::cout << "\n\n";
}
