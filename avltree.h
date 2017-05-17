#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

#define VERBOSE false


//implementation of AVL Tree nodes
//each contains a payload and pointers to two children


template<class T>
class TreeNode{
public:
    //pointers to childeren
    TreeNode<T> * leftchild;
    TreeNode<T> * rightchild;

    //data payload
    T payload;

    //height value for balancing
    int heightint;

    //constructors
    TreeNode<T>();
    TreeNode<T>(TreeNode<T> * & inNode);
    TreeNode<T>(T value);

    //assignment operator
    TreeNode<T> & operator=(TreeNode<T> & inNode);

    //mutators
    void setPayload(T);
    void setLeft(TreeNode<T> * inNode);
    void setRight(TreeNode<T> * inNode);
    TreeNode<T> * getLeft();
    TreeNode<T> * getRight();
    T getPayload();

    //print node and children
    void print();
    void printPost();

    //destructor
    ~TreeNode<T>();
};

//implementation of AVL Tree, contains tree root pointer and public
//functions to balance tree
template <class T>
class AVLTree{
private:

    //pointer to root node
    TreeNode<T> * root;

public:

    //class TreeNode<T>;

    //constructors
    AVLTree<T>();
    AVLTree<T>(AVLTree & inTree);

    //assignment operator
    AVLTree<T> * operator=(AVLTree<T> & inTree);

    //insert into tree, create node for provided value
    void addNode(T);

    //remove node from tree, return value removed
    T removeNode(T);

    //find node, return pointer to
    TreeNode<T> * findValue(T value);

    //print out tree
    void print();
    void printPost();

    //destructor
    ~AVLTree();
};

//=================================
//     AVL Tree Implementation
//=================================

//constructors
template<class T>
AVLTree<T>::AVLTree(){
    if(VERBOSE) std::cout << "AVL Tree Defualt Constructor Called" <<std::endl;
    this->root = nullptr;
}

template<class T>
AVLTree<T>::AVLTree(AVLTree<T> & inTree){
    if(VERBOSE) std::cout << "AVL Tree Copy Constructor Called" <<std::endl;
    if(inTree.root != nullptr){
        this->root = new TreeNode<T>(inTree.root);
    }
}

//assignment operator
template<class T>
AVLTree<T> * AVLTree<T>::operator=(AVLTree<T> & inTree ){
    if(VERBOSE) std::cout << "AVL Tree Assignment Operator Called" <<std::endl;

    //clear old tree
    delete root;

    if( inTree.root != nullptr){
        this->root = new TreeNode<T>(inTree.root);
    }
    else{
        this->root = nullptr;
    }
    return this;
}

//insert into tree
template<class T>
void AVLTree<T>::addNode(T value){
    if(VERBOSE) std::cout << "AVL Tree addNode Called" <<std::endl;

    //create new node if tree is empty
    if (root == nullptr){
        root = new TreeNode<T>(value);
    }

    //recursivly add to tree
    else{
        add(root, value);
    }
}

//remove node from tree, return value removed
template<class T>
T AVLTree<T>::removeNode(T){
    if(VERBOSE) std::cout << "AVL Tree removeNode Called" <<std::endl;

}

//find node, return pointer to if found, null otherwise
template<class T>
TreeNode<T> * AVLTree<T>::findValue(T value){
    if(VERBOSE) std::cout << "AVL Tree findNode Called" <<std::endl;
    if(root == nullptr){
        return nullptr;
    }
    return find(root, value);

}

//print tree in order
template<class T>
void AVLTree<T>::print(){
    if(VERBOSE) std::cout << "AVL Tree print Called" <<std::endl;
    if (root != nullptr){
        root->print();
    }
    else{
        std::cout << "Tree empty!" <<std::endl;
    }

}

//post order print
template<class T>
void AVLTree<T>::printPost(){
    if(VERBOSE) std::cout << "AVL Tree printPost Called" <<std::endl;
    if (root != nullptr){
        root->printPost();
    }
    else{
        std::cout << "Tree empty!" <<std::endl;
    }

}

