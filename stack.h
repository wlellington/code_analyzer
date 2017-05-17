//Wesley Elington
//CSE 2341
//Sprint 02

#ifndef STACK
#define STACK

#include "linkedlist.h"

template<class T>
class Stack{

public:

    //default constructor
    Stack();

    //copy constructor
    Stack(const Stack<T> & inStack);

    //return first item off top of stack;
    T pop();

    //view first item off top of stack without popping
    T peek();

    //add item to top of stack
    void push(T inElement);

    //indicates if stack is empty
    bool isEmpty();

    //give returns size of stack
    int size();

    //indicates if item is in stack
    bool isIn(T inObj);

    //prints items in stack
    void printStack();

     //destructor
    ~Stack();

private:

    LinkedList<T> data;

};


//default constructor
template<class T>
Stack<T>::Stack(){
    this->data = (LinkedList<T>());
}

//copy constructor
template<class T>
Stack<T>::Stack(const Stack<T> &inStack){
    this->data = (LinkedList<T>(inStack.data));
}

//return first item off top of stack
template<class T>
T Stack<T>::pop(){
    return this->data.remove(0);
}

//view first item off top of stack without popping
template<class T>
T Stack<T>::peek(){
    return this->data.get(0);
}

//add item to top of stack
template<class T>
void Stack<T>::push(T inElement){
    this->data.addToFront(inElement);
}

//indicates if stack is empty
template<class T>
bool Stack<T>::isEmpty(){
    return this->data.isEmpty();
}

//returns size of stack
template<class T>
int Stack<T>::size(){
    return data.size();
}

//indicates if item exsists in stack
template<class T>
bool Stack<T>::isIn(T inObj){
    for(int i =0; i < data.size(); i ++){
        if (inObj ==  data[i]){
            return true;
        }
    }
    return false;
}

//prints stack items
template<class T>
void Stack<T>::printStack(){
    std::cout << "=====Printing Stack=====" << std::endl;
    for(int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;

    }
    std::cout << "======================= " <<std::endl;
}

//destructor
template<class T>
Stack<T>::~Stack(){

}

#endif
