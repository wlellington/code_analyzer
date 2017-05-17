//Wesley Elington
//CSE 2341
//Sprint 02

#ifndef LINKED_LIST
#define LINKED_LIST
#define VERBOSE false
#define DEBUG false

#include <iostream>

template <class T>
class ListNode {

public:
    //default constructor, initializes pointers to null and leaves empty payload
    ListNode<T>();

    //node copy constructor
    ListNode(const ListNode * inNode);

    //creates new node with empty pointers and payload
    ListNode<T>(const T & inObj);

    //creates new node with payload, and pointers to next and last elements
    ListNode<T>(const T & inObj, const ListNode<T> * inNext, const ListNode<T> * inLast);

    //allows for editing of node payload
    void setPayload(T & inObj);

    //sets next element pointer
    void setNext(ListNode<T>* inNext);

    //sets last element pointer
    void setLast(ListNode<T>* inLast);

    //returns payload at index
    T & getPayload();

    //returns next pointer
    ListNode<T> * getNext();

    //returns last pointer
    ListNode<T> * getLast();

    //Destuctor for single node
    ~ListNode<T>();

private:

    //points to next element in list
    ListNode<T>*next;

    //points to previous element in list
    ListNode<T>*last;

    //actual data stored in element in list
    T data;
};



template<class T>
class LinkedList {

public:

    //default constructor, initializes pointers to null and length to zero
    LinkedList<T>();

    // creates new list with one element and sets pointers
    LinkedList<T>(T inElement);

    //copies pre exsisting list
    LinkedList<T>(const LinkedList<T>&inList);

    // adds element to end of list
    void add(T inObj);

    // adds element to front of list
    void addToFront(T inObj);

    //returns an element at a given index
    T get(int index);

    //returns int size of list
    int size();

    //removes and returns element from given index
    T remove(int index);

    //returns true if no elements exsist in list, false else
    bool isEmpty();

    //destructs list element by element, freeing alloc each starting at head
    ~LinkedList();

    //returns pointer value for an element of the list given an index
    T& operator[] (int);

    //assignment operator, sets one list equal to another
    LinkedList<T>& operator=(const LinkedList<T>& inObj);

    //prints out all values in list
    void printPayloads();

    //prints out values in reverse
    void printPayloadsReverse();
    //together these two can be used to verify a list both directions


private:
    // pointer to beginning of list
    ListNode<T>*head;

    // pointer to the end of the list
    ListNode<T>*tail;

    // number of elements in list
    int num_elements;

};

//*****************************************************************
//================= List Node Implementations =====================
//*****************************************************************

//default constructor, initializes pointers to null and leaves empty payload
template <class T>
ListNode<T>::ListNode(){
    if (VERBOSE) std::cout << "Default List Node constuctor called" << std::endl;
    this->next = nullptr;
    this->last = nullptr;
}

//creates new node with empty pointers and payload
template <class T>
ListNode<T>::ListNode(const T & inObj){
    if (VERBOSE) std::cout << "Default List Node with Payload constructor called" << std::endl;
    this->next = nullptr;
    this->last = nullptr;
    this->data = inObj;
}

//creates new node with payload, and pointers to next and last elements
template <class T>
ListNode<T>::ListNode(const T & inObj, const ListNode<T> * inNext, const ListNode<T> * inLast){
    if (VERBOSE) std::cout << "Default List Node with Payload and pointers Constructors Called" << std::endl;
    this->next = inNext;
    this->last = inLast;
    this->data = inObj;
}

// copy constructor for node
template<class T>
ListNode<T>::ListNode(const ListNode * inNode){
    if (VERBOSE) std::cout << "List Node copy constructor called" <<std::endl;
    //sets data payload
    this->data = inNode->data;
    //leaves next and last references blank
    this->next = nullptr;
    this->last = nullptr;
}

//allows for editing of node payload
template <class T>
void ListNode<T>::setPayload(T & inObj){
    if (VERBOSE) std::cout << "Set Payload of List Node Called" << std::endl;
    this->data = inObj;
}