//destructor, calls recursive delete on root
template<class T>
AVLTree<T>::~AVLTree(){
    if(VERBOSE) std::cout << "AVL Tree Destuctor Called" <<std::endl;
    if(root != nullptr){
        delete root;
    }
    if(VERBOSE) std::cout << "AVL Tree Destuction Complete" <<std::endl;

}


//=================================
//    Tree Node Implementation
//=================================


//constructors
template<class T>
TreeNode<T>::TreeNode(){
    if(VERBOSE) std::cout << "TreeNode Defualt Constructor Called" <<std::endl;
    this->leftchild = nullptr;
    this->rightchild = nullptr;
}

//copy constructor
template<class T>
TreeNode<T>::TreeNode(TreeNode<T> * & inNode){
    //be aware that direct assignment of nodes can lead to redundancy
    //setting node payload may be more advisable
    if(VERBOSE) std::cout << "TreeNode Copy Constructor Called" <<std::endl;

    this->leftchild = nullptr;
    this->rightchild = nullptr;

    //if in node has left, add as child
    if(inNode->leftchild  != nullptr){
        this->leftchild = new TreeNode<T>(inNode->leftchild);
    }

    //if in node has right, add as child
    if(inNode->rightchild != nullptr){
        this->rightchild = new TreeNode<T>(inNode->rightchild);
    }
    this->payload = inNode->payload;
    this->heightint = inNode->heightint;
}

//value only constructor
template<class T>
TreeNode<T>::TreeNode(T value){
    this->leftchild = nullptr;
    this->rightchild = nullptr;
    this->heightint = 0;
    this->payload = value;
}

//assignment operator
template<class T>
TreeNode<T> & TreeNode<T>::operator=(TreeNode<T> & inNode){
    //direct assignment will drop references to childeren, best let AVL assignment handle this
    if(VERBOSE) std::cout << "TreeNode Assignment Operator Called" <<std::endl;
    this->leftchild = inNode->leftchild;
    this->rightchild = inNode->rightchild;
    this->payload = inNode->payload;
}

//****************
// MUTATORS
//****************

//the following are primarily for debugging purposes, do not use in high level implementation

template<class T>
void TreeNode<T>::setPayload(T inObj){
    if(VERBOSE) std::cout << "TreeNode setPayload Called" <<std::endl;
    this->payload = inObj;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T> * inNode){
    if(VERBOSE) std::cout << "TreeNode setLeft Called" <<std::endl;
    this->leftchild = inNode;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T> * inNode){
    if(VERBOSE) std::cout << "TreeNode setRight Called" <<std::endl;
    this->rightchild = inNode;
}

template<class T>
TreeNode<T> * TreeNode<T>::getLeft(){
    if(VERBOSE) std::cout << "TreeNode getLeft Called" <<std::endl;
    return this->getLeft();
}

template<class T>
TreeNode<T> * TreeNode<T>::getRight(){
    if(VERBOSE) std::cout << "TreeNode getRight Called" <<std::endl;
    return this->rightchild;
}

template<class T>
T TreeNode<T>::getPayload(){
    if(VERBOSE) std::cout << "TreeNode getPayload Called" <<std::endl;
    return payload;
}


//in order print
template<class T>
void TreeNode<T>::print(){

    //print left
    if(leftchild != nullptr){
        leftchild->print();
    }

    //print self
    this->payload.print();

    //print right
    if(rightchild != nullptr){
        rightchild->print();
    }

}

//post order printing
template<class T>
void TreeNode<T>::printPost(){
    //print left
    if(leftchild != nullptr){
        leftchild->print();
    }

    //print right
    if(rightchild != nullptr){
        rightchild->print();
    }

    //print self
    std::cout << this->payload <<std::endl;

}


//destructor, deletes subtree with self as root
template<class T>
TreeNode<T>::~TreeNode(){
    //should an item need to be deleted from within tree, isolate and
    //set pointers to null
    if(VERBOSE) std::cout << "TreeNode Destructor Called" <<std::endl;

    //look left, delete child
    if(this->leftchild != nullptr){
        delete leftchild;
    }

    //look right, delete child
    if(this->rightchild != nullptr){
        delete rightchild;
    }

    //delete self
}