//sets next element pointer
template <class T>
void ListNode<T>::setNext(ListNode<T> * inNext){
    if (VERBOSE) std::cout << "Set next pointer in Node Called" << std::endl;
    this->next = inNext;
}

//sets last element pointer
template <class T>
void ListNode<T>::setLast(ListNode<T> * inLast){
    if (VERBOSE) std::cout << "Set last pointer in Node Called" << std::endl;
    this->last = inLast;
}

//returns payload at index
template <class T>
T & ListNode<T>::getPayload(){
    if (VERBOSE) std::cout << "Get payload of Node Called" << std::endl;
    return this->data;

}

//returns next pointer at index
template <class T>
ListNode<T> * ListNode<T>::getNext(){
    if (VERBOSE) std::cout << "Get next pointer of Node Called" << std::endl;
    return this->next;
}

//returns last pointer at index
template <class T>
ListNode<T> * ListNode<T>::getLast(){
    if (VERBOSE) std::cout << "Get last pointer of Node Called" << std::endl;
    return this->last;
}

//Destuctor for single node
template <class T>
ListNode<T>::~ListNode<T>(){
    if (VERBOSE) std::cout << "Node Destructor Called" << std::endl;


}

//*****************************************************************
//================ Linked List implementations ====================
//*****************************************************************

//default constructor, initializes pointers to null and length to zero
template <class T>
LinkedList<T>::LinkedList(){
    if (VERBOSE) std::cout << "Defualt Linked List Constructor Called" <<std::endl;
    this->head = nullptr;
    this->tail = nullptr;
    this->num_elements = 0;
}

// creates new list with one element and sets pointers
template <class T>
LinkedList<T>::LinkedList(T inElement){
    if (VERBOSE) std::cout << "Default Linked List with First Element Constructor called" <<std::endl;
    ListNode<T> * newElement  = new ListNode<T>(inElement);
    head = newElement;
    tail = newElement;
    num_elements = 1;
}

//copies pre exsisting list
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& inList){
    if (VERBOSE) std::cout << "Copy Linked List Constructor Called" <<std::endl;
    ListNode<T> * currNode = inList.head;
    ListNode<T> * newNode;
    ListNode<T> * lastNew = nullptr;
    //ListNode<T> * nextNew = nullptr;
    this->num_elements = inList.num_elements;

    //initialize empty list
    if(this->num_elements == 0){
        this->head = nullptr;
        this->tail = nullptr;
    }

    else{ // add elements to list if any exsist
        while(currNode != nullptr){
            if (DEBUG) std::cout << "Creating new Node in copy" <<std::endl;
            //create new node
            newNode = new ListNode<T>(currNode);
             //set node last pointer to old new node
            newNode->setLast(lastNew);

            //set referance forward from last node if not empty
            if(lastNew != nullptr){
                //set previous node next to current
                lastNew->setNext(newNode);
            }

            // set placeholder to store old new node
            lastNew = newNode;

            //set tail if last element
            if(currNode->getNext() == nullptr){
                if (DEBUG) std::cout << "New tail set!" << std::endl;
                this->tail = newNode;
            }
            //set head if first element
            if(currNode->getLast() == nullptr){
                if (DEBUG) std::cout << "New head set!" << std::endl;
                this->head = newNode;
            }

            //move forward in list
            currNode = currNode->getNext();
        }

    }

}

// adds element to end of list
template <class T>
void LinkedList<T>::add(T inObj){
    if (VERBOSE) std::cout << "Add to Linked List Called" << std::endl;
    //create new node object
    ListNode<T> * newElement = new ListNode<T>(inObj);

    // if list was empty before hand
    if(this->isEmpty() == true){
        if (DEBUG) std::cout << "First element in array created!" <<std::endl;
        //point head to new item
        this->head = newElement;
        //point tail to new item
        this->tail = newElement;
    }

    else{
        //create placeholder for old last item
        ListNode<T> * oldEnd = this->tail;

        //set next pointer in old to new element
        oldEnd->setNext(newElement);
        //set last pointer in new last to old last
        newElement->setLast(oldEnd);
        //set tail to point to new element
        this->tail = newElement;
    }

    if (DEBUG)  std::cout << "Adding element at: " << &newElement <<std::endl;

    //increase size variable
    this->num_elements = this->num_elements + 1;
}

// adds element to front of list
template <class T>
void LinkedList<T>::addToFront(T inObj){
    if(VERBOSE) std::cout << "AddToFront of Linked List Called" << std::endl;
    //create new element
    ListNode<T> * newElement = new ListNode<T>(inObj);

    //if list was initially empty
    if(this->isEmpty() == true){
        //set tail to point to new element
        this->tail = newElement;
        //set head to point to new element
        this->head = newElement;
    }

    else{
        ListNode<T> * oldStart = this->head;

        //set element to point to old first item in array
        newElement->setNext(this->head);
        //set head to point to new element
        this->head = newElement;
        oldStart->setLast(newElement);
    }
    //increase size variable
    this->num_elements = this->num_elements + 1;
}

//returns an element at a given index
template <class T>
T LinkedList<T>::get(int index){ 
    if(VERBOSE) std::cout << "Get element of Linked List Called" << std::endl;

    //start at head
    ListNode<T> * currNode = this->head; 

    //loop through list until desired element is reached
    for(int i = 0; i < index; i++){ 
       //move to next item
       currNode = currNode->getNext(); 
    }

    //return payload object
    return currNode->getPayload(); 
}

//returns int size of list
template <class T>
int LinkedList<T>::size(){ 
    if (VERBOSE) std::cout << "Size function of Linked List Called" << std::endl;
    return this->num_elements;
}

//removes and returns element from given index
template <class T>
T LinkedList<T>::remove(int index){
    if (VERBOSE) std::cout << "Remove function of Linked List Called" << std::endl;
    // start at head of list;
    ListNode<T> * currNode = this->head; 
    ListNode<T> * placeHolder;

    //loop through list looking for index
    for(int i = 0; i < index; i ++){ 
        if (DEBUG) std::cout << "Looking at index: " << i << std::endl;
        placeHolder = currNode->getNext();
        currNode = placeHolder;
        if (DEBUG) std::cout << "Current Node at: " << &currNode << std::endl;
    }

    if (DEBUG) std::cout << "Creating placeholders" <<std::endl;

    //create place holders for array before and after deletion item
    ListNode<T> * lastNode = currNode->getLast();
    ListNode<T> * nextNode = currNode->getNext(); 
    //store payload
    T returnVal = currNode->getPayload(); 

    if (DEBUG) std::cout << "Last Node at: " << &lastNode << " Next Node at: " << &nextNode << std::endl;

    if (DEBUG) std::cout << "Linking gap pointers" << std::endl;

    if(num_elements == 1){
        this->head = nullptr;
        this->tail = nullptr;
    }

    else{
        //if not last element
        if(currNode->getNext() != nullptr){ 
            if (DEBUG) std::cout << "Forward assigned!" << std::endl;
             //assign pointer for prev element to point to next
            nextNode->setLast(nextNode);
        }
        else{
            if (DEBUG) std::cout << "Tail Reassigned!" << std::endl;
            //reassign tail
            this->tail = currNode->getLast(); 
            //set forward pointer to null
            lastNode = currNode->getLast(); 
            lastNode->setNext(nullptr);
        }

        //if not first element
        if(currNode->getLast() != nullptr){ 
            if (DEBUG) std::cout << "Backward assigned!" << std::endl;
            //assign point from next element to point to prev
            lastNode->setNext(nextNode); 
        }
        else{
            if (DEBUG) std::cout << "Head Reassigned!" << std::endl;
            //reassign head
            this->head = currNode->getNext(); 
            //set back pointer to null
            nextNode = currNode->getNext(); 
            nextNode->setLast(nullptr);
        }
    }

    if (DEBUG) std::cout << "Deleting element" << std::endl;
    //delete item at index
    delete currNode; 

    //decrease size of list
    this->num_elements = this->num_elements - 1; 


    return returnVal;

}

//returns true if no elements exsist in list, false else
template <class T>
bool LinkedList<T>::isEmpty(){ 
    if (VERBOSE) std::cout << "IsEmpty function of Linked List Called" << std::endl;
    if(this->num_elements == 0){
        return true;
    }
    return false;
}