//returns height of node
template<class T>
int height(TreeNode<T> * inNode){
    if(inNode == nullptr){
        return -1;
    }
    return inNode->heightint;
}

//returns maximum of two ints
int max(int first, int second){
    if (first > second){
        return first;
    }
    return second;
}

//instert item into tree
template<class T>
void add(TreeNode<T> * &inNode, T value) {
    if (VERBOSE) std::cout << "Add function called" << std::endl;
    //check if null, if so, add self
    if(inNode == nullptr){
        inNode = new TreeNode<T>(value);
    }

    //if value is on left side of curr node
    else if(value < inNode->payload){
        //add node to left child
        add(inNode->leftchild, value);

        //check if alpha unbalance is 2
        if(height(inNode->leftchild) - height(inNode->rightchild) == 2){
            //if value was added to left child, rotate
            if(value < inNode->leftchild->payload){
                rotateWithLeftChild(inNode);
            }

            //if value was added to right subtree of left child
            else{
                doubleWithLeftChild(inNode);
            }
        }
    }

    //if value is on right side of curr node
    else if(inNode->payload < value){
        //add node to right subtree
        add(inNode->rightchild, value);

        //check if unbalanced
        if(height(inNode->rightchild) - height(inNode->leftchild) == 2){
            //if value was added to right child
            if(inNode->rightchild->payload < value){
                rotateWithRightChild(inNode);
            }

            //if value was added to left subtree of right child
            else{
                doubleWithRightChild(inNode);
            }
        }
    }
    //update node height
    inNode->heightint = max(height(inNode->leftchild), height(inNode->rightchild)) + 1;
}


//ROTATIONS

//case 1 rotation
template<class T>
void rotateWithLeftChild( TreeNode<T> * & a2 ){
    if (VERBOSE) std::cout << "rotateLeft function called" << std::endl;

    TreeNode<T> *a1 = a2->leftchild;
    //rotate children
    a2->leftchild = a1->rightchild;
    //move a2 to child
    a1->rightchild = a2;
    //update heights
    a2->heightint = max( height( a2->leftchild ), height( a2->rightchild ) ) + 1;
    a1->heightint = max( height( a1->leftchild ), a2->heightint ) + 1;
    //finish swap
    a2 = a1;
}

//case 4 rotation
template<class T>
void rotateWithRightChild( TreeNode<T> * & a1 ){
    if (VERBOSE) std::cout << "rotateRight function called" << std::endl;

    TreeNode<T> *a2 = a1->rightchild;
    //rotate children
    a1->rightchild = a2->leftchild;
    //move a2 to child
    a2->leftchild = a1;
    //update heights
    a1->heightint = max( height( a1->leftchild ), height( a1->rightchild ) ) + 1;
    a2->heightint = max( height( a2->rightchild ), a1->heightint ) + 1;
    //finish swap
    a1 = a2;
}

//case 2 rotation
template<class T>
void doubleWithLeftChild( TreeNode<T> * & a3 ){
    if (VERBOSE) std::cout << "doubleWithLeftChild function called" << std::endl;

    //move child up
    rotateWithRightChild( a3->leftchild );
    //move child equal
    rotateWithLeftChild( a3 );
}

//case 3 rotation
template<class T>
void doubleWithRightChild( TreeNode<T> * & a1 ){
    if (VERBOSE) std::cout << "doubleWithRightChild function called" << std::endl;

    //move child up
    rotateWithLeftChild( a1->rightchild );
    //move child equal
    rotateWithRightChild( a1 );
}

template<class T>
TreeNode<T> * find(TreeNode<T> * & inNode, T value){
    if (VERBOSE) std::cout << "Find function called" << std::endl;

    //check null
    if(inNode == nullptr){
        return nullptr;
    }

    //if value is current node
    if(inNode->payload == value){
        return inNode;
    }

    //if left child exsists, search
    if(value < inNode->payload){
        return find(inNode->leftchild, value);
    }

    //if right child exsists, search
    else{
        return find(inNode->rightchild, value);
    }
    //return value of result
    return nullptr;

}

#endif // AVLTREE_H