//destructs list element by element, freeing alloc for each starting at head
template <class T>
LinkedList<T>::~LinkedList(){
    if (VERBOSE)  std::cout << "Linked List Destructor Called" << std::endl;
    //assign placeholder pointers for iteration
    ListNode<T> * currNode = this->head; 
    ListNode<T> * nextNode = nullptr;
    
    //loop over full list, deleting each element
    while(currNode != nullptr){ 
        if (DEBUG)  std::cout << "Deleting element at: " << &currNode <<std::endl;
        nextNode = currNode->getNext();
        delete currNode;
        currNode = nextNode;
    }

}

//returns pointer value for an element of the list given an index
template <class T>
T& LinkedList<T>::operator[] (int index){
    if (VERBOSE) std::cout << "[] operator for Linked List Called" << std::endl;
    ListNode<T> * currNode = this->head;
    ListNode<T> * nextNode = nullptr;

    //print error if out of bounds
    if(index >= this->num_elements){
        std::cout << "Index out of bounds!" << std::endl;
    }

    for(int i = 0; i < index; i++){
        nextNode = currNode->getNext();
        currNode = nextNode;
    }

    if (DEBUG) std::cout << "Getting payload from: " <<&currNode <<std::endl;
    return currNode->getPayload();
}

//assignment operator, sets one list equal to another
template <class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T>& inList){
    if (VERBOSE) std::cout << "= operator for Linked List Called" << std::endl;
    this->~LinkedList();
    ListNode<T> * currNode = inList.head;
    ListNode<T> * newNode;
    ListNode<T> * lastNew = nullptr;

    //functionality non used
    //ListNode<T> * nextNew = nullptr;

    this->num_elements = inList.num_elements;

    //initialize empty list
    if(this->num_elements == 0){
        this->head = nullptr;
        this->tail = nullptr;
    }

    // add elements to list if any exsist
    else{
        while(currNode != nullptr){
            if (DEBUG) std::cout << "Creating new Node in copy" <<std::endl;
            //create new node
            newNode = new ListNode<T>(currNode);
            //set node last pointer to old new node
            newNode->setLast(lastNew);

            //set referance forward from last node if not empty
            if(lastNew != nullptr){
                //set previous node next to current
                lastNew->setNext(newNode);
            }

            // set placeholder to store old new node
            lastNew = newNode;

            //set tail if last element
            if(currNode->getNext() == nullptr){
                if (DEBUG) std::cout << "New tail set!" << std::endl;
                this->tail = newNode;
            }
            //set head if first element
            if(currNode->getLast() == nullptr){
                if (DEBUG) std::cout << "New head set!" << std::endl;
                this->head = newNode;
            }

            //move forward in list
            currNode = currNode->getNext();
        }

    }

    if (DEBUG) std::cout << "New Head: " << & this->head <<std::endl;
    if (DEBUG) std::cout << "New Tail: " << & this->tail <<std::endl;
    return * this;

}

//prints out contents of list in forward order
template <class T>
void LinkedList<T>::printPayloads(){
    ListNode<T> * currNode = this->head;
    int location = 0;
    std::cout << "===================" <<std::endl;
    std::cout << "Printing list of length: " << this->num_elements <<std::endl;
    while(currNode != nullptr){
        std::cout << "Index: " << location << std::endl;
        std::cout << currNode->getPayload() <<std::endl;
        location++;
        currNode = currNode->getNext();
    }

    std::cout << "===================" <<std::endl;
}

//prints out contents of list in reverse order
template<class T>
void LinkedList<T>::printPayloadsReverse(){
    ListNode<T> * currNode = this->tail;
    int location = 0;
    std::cout << "===================" <<std::endl;
    std::cout << "Printing Reverse list of length: " << this->num_elements <<std::endl;
    while(currNode != nullptr){
        std::cout << "Index: " << this->size() - location << std::endl;
        std::cout << currNode->getPayload() <<std::endl;
        location++;
        currNode = currNode->getLast();
    }

    std::cout << "===================" <<std::endl;
}




#endif
